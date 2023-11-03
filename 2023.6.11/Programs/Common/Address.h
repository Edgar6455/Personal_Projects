#ifndef PROGRAM1_ADDRESS_H
#define PROGRAM1_ADDRESS_H

#include "ConnectionWindows.h"
#include <winsock2.h>

struct Address
{
    sockaddr_in connectionAddress{};

    Address() = default;

    Address(short family, u_short port, unsigned long hostValue)
    {
        connectionAddress.sin_family = family;
        connectionAddress.sin_port = htons(port);
        connectionAddress.sin_addr.s_addr = htonl(hostValue);
    }

    sockaddr_in& getAddress()
    {
        return connectionAddress;
    }
};

#endif //PROGRAM1_ADDRESS_H