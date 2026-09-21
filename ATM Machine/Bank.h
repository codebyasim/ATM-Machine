#ifndef BANK_H
#define BANK_H

#include <unordered_map>
#include "Account.h"
#include <string>
#include <memory>

class Bank {

private:
    std::unordered_map<int, std::unique_ptr<Account>> accounts;

public:
    void addAccount(const Account& account);
    Account* findAccount(int accountNumber);
    Account* findAccountWithBalance(double minimumBalance);
    std::unordered_map<int, std::unique_ptr<Account>>& getAccounts();
    
    void saveAccounts(const std::string& filename) const;
    void loadAccounts(const std::string& filename);
};

#endif