#include <iostream>
using namespace std;

int main() {
    double balance = 1000.0;   // Starting balance
    int choice;
    double amount;

    cout << "=== Simple ATM ===\n";

    while (true) {
        // ATM Menu
        cout << "\n1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            // Show balance
            cout << "Your balance is: £" << balance << "\n";
        }
        else if (choice == 2) {
            // Deposit money
            cout << "Enter amount to deposit: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!\n";
            } else {
                balance += amount;
                cout << "Deposit successful. New balance: £" << balance << "\n";
            }
        }
        else if (choice == 3) {
            // Withdraw money
            cout << "Enter amount to withdraw: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!\n";
            } else if (amount > balance) {
                cout << "Insufficient balance!\n";
            } else {
                balance -= amount;
                cout << "Withdrawal successful. New balance: £" << balance << "\n";
            }
        }
        else if (choice == 4) {
            // Exit
            cout << "Thank you for using the ATM. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
