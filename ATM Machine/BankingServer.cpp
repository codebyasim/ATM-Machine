#include "BankingServer.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <sstream>

BankingServer::BankingServer(BankService& bankService)
    : bankService(bankService), serverSocket(INVALID_SOCKET)
{
}

void BankingServer::start() {

    // Start Windows socket system
    WSADATA wsaData;

    int result = WSAStartup(
        MAKEWORD(2, 2),
        &wsaData
    );

    if (result != 0) {
        std::cout << "WSAStartup failed.\n";
        return;
    }

    // Create TCP socket
    serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // bind provide ip address and connect it to port number
    if (bind(
        serverSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    ) == SOCKET_ERROR) {

    std::cout << "Failed to bind server socket.\n";

    closesocket(serverSocket);
    WSACleanup();
    return;
}

    std::cout << "Server bound to port 8080.\n";   
    
    // Listen for ATM clients
if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
    std::cout << "Failed to listen on port 8080.\n";

    closesocket(serverSocket);
    WSACleanup();
    return;
}

std::cout << "Banking server is listening on port 8080.\n";

// Accept multiple client requests
while (true) {

    SOCKET clientSocket = accept(
        serverSocket,
        nullptr,
        nullptr
    );

    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Failed to accept client.\n";
        continue;
    }


    std::thread clientThread([this, clientSocket]() {

        std::lock_guard<std::mutex> lock(bankMutex);

        char buffer[1024];

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';

            std::string request(buffer);

            std::stringstream ss(request);

            std::string command;
            int accountNumber;
            int pin;

            ss >> command >> accountNumber;
            
            if (command == "BALANCE") {
            Account* account = bankService.login(accountNumber, 0);
}

            std::cout << "Request: "
                << request << "\n";

            std::cout << "Received from ATM: "
                      << buffer << "\n";

            const char* response =
                "Request received by banking server.";

            send(
                clientSocket,
                response,
                static_cast<int>(strlen(response)),
                0
            );
        }

        closesocket(clientSocket);
    });

    clientThread.detach();
}



    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Failed to create server socket.\n";
        WSACleanup();
        return;
    }

    std::cout << "Banking server socket created.\n";
}