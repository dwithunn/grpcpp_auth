#include <db/auth_fncs.hpp>

bool db::Auth_Methods::user_exists(const std::string &credential_id) {
  db::main database;
  if (!database.connect()) return false;

  try
  {
    pqxx::work txn(*database.cx);
    pqxx::result r = txn.exec(
      "SELECT 1 FROM users WHERE username = " + txn.quote(credential_id)
    );
    return !r.empty();
  }
  catch(const std::exception& e)
  {
    std::cerr<< "DB query failed:\n" << e.what() << '\n';
    return false;
  }

}

bool db::Auth_Methods::check_pswd(const std::string& credential_id, const std::string& pswd) {
    db::main database;
    if (!database.connect()) return false;

    try {
        pqxx::work txn(*database.cx);

        // Modern invocation
        pqxx::result r = txn.exec("SELECT password FROM users WHERE username = $1" + credential_id);

        if (r.empty()) return false;

        std::string db_pswd = r[0][0].as<std::string>();
        return pswd == db_pswd;
    } catch(const std::exception& e) {
        std::cerr << "DB query failed:\n" << e.what() << '\n';
        return false;
    }
}


