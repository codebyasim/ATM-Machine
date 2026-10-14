#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed.\n";
        return 1;
    }

    int accountNumber, pin;

    std::cout << "============================\n";
    std::cout << "       ATM CLIENT MENU      \n";
    std::cout << "============================\n";

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    std::cout << "Enter PIN: ";
    std::cin >> pin;

    int choice;

    while (true) {
        std::cout << "\n1. Check Balance\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw (not implemented)\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        if (choice == 4) {
            std::cout << "Thank you for using the ATM.\n";
            break;
        }

        std::string request;

        if (choice == 1) {
            request = "BALANCE " +
                std::to_string(accountNumber) + " " +
                std::to_string(pin);
        }
        else if (choice == 2) {
            double amount;

            std::cout << "Enter deposit amount: GBP ";
            std::cin >> amount;

            if (!std::cin || amount <= 0) {
                std::cout << "Invalid amount.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            request = "DEPOSIT " +
                std::to_string(accountNumber) + " " +
                std::to_string(pin) + " " +
                std::to_string(amount);
        }
        else if (choice == 3) {
            std::cout << "Withdrawal is not implemented "
                         "in the network server yet.\n";
            continue;
        }
        else {
            std::cout << "Invalid choice.\n";
            continue;
        }

        SOCKET clientSocket = socket(
            AF_INET, SOCK_STREAM, IPPROTO_TCP
        );

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Failed to create socket.\n";
            break;
        }

        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        inet_pton(AF_INET, "127.0.0.1",
                  &serverAddress.sin_addr);

        if (connect(
            clientSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)
        ) == SOCKET_ERROR) {
            std::cout << "Failed to connect to server.\n";
            closesocket(clientSocket);
            continue;
        }

        int sent = send(
            clientSocket,
            request.c_str(),
            static_cast<int>(request.length()),
            0
        );

        if (sent == SOCKET_ERROR) {
            std::cout << "Failed to send request.\n";
            closesocket(clientSocket);
            continue;
        }

        char buffer[1024];

        int received = recv(
            clientSocket, buffer,
            sizeof(buffer) - 1, 0
        );

        if (received > 0) {
            buffer[received] = '\0';
            std::cout << "Server response: "
                      << buffer << "\n";
        }
        else {
            std::cout << "No response received.\n";
        }

        closesocket(clientSocket);
    }

    WSACleanup();
    return 0;
}
