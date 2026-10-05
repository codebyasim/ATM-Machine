#ifndef BANKING_SERVER_H
#define BANKING_SERVER_H

#include "BankService.h"
#include <winsock2.h>

class BankingServer {

private:
    BankService& bankService;
    SOCKET serverSocket;

public:
    BankingServer(BankService& bankService);

    void start();
};

#endif