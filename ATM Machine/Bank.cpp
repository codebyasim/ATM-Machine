#include "Bank.h"
#include <fstream>

void Bank::addAccount(const Account& account) {
    accounts.emplace(account.getAccountNumber(), account);
}

Account* Bank::findAccount(int accountNumber) {
    auto it = accounts.find(accountNumber);

    if (it != accounts.end()) {
        return &it->second;
    }

    return nullptr;
}

std::unordered_map<int, Account>& Bank::getAccounts() {
    return accounts;
}

void Bank::saveAccounts(const std::string& filename) const {
    std::ofstream file(filename);

    for (const auto& pair : accounts) {
    const Account& account = pair.second;

        file << "ACCOUNT,"
             << account.getAccountNumber() << ","
             << account.getAccountHolder() << ","
             << account.getBalance() << "\n";

        for (const Transaction& transaction : account.getTransactions()) {

            file << "TRANSACTION,"
                 << account.getAccountNumber() << ","
                 << transaction.getType() << ","
                 << transaction.getAmount() << "\n";
        }
    }
}

void Bank::loadAccounts(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        return;
    }

    std::string type;

    while (std::getline(file, type, ',')) {

        if (type == "ACCOUNT") {

            int number;
            std::string name;
            double balance;
            char comma;

            file >> number >> comma;
            std::getline(file, name, ',');
            file >> balance;
            file.ignore();

            accounts.emplace(
                number,
                Account(number, name, balance, 1234)
            );
        }

        else if (type == "TRANSACTION") {

            int accountNumber;
            std::string transactionType;
            double amount;
            char comma;

            file >> accountNumber >> comma;
            std::getline(file, transactionType, ',');
            file >> amount;
            file.ignore();

            Account* account = findAccount(accountNumber);

            if (account != nullptr) {
                account->addTransaction(
                    Transaction(transactionType, amount)
                );
            }
        }
    }
}