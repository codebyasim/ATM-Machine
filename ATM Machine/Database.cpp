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

bool Database::createTables() {

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS accounts (
            account_number INTEGER PRIMARY KEY,
            account_holder TEXT NOT NULL,
            balance REAL NOT NULL,
            pin INTEGER NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    int result = sqlite3_exec(
        db,
        sql,
        nullptr,
        nullptr,
        &errorMessage
    );

    if (result != SQLITE_OK) {
        std::cout << "Failed to create accounts table: "
                  << errorMessage << "\n";

        sqlite3_free(errorMessage);
        return false;
    }

    std::cout << "Accounts table created successfully.\n";
    return true;
}