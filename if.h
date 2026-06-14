#pragma once

#include <mutex>

#include "messaging.h"

class interface_machine
{
    messaging::receiver incoming;
    std::mutex iom;
public:
    void done();
    messaging::sender   get_sender();
    void run();
};
