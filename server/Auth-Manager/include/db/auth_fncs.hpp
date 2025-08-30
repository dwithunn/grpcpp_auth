#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <db/db_main.hpp>
#include <string>

namespace db {

class Auth_Methods {
public:
    Auth_Methods() = default;

    bool user_exists(const std::string &credential_id);
    bool check_pswd(const std::string& credential_id, const std::string& pswd);
    bool add_user(const std::string &credential_id, const std::string& password); // example
};

}// namespace db

