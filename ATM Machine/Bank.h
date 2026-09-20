#ifndef BANK_H
#define BANK_H

#include <unordered_map>
#include "Account.h"
#include <string>

class Bank {

private:
    std::unordered_map<int, Account> accounts;

public:
    void addAccount(const Account& account);
    Account* findAccount(int accountNumber);
    Account* findAccountWithBalance(double minimumBalance);
    std::unordered_map<int, Account>& getAccounts();
    
    void saveAccounts(const std::string& filename) const;
    void loadAccounts(const std::string& filename);
};

#endif