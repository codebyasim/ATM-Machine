#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount(
    int number,
    std::string name,
    double initialBalance,
    int accountPin
)
    : Account(number, name, initialBalance, accountPin)
{
}

void SavingsAccount::applyInterest(double rate) {
    double interest = getBalance() * rate / 100;
    deposit(interest);
}

void SavingsAccount::displayAccountType() const {
    std::cout << "Account Type: Savings Account\n";
}