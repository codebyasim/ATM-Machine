#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {

public:
    SavingsAccount(
        int number,
        std::string name,
        double initialBalance,
        int accountPin
    );

    void applyInterest(double rate);

    void displayAccountType() const override;
};

#endif