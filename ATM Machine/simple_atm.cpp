#include <iostream>
#include <iomanip>
#include <limits>

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

// Check account balance
void checkBalance(double balance) {
    cout << fixed << setprecision(2);
    cout << "Your balance is: GBP " << balance << "\n";
}

// Deposit money
double deposit(double balance) {

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
        return balance;
    }

    if (amount <= 0) {
        cout << "Amount must be greater than GBP 0.\n";
        return balance;
    }

    balance += amount;

    cout << fixed << setprecision(2);
    cout << "Deposit successful.\n";
    cout << "New balance: GBP " << balance << "\n";

    return balance;
}

// Withdraw money
double withdraw(double balance) {

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
        return balance;
    }

    if (amount <= 0) {
        cout << "Amount must be greater than GBP 0.\n";
        return balance;
    }

    if (amount > balance) {
        cout << "Insufficient balance.\n";
        return balance;
    }

    balance -= amount;

    cout << fixed << setprecision(2);
    cout << "Withdrawal successful.\n";
    cout << "New balance: GBP " << balance << "\n";

    return balance;
}

int main() {

    double balance = 1000.00;
    int choice;

    cout << "============================\n";
    cout << "       C++ ATM SYSTEM       \n";
    cout << "============================\n";

    while (true) {

        displayMenu();

        cin >> choice;

        // Validate menu input
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

            checkBalance(balance);

        }
        else if (choice == 2) {

            balance = deposit(balance);

        }
        else if (choice == 3) {

            balance = withdraw(balance);

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