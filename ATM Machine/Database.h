#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include "Account.h"
#include <unordered_map>
#include <memory>

class Bank;

class Database {

private:
    sqlite3* db;

public:
    Database();
    ~Database();

    bool open(const std::string& filename);
    bool createTables();
    bool saveAccount(const Account& account);
    Account* findAccount(int accountNumber);

    bool saveAccounts(
        const std::unordered_map<int, std::unique_ptr<Account>>& accounts
    );

    bool loadAccounts(Bank& bank);

    void close();
};

#endif