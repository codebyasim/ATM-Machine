#include <iostream>
#include <iomanip>
#include <limits>
#include "Bank.h"
#include "SavingsAccount.h"
#include "Database.h"
#include "BankService.h"

using namespace std;

void displayMenu() {
    cout << "\n1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Transaction History\n";
    cout << "5. Transfer Money\n";
    cout << "6. Find Account by Minimum Balance\n";
    cout << "7. Exit\n";
    cout << "Choose: ";
}

void checkBalance(Account& account, BankService& bankService) {
    cout << fixed << setprecision(2);
    cout << "Balance: GBP "
         << bankService.getBalance(account)
         << "\n";
}

void deposit(Account& account, BankService& bankService) {
    double amount;

    cout << "Enter deposit: GBP ";
    cin >> amount;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
        return;
    }

    try {
        bankService.deposit(account, amount);

        cout << "Deposit successful. Balance: GBP "
             << bankService.getBalance(account) << "\n";
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void withdraw(Account& account, BankService& bankService) {
    double amount;

    cout << "Enter withdrawal: GBP ";
    cin >> amount;

    if (cin.fail() || amount <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
        return;
    }

    try {
        bankService.withdraw(account, amount);

        cout << "Withdrawal successful. Balance: GBP "
             << bankService.getBalance(account) << "\n";
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void showTransactionHistory(const Account& account) {
    cout << "\n--- Transaction History ---\n";

    const auto& transactions = account.getTransactions();

    if (transactions.empty()) {
        cout << "No transactions yet.\n";
        return;
    }

    cout << fixed << setprecision(2);

    for (const Transaction& transaction : transactions) {
        cout << transaction.getType()
             << ": GBP "
             << transaction.getAmount()
             << "\n";
    }
}

void transferMoney(Account& sender, BankService& bankService) {
    int recipientNumber;
    double amount;

    cout << "Enter recipient account number: ";
    cin >> recipientNumber;

    cout << "Enter amount to transfer: GBP ";
    cin >> amount;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
        return;
    }

    try {
        bool success = bankService.transfer(
            sender,
            recipientNumber,
            amount
        );

        if (success) {
            cout << "Transfer successful.\n";
        }
        else {
            cout << "Transfer failed. Recipient account not found "
                 << "or invalid recipient.\n";
        }
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}
    
void findAccountByMinimumBalance(Bank& bank) {
    double minimumBalance;

    cout << "Enter minimum balance: GBP ";
    cin >> minimumBalance;

    Account* account = bank.findAccountWithBalance(minimumBalance);

    if (account != nullptr) {
        cout << "Account found: "
             << account->getAccountNumber()
             << " - "
             << account->getAccountHolder()
             << " - Balance: GBP "
             << account->getBalance()
             << "\n";
    }
    else {
        cout << "No account found with that balance.\n";
    }
}

void testSavingsAccount() {
    SavingsAccount savings(10004, "Savings User", 1000, 9999);

    Account* account = &savings;

    account->displayAccountType();

    cout << "Savings balance: GBP "
         << account->getBalance() << "\n";

    savings.applyInterest(5);

    cout << "After 5% interest: GBP "
         << savings.getBalance() << "\n";
}

int main() {

    testSavingsAccount();

    Database database;

    if (!database.open("atm.db")) {
    return 1;
    }

    if (!database.createTables()) {
    return 1;
    }

    Bank bank;
    BankService bankService(bank, database);

    database.loadAccounts(bank);

    if (bank.getAccounts().empty()) {
        bank.addAccount(Account(10001, "Asim", 1000, 1234));
        bank.addAccount(Account(10002, "Ahmed", 2000, 5678));
        bank.addAccount(Account(10003, "John", 1500, 4321));

        SavingsAccount savings(10004, "Savings User", 1000, 9999);
        bank.addAccount(savings);
}

    int number;

    cout << "============================\n";
    cout << "       C++ ATM SYSTEM       \n";
    cout << "============================\n";

    cout << "\nEnter account number: ";
    cin >> number;
    Account* account = bank.findAccount(number);

    if (account == nullptr) {
        cout << "Account not found.\n";
        return 0;
    }

    int enteredPin;
    bool authenticated = false;

    for (int attempts = 3; attempts > 0; attempts--) {

        cout << "Enter PIN: ";
        cin >> enteredPin;

        account = bankService.login(number, enteredPin);

        if (account != nullptr) {
            authenticated = true;
            break;
        }

        cout << "Incorrect PIN. Attempts remaining: "
            << attempts - 1 << "\n";
    }

    if (!authenticated) {
        cout << "Too many incorrect attempts. Access denied.\n";
        return 0;
    }

    cout << "\nWelcome, "
         << account->getAccountHolder()
         << "!\n";

    int choice;

    while (true) {

        displayMenu();
        cin >> choice;

        if (choice == 1)
            checkBalance(*account, bankService);

        else if (choice == 2)
            deposit(*account, bankService);

        else if (choice == 3)
           withdraw(*account, bankService);

        else if (choice == 4)
            showTransactionHistory(*account);

        else if (choice == 5)
            transferMoney(*account, bankService);

        else if (choice == 6) {
        findAccountByMinimumBalance(bank);
    }

        else if (choice == 7) {
  
            bankService.saveAllAccounts();
        
        cout << "Account data saved.\n";
        cout << "Thank you for using the ATM.\n";
        break;
    }

        else
            cout << "Invalid choice.\n";
    }

    return 0;
}