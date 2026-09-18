#include "Account.h"

Account::Account(double initialBalance) {
    balance = initialBalance;
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