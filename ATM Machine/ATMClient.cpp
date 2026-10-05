#include <iostream>
#include <winsock2.h>
#include <cstring>

int main() {

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed.\n";
        return 1;
    }

    SOCKET clientSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Failed to create client socket.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);

    if (connect(
        clientSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    ) == SOCKET_ERROR) {

        std::cout << "Failed to connect to banking server.\n";

        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to banking server.\n";

    const char* message = "Hello from ATM client.";

    send(
        clientSocket,
        message,
        static_cast<int>(strlen(message)),
        0
    );

    char buffer[1024];

    int bytesReceived = recv(
        clientSocket,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';

        std::cout << "Server response: "
                  << buffer << "\n";
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}