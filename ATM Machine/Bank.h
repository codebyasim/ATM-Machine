#ifndef BANK_H
#define BANK_H

#include <unordered_map>
#include "Account.h"
#include <memory>

class Bank {

private:
    std::unordered_map<int, std::unique_ptr<Account>> accounts;

public:
    // Method with parameter
    void addAccount(const Account& account);
    // Method with parameter
    Account* findAccount(int accountNumber);
    // Method with parameter
    Account* findAccountWithBalance(double minimumBalance);
    std::unordered_map<int, std::unique_ptr<Account>>& getAccounts();
    
};

#endif