#include <iostream>
#include <iomanip>
#include <limits>
#include "Bank.h"

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

void checkBalance(const Account& account) {
    cout << fixed << setprecision(2);
    cout << "Balance: GBP " << account.getBalance() << "\n";
}

void deposit(Account& account) {
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
        account.deposit(amount);

        cout << "Deposit successful. Balance: GBP "
             << account.getBalance() << "\n";
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void withdraw(Account& account) {
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
        account.withdraw(amount);

        cout << "Withdrawal successful. Balance: GBP "
            << account.getBalance() << "\n";
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

void transferMoney(Account& sender, Bank& bank) {
    int recipientNumber;
    double amount;

    cout << "Enter recipient account number: ";
    cin >> recipientNumber;

    Account* recipient = bank.findAccount(recipientNumber);

    if (recipient == nullptr) {
        cout << "Recipient account not found.\n";
        return;
    }

    if (recipient == &sender) {
        cout << "You cannot transfer to your own account.\n";
        return;
    }

    cout << "Enter amount to transfer: GBP ";
    cin >> amount;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
        return;
}

    try {
        sender.transfer(*recipient, amount);

        cout << "Transfer successful.\n";
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


int main() {

    Bank bank;

    bank.loadAccounts("accounts.txt");

    if (bank.getAccounts().empty()) {
        bank.addAccount(Account(10001, "Asim", 1000, 1234));
        bank.addAccount(Account(10002, "Ahmed", 2000, 5678));
        bank.addAccount(Account(10003, "John", 1500, 4321));
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

    cout << "\nWelcome, "
         << account->getAccountHolder()
         << "!\n";

    int choice;

    while (true) {

        displayMenu();
        cin >> choice;

        if (choice == 1)
            checkBalance(*account);

        else if (choice == 2)
            deposit(*account);

        else if (choice == 3)
            withdraw(*account);

        else if (choice == 4)
            showTransactionHistory(*account);

        else if (choice == 5)
            transferMoney(*account, bank);

        else if (choice == 6) {
        findAccountByMinimumBalance(bank);
    }

        else if (choice == 7) {
        bank.saveAccounts("accounts.txt");
        cout << "Account data saved.\n";
        cout << "Thank you for using the ATM.\n";
        break;
    }

        else
            cout << "Invalid choice.\n";
    }

    return 0;
}