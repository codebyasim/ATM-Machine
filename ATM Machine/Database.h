#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include "Account.h"
#include "Bank.h"

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
    void close();
};

#endif