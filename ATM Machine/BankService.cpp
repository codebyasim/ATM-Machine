#include "BankService.h"

// Constructor
BankService::BankService(Bank& bank)
    : bank(bank)
{
}

// Login
Account* BankService::login(int accountNumber, int pin) {

    Account* account = bank.findAccount(accountNumber);

    if (account == nullptr) {
        return nullptr;
    }

    if (!account->verifyPin(pin)) {
        return nullptr;
    }

    return account;
}

// Get balance
double BankService::getBalance(Account& account) {
    return account.getBalance();
}

// Deposit
void BankService::deposit(Account& account, double amount) {
    account.deposit(amount);
}

// Withdraw
bool BankService::withdraw(Account& account, double amount) {
    return account.withdraw(amount);
}

// Transfer
bool BankService::transfer(
    Account& sender,
    int recipientNumber,
    double amount
) {

    Account* recipient = bank.findAccount(recipientNumber);

    if (recipient == nullptr) {
        return false;
    }

    if (recipient == &sender) {
        return false;
    }

    return sender.transfer(*recipient, amount);
}