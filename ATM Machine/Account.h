#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {

private:
    int accountNumber;
    std::string accountHolder;
    double balance;
    int pin;

public:
    Account(int number, std::string name, double initialBalance, int accountPin);

    int getAccountNumber() const;
    std::string getAccountHolder() const;

    bool verifyPin(int enteredPin) const;

    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
};

#endif