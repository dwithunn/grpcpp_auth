#include "db/db_main.hpp"

bool db::main::connect() {
    try {
        cx = std::make_unique<pqxx::connection>("dbname=demo user=postgres host=localhost password=fish");
        if (cx->is_open()) {
            std::cout << "Connected to database: " << cx->dbname() << "\n";
            return true;
        } else {
            std::cerr << "Failed to connect\n";
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << "Connection error: " << e.what() << "\n";
        return false;
    }
}
