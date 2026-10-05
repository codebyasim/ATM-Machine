#ifndef BANKING_SERVER_H
#define BANKING_SERVER_H

#include "BankService.h"

class BankingServer {

private:
    BankService& bankService;

public:
    BankingServer(BankService& bankService);

    void start();
};

#endif