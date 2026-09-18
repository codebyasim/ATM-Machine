#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {

private:
    std::string type;
    double amount;

public:
    Transaction(std::string transactionType, double transactionAmount);

    std::string getType() const;
    double getAmount() const;
};

#endif