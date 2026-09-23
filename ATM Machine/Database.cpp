#include "Database.h"
#include <iostream>

Database::Database() {
    db = nullptr;
}

Database::~Database() {
    close();
}

bool Database::open(const std::string& filename) {
    int result = sqlite3_open(filename.c_str(), &db);

    if (result != SQLITE_OK) {
        std::cout << "Failed to open database.\n";
        return false;
    }

    std::cout << "Database opened successfully.\n";
    return true;
}

void Database::close() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}