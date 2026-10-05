#include "BankingServer.h"
#include <iostream>

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

    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Failed to create server socket.\n";
        WSACleanup();
        return;
    }

    std::cout << "Banking server socket created.\n";
}