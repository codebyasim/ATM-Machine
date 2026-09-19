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
        transactions.push_back(Transaction("Deposit", amount));
    }
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    balance -= amount;

    transactions.push_back(Transaction("Withdrawal", amount));

    return true;
}

bool Account::transfer(Account& recipient, double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    balance -= amount;
    recipient.balance += amount;

    transactions.push_back(Transaction("Transfer to " +
                                       recipient.getAccountHolder(), amount));

    recipient.transactions.push_back(Transaction("Transfer from " +
                                                 accountHolder, amount));

    return true;
}

double Account::getBalance() const {
    return balance;
}

const std::vector<Transaction>& Account::getTransactions() const {
    return transactions;
}

void Account::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}