#include "Transaction.h"

Transaction::Transaction(std::string transactionType, double transactionAmount) {
    type = transactionType;
    amount = transactionAmount;
}

std::string Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}