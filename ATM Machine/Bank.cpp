#include "Bank.h"
#include <fstream>

void Bank::addAccount(const Account& account) {
    accounts.push_back(account);
}

Account* Bank::findAccount(int accountNumber) {
    for (Account& account : accounts) {
        if (account.getAccountNumber() == accountNumber) {
            return &account;
        }
    }

    return nullptr;
}

std::vector<Account>& Bank::getAccounts() {
    return accounts;
}

void Bank::saveAccounts(const std::string& filename) const {
    std::ofstream file(filename);

    for (const Account& account : accounts) {
        file << account.getAccountNumber() << ","
             << account.getAccountHolder() << ","
             << account.getBalance() << "\n";
    }
}

void Bank::loadAccounts(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        return;
    }

    int number;
    std::string name;
    double balance;

    char comma;

    while (file >> number >> comma
                && std::getline(file, name, ',')
                && file >> balance) {

        accounts.emplace_back(number, name, balance, 1234);
    }
}