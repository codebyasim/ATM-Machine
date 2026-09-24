#include "Database.h"
#include <iostream>
#include "Bank.h"

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

bool Database::saveAccount(const Account& account) {

    const char* sql = R"(
        INSERT OR REPLACE INTO accounts
        (account_number, account_holder, balance, pin)
        VALUES (?, ?, ?, ?);
    )";

    sqlite3_stmt* statement;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK) {
        std::cout << "Failed to prepare account insert.\n";
        return false;
    }

    sqlite3_bind_int(
        statement,
        1,
        account.getAccountNumber()
    );

    sqlite3_bind_text(
        statement,
        2,
        account.getAccountHolder().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_double(
        statement,
        3,
        account.getBalance()
    );

    sqlite3_bind_int(
        statement,
        4,
        account.getPin()
    );

    result = sqlite3_step(statement);

    sqlite3_finalize(statement);

    if (result != SQLITE_DONE) {
        std::cout << "Failed to save account.\n";
        return false;
    }

    std::cout << "Account saved to database.\n";
    return true;
}

Account* Database::findAccount(int accountNumber) {

    const char* sql = R"(
        SELECT account_number, account_holder, balance, pin
        FROM accounts
        WHERE account_number = ?;
    )";

    sqlite3_stmt* statement;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK) {
        return nullptr;
    }

    sqlite3_bind_int(statement, 1, accountNumber);

    result = sqlite3_step(statement);

    if (result == SQLITE_ROW) {

        int number = sqlite3_column_int(statement, 0);
        const char* name =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1)
            );
        double balance = sqlite3_column_double(statement, 2);
        int pin = sqlite3_column_int(statement, 3);

        Account* account =
            new Account(number, name, balance, pin);

        sqlite3_finalize(statement);

        return account;
    }

    sqlite3_finalize(statement);

    return nullptr;
}

bool Database::saveAccounts(
    const std::unordered_map<int, std::unique_ptr<Account>>& accounts
) {
    for (const auto& pair : accounts) {

        const Account& account = *pair.second;

        if (!saveAccount(account)) {
            return false;
        }
    }

    return true;
}

bool Database::loadAccounts(Bank& bank) {

    const char* sql = R"(
        SELECT account_number, account_holder, balance, pin
        FROM accounts;
    )";

    sqlite3_stmt* statement;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK) {
        std::cout << "Failed to load accounts.\n";
        return false;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {

        int number = sqlite3_column_int(statement, 0);

        const char* name =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1)
            );

        double balance = sqlite3_column_double(statement, 2);

        int pin = sqlite3_column_int(statement, 3);

        bank.addAccount(
            Account(number, name, balance, pin)
        );
    }

    sqlite3_finalize(statement);

    std::cout << "Accounts loaded from database.\n";
    return true;
}