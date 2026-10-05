#ifndef BANKING_SERVER_H
#define BANKING_SERVER_H

#include "BankService.h"
#include <winsock2.h>
#include <mutex>

class BankingServer {

private:
    BankService& bankService;
    SOCKET serverSocket;
    std::mutex bankMutex;   

public:
    BankingServer(BankService& bankService);

    void start();
};

#endif