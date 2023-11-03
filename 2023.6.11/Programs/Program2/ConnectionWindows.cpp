#include "ConnectionWindows.h"
#include "SocketException.h"


/* Private functions */

void ConnectionOS::listenForConnections() const
{
    if (listen(sockfd, 1) == SOCKET_ERROR)
    {
        closesocket(sockfd);
        WSACleanup();
        throw SocketException("Error listening for connections!");
    }
}

void ConnectionOS::bindSocketToAddress() const
{
    Address connectionAddress(AF_INET, 8080, INADDR_ANY);
    if (bind(sockfd, reinterpret_cast<sockaddr*>(&connectionAddress.getAddress()),
             sizeof(connectionAddress.getAddress())) == SOCKET_ERROR)
    {
        closesocket(sockfd);
        WSACleanup();
        throw SocketException("Error binding socket!");
    }
}

void ConnectionOS::createSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        WSACleanup();
        throw SocketException("Error creating socket!");
    }
}

void ConnectionOS::initializeWSA()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw SocketException("Failed to initialize Winsock!");
    }
}

void ConnectionOS::close() const
{
    closesocket(sockfd);
    WSACleanup();
}

void ConnectionOS::initializeConnection()
{
    initializeWSA();
    createSocket();
    bindSocketToAddress();
    listenForConnections();
}


/* Public functions */

void ConnectionOS::connect()
{
    sockaddr_in clientAddr{};
    int clientAddrLen = sizeof(clientAddr);

        clientSockfd = accept(sockfd, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
        if (clientSockfd == INVALID_SOCKET)
        {
            closesocket(sockfd);
            WSACleanup();
            throw SocketException("Error listening for connections!");
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
    int bytesReceived = recv(clientSockfd, buffer, sizeof(buffer), 0);
    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Error receiving data from Program 1. Waiting for Program 1 to connect again..."
                  << std::endl;
        closesocket(clientSockfd);
        return "";
    } else if (bytesReceived == 0) {
        std::cerr << "Connection closed by Program 1. Waiting for Program 1 to connect again..."
                  << std::endl;
        closesocket(clientSockfd);
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