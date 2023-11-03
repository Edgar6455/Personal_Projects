#ifndef PROGRAM1_CONNECTIONUNIX_H
#define PROGRAM1_CONNECTIONUNIX_H

//#include "Connection.h"
#include "SocketException.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/poll.h>

#include <iostream>
#include <string>

class Connection;

class ConnectionOS
{
private:
    /* Data members */
    int sockfd{};
    bool isConnected{};
    struct sockaddr_un program2{};

    /* Private functions */
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


#endif //PROGRAM1_CONNECTIONUNIX_H