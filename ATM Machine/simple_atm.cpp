#include <iostream>
#include <iomanip>
#include <limits>
#include "Account.h"

using namespace std;

// Display ATM menu
void displayMenu() {

    cout << "\n----- ATM MENU -----\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Exit\n";
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

int main() {

    Account account(1000.00);

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

            checkBalance(account);

        }
        else if (choice == 2) {

            deposit(account);

        }
        else if (choice == 3) {

            withdraw(account);

        }
        else if (choice == 4) {

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