#ifndef BANK_H
#define BANK_H

#include <vector>
#include "Account.h"
#include <string>

class Bank {

private:
    std::vector<Account> accounts;

public:
    void addAccount(const Account& account);
    Account* findAccount(int accountNumber);
    std::vector<Account>& getAccounts();
    
    void saveAccounts(const std::string& filename) const;
    void loadAccounts(const std::string& filename);
};

#endif