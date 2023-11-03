#ifndef PROGRAM2_CONNECTIONUNIX_H
#define PROGRAM2_CONNECTIONUNIX_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>

#include <iostream>
#include <string>
#include <cstring>

class ConnectionOS
{
private:
    /* Data members */
    int sockfd{};
    int clientSockfd{};

    /* Private functions */
    void listenForConnections() const;
    void bindSocketToAddress() const;
    void createSocket();
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


#endif //PROGRAM2_CONNECTIONUNIX_H
