#include "ConnectionUnix.h"
#include "SocketException.h"


/* Private functions */

void ConnectionOS::listenForConnections() const
{
    if (listen(sockfd, 1) == -1)
    {
        ::close(sockfd);
        throw SocketException("Error listening for connections!");
    }
}

void ConnectionOS::bindSocketToAddress() const
{
    // Initialize connection address
    struct sockaddr_un connectionAddress{};
    unlink("/tmp/my_socket");
    connectionAddress.sun_family = AF_UNIX;
    strcpy(connectionAddress.sun_path, "/tmp/my_socket");

    if (bind(sockfd, (struct sockaddr*)&connectionAddress,
             sizeof(connectionAddress)) == -1)
    {
        ::close(sockfd);
        throw SocketException("Error binding socket!");
    }
}

void ConnectionOS::createSocket()
{
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        throw SocketException("Error creating socket!");
    }
}

void ConnectionOS::close() const
{
    unlink("/tmp/my_socket");
    ::close(sockfd);
}

void ConnectionOS::initializeConnection()
{
    createSocket();
    bindSocketToAddress();
    listenForConnections();
}


/* Public functions */

void ConnectionOS::connect()
{
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);

    clientSockfd = accept(sockfd, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
    if (clientSockfd == -1)
    {
        ::close(sockfd);
        throw SocketException("Connection error!");
    }
    else
    {
        std::cout << "Program 1 connected!" << std::endl;
    }
}

std::string ConnectionOS::getData() const
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesReceived = recv(clientSockfd, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1)
    {
        std::cerr << "Error receiving data from Program 1. Waiting for Program 1 to connect again..."
                  << std::endl;
        ::close(clientSockfd);
        return "";
    }
    else if (bytesReceived == 0)
    {
        std::cerr << "Connection closed by Program 1. Waiting for Program 1 to connect again..."
                  << std::endl;
        ::close(clientSockfd);
        return "";
    }

    std::string s1 = buffer;
    return s1;
}


/* Constructor / Destructor */

ConnectionOS::ConnectionOS()
{
    initializeConnection();
}

ConnectionOS::~ConnectionOS()
{
    close();
}
