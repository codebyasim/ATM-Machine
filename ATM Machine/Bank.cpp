#include "Bank.h"

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