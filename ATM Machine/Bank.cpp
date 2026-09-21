#include "Bank.h"
#include <fstream>
#include <algorithm>

void Bank::addAccount(const Account& account) {
    accounts.emplace(
        account.getAccountNumber(),
        std::make_unique<Account>(account)
    );
}

Account* Bank::findAccount(int accountNumber) {
    auto it = accounts.find(accountNumber);

    if (it != accounts.end()) {
        return it->second.get();
    }

    return nullptr;
}

std::unordered_map<int, std::unique_ptr<Account>>& Bank::getAccounts() {
    return accounts;
}

Account* Bank::findAccountWithBalance(double minimumBalance) {

    auto result = std::find_if(
        accounts.begin(),
        accounts.end(),
        [minimumBalance](const auto& pair) {
            return pair.second->getBalance() >= minimumBalance;
        }
    );

    if (result != accounts.end()) {
        return result->second.get();
    }

    return nullptr;
}

void Bank::saveAccounts(const std::string& filename) const {
    std::ofstream file(filename);

    for (const auto& pair : accounts) {
    const Account& account = *pair.second;

        file << "ACCOUNT,"
             << account.getAccountNumber() << ","
             << account.getAccountHolder() << ","
             << account.getBalance() << ","
             << account.getPin() << "\n";

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
            int pin;
            char comma;

            file >> number >> comma;
            std::getline(file, name, ',');
            file >> balance >> comma >> pin;
            file.ignore();

            accounts.emplace(
                number,
                std::make_unique<Account>(number, name, balance, pin)
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