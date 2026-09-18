#ifndef BANK_H
#define BANK_H

#include <vector>
#include "Account.h"

class Bank {

private:
    std::vector<Account> accounts;

public:
    void addAccount(const Account& account);
    Account* findAccount(int accountNumber);
    std::vector<Account>& getAccounts();
};

#endif