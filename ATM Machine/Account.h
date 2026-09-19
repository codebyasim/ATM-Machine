#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class Account {

private:
    int accountNumber;
    std::string accountHolder;
    double balance;
    int pin;
    std::vector<Transaction> transactions;

public:
    Account(int number, std::string name, double initialBalance, int accountPin);

    int getAccountNumber() const;
    std::string getAccountHolder() const;

    bool verifyPin(int enteredPin) const;

    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account& recipient, double amount);
    double getBalance() const;

    const std::vector<Transaction>& getTransactions() const;
    void addTransaction(const Transaction& transaction);
};

#endif