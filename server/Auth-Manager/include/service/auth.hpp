#pragma once
#include <iostream>
#include <jwt-cpp/jwt.h>
#include "Auth.grpc.pb.h"
#include "Auth.pb.h"
#include <chrono>
#include <string>
#include <memory.h>
#include <db/auth_fncs.hpp>
#include <grpcpp/grpcpp.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <google/protobuf/map.h>

using Status = grpc::Status;

namespace Authenticator 
{
  class Login_Validator final : public AuthService::services::Service
  {
  private:
    std::string credential_id;
    std::string password;

  public:
    //Login_Validator();
    virtual Status Login(grpc::ServerContext* context, const AuthService::Credentials* request, AuthService::Auth_Response* response) override;
    
    bool validate();
    std::string IssueJwt(std::string& credential_id);
    std::time_t SetTimeStamp();
  };
  
} // namespace Authenticator
