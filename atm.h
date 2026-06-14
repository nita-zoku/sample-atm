#pragma once

#include <string>

#include "messaging.h"

class atm
{
    messaging::receiver incoming;
    messaging::sender   bank, interface_hardware;
    void    (atm::*state)();
    std::string account;
    unsigned withdrawal_amount;
    std::string pin;

    void process_withdrawal();
    void process_balance();
    void wait_for_action();
    void verifying_pin();
    void getting_pin();
    void waiting_for_card();
    void done_processing();

    atm(atm const&) = delete;
    atm& operator=(atm const & other) = delete;
public:
    atm(messaging::sender bank_,
        messaging::sender   interface_hardware_):
        bank(bank_), interface_hardware(interface_hardware_)
    {}

    void done();
    void run();

    messaging::sender   get_sender();
};
