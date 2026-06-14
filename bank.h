#pragma once

#include "messaging.h"

class bank_machine
{
    messaging::receiver incoming;
    unsigned balance;
public:
    bank_machine():
        balance(199)
    {}

    void done();
    void run();
    messaging::sender   get_sender();
};
