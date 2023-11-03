#ifndef PROGRAM2_CONNECTIONWINDOWS_H
#define PROGRAM2_CONNECTIONWINDOWS_H

#include "SocketException.h"
#include "Address.h"

#include <winsock2.h>
#include <processthreadsapi.h>

#include <iostream>
#include <string>

class ConnectionOS
{
private:
    /* Data members */
    WSAData wsaData{};
    SOCKET sockfd{};
    SOCKET clientSockfd{};
    //Address connectionAddress{};

    /* Private functions */
    void listenForConnections() const;
    void bindSocketToAddress() const;
    void createSocket();
    void initializeWSA();
    void close() const;
    void initializeConnection();

public:
    /* Public functions */
    void connect();
    [[nodiscard]] std::string getData() const;

    /* Constructor / Destructor */
    ConnectionOS();
    ~ConnectionOS();
};


#endif //PROGRAM2_CONNECTIONWINDOWS_H
