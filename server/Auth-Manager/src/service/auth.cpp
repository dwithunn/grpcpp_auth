#include <service/auth.hpp>

Status Authenticator::Login_Validator::Login(grpc::ServerContext* context, const AuthService::Credentials* request, AuthService::Auth_Response* response)
{
  db::Auth_Methods database;
  credential_id = request->id();
  password = request->password();

  if(!database.check_pswd(credential_id, password)){
    std::cerr << "Incorrect password" << std::endl;
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid credentials");
  }

  if(validate())
  {
  // issue jwt token
  std::string token = IssueJwt(credential_id);
  response->set_token(token);
  }

  return grpc::Status::OK;
}


bool Authenticator::Login_Validator::validate()
{
  db::Auth_Methods database;
  return database.user_exists(this->credential_id);
}


std::string Authenticator::Login_Validator::IssueJwt(std::string& credential_id)
{
  auto token = jwt::create()
    .set_issuer("Med Deck")
    .set_type("JWT")
    .set_payload_claim("user", jwt::claim(credential_id))
    .set_issued_at(std::chrono::system_clock::now())
    .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes(30))
    .sign(jwt::algorithm::hs256{"This is the hash"});
  return token;
}

