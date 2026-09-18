#include "Account.h"

Account::Account(int number, std::string name, double initialBalance, int accountPin) {
    accountNumber = number;
    accountHolder = name;
    balance = initialBalance;
    pin = accountPin;
}


int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getAccountHolder() const {
    return accountHolder;
}

bool Account::verifyPin(int enteredPin) const {
    return enteredPin == pin;
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