#ifndef PROGRAM1_CONNECTIONWINDOWS_H
#define PROGRAM1_CONNECTIONWINDOWS_H

#include <SocketException.h>
#include <Address.h>

#include <winsock2.h>
#include <processthreadsapi.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>
#include <vector>

class Connection;

class ConnectionOS
{
private:
    /* Data members */
    WSAData wsaData{};
    SOCKET sockfd{};
    bool isConnected;
    Address connectionAddress{};

    /* Private functions */
    void initializeWSA();
    void createSocket();
    void connectToProgram2();
    void initializeConnection();
    void close() const;

public:
    /* Public functions */
    void reconnect();
    [[nodiscard]] bool connected() const;
    void handleSend(const std::string& message);

    /* Constructor / Destructor */
    ConnectionOS();
    ~ConnectionOS();
};


#endif //PROGRAM1_CONNECTIONWINDOWS_H
