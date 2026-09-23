#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include "Account.h"

class Database {

private:
    sqlite3* db;

public:
    Database();
    ~Database();

    bool open(const std::string& filename);
    bool createTables();
    bool saveAccount(const Account& account);
    void close();
};

#endif