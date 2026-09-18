#include <iostream>
#include <iomanip>
#include <limits>
#include "Account.h"
#include <vector>

using namespace std;

// Display ATM menu
void displayMenu() {

    cout << "\n----- ATM MENU -----\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Transaction History\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

// Check balance
void checkBalance(const Account& account) {

    cout << fixed << setprecision(2);

    cout << "Your balance is: GBP "
         << account.getBalance() << "\n";
}

// Deposit
void deposit(Account& account) {

    double amount;

    cout << "Enter amount to deposit: GBP ";
    cin >> amount;

    if (cin.fail()) {

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Invalid amount.\n";
        return;
    }

    if (amount <= 0) {

        cout << "Amount must be greater than GBP 0.\n";
        return;
    }

    account.deposit(amount);

    cout << fixed << setprecision(2);

    cout << "Deposit successful.\n";
    cout << "New balance: GBP "
         << account.getBalance() << "\n";
}

// Withdraw
void withdraw(Account& account) {

    double amount;

    cout << "Enter amount to withdraw: GBP ";
    cin >> amount;

    if (cin.fail()) {

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Invalid amount.\n";
        return;
    }

    if (amount <= 0) {

        cout << "Amount must be greater than GBP 0.\n";
        return;
    }

    if (amount > account.getBalance()) {

        cout << "Insufficient balance.\n";
        return;
    }

    account.withdraw(amount);

    cout << fixed << setprecision(2);

    cout << "Withdrawal successful.\n";
    cout << "New balance: GBP "
         << account.getBalance() << "\n";
}

    Account* findAccount(vector<Account>& accounts, int accountNumber) {

    for (Account& account : accounts) {

        if (account.getAccountNumber() == accountNumber) {
            return &account;
        }
    }

    return nullptr;
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

int main() {

   vector<Account> accounts;

    accounts.push_back(Account(10001, "Asim", 1000.00, 1234));
    accounts.push_back(Account(10002, "Ahmed", 2000.00, 5678));
    accounts.push_back(Account(10003, "John", 1500.00, 4321));

    int accountNumber;

    cout << "\nEnter account number: ";
    cin >> accountNumber;

    Account* account = findAccount(accounts, accountNumber);

    if (account == nullptr) {
    cout << "Account not found.\n";
    return 0;
    }

    int enteredPin;
    bool authenticated = false;

    for (int attempts = 3; attempts > 0; attempts--) {

        cout << "Enter PIN: ";
        cin >> enteredPin;

        if (account->verifyPin(enteredPin)) {
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


    cout << "Welcome, "
     << account->getAccountHolder()
     << "!\n";

    
    int choice;

    cout << "============================\n";
    cout << "       C++ ATM SYSTEM       \n";
    cout << "============================\n";

    while (true) {

        displayMenu();

        cin >> choice;

        if (cin.fail()) {

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Invalid input. Please enter a number.\n";

            continue;
        }

        if (choice == 1) {

            checkBalance(*account);

        }
        else if (choice == 2) {

            deposit(*account);

        }
        else if (choice == 3) {

            withdraw(*account);

        }

        else if (choice == 4)
            showTransactionHistory(*account);
        
        else if (choice == 5) {

            cout << "\nThank you for using the ATM.\n";
            cout << "Goodbye!\n";

            break;

        }
        else {

            cout << "Invalid choice. Please select 1-4.\n";
        }
    }

    return 0;
}