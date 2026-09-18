#include "Account.h"

Account::Account(int number, std::string name, double initialBalance) {
    accountNumber = number;
    accountHolder = name;
    balance = initialBalance;
}

int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getAccountHolder() const {
    return accountHolder;
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    balance -= amount;
    return true;
}

double Account::getBalance() const {
    return balance;
}