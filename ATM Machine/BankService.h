#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include "Bank.h"
#include "Database.h"

class BankService {

private:
    Bank& bank;
    Database& database;

public:
    // Constructor
    BankService(Bank& bank, Database& database);

    // Banking operations
    Account* login(int accountNumber, int pin);

    double getBalance(Account& account);

    void deposit(Account& account, double amount);

    bool withdraw(Account& account, double amount);

    bool transfer(Account& sender, int recipientNumber, double amount);
};

#endif