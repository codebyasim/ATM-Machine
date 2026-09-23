#include "Bank.h"
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
