#include "ConnectionWindows.h"

/* Private functions */

void ConnectionOS::initializeWSA()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw SocketException("Failed to initialize Winsock!");
    }
}

void ConnectionOS::createSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        WSACleanup();
        throw SocketException("Failed to create socket!");
    }
}

void ConnectionOS::connectToProgram2()
{

    if (connect(sockfd, reinterpret_cast<sockaddr*>(&connectionAddress.getAddress()),
                sizeof(connectionAddress.getAddress())) == SOCKET_ERROR)
    {
        closesocket(sockfd);
        isConnected = false;
        std::cerr << "Could not connect to Program 2!" << std::endl;
    }
    else
    {
        isConnected = true;
        std::cout << "Connected to Program 2!" << std::endl;
    }
}

void ConnectionOS::initializeConnection()
{
    initializeWSA();
    createSocket();
}

void ConnectionOS::close() const
{
    closesocket(sockfd);
    WSACleanup();
}


/* Public functions */

void ConnectionOS::reconnect()
{
    closesocket(sockfd);
    createSocket();
    connectToProgram2();
}

bool ConnectionOS::connected() const
{
    return isConnected;
}

void ConnectionOS::handleSend(const std::string &message)
{
    std::vector<WSAPOLLFD> pollSockets(1);
    pollSockets[0].fd = sockfd;
    pollSockets[0].events = POLLHUP;

    if (WSAPoll(pollSockets.data(), pollSockets.size(), 0) > 0
            && pollSockets[0].revents & POLLHUP)
    {
        std::cerr << "Program 2 disconnected!" << std::endl;
        isConnected = false;
        return;
    }
    int bytesSent = send(sockfd, message.c_str(), message.size(), 0);
    if (bytesSent == SOCKET_ERROR || bytesSent == 0)
    {
        std::cerr << "Error sending data to Program 2!" << std::endl;
        isConnected = false;
    }
    else
        std::cout << "Sent! " << std::endl;
}


/* Constructor / Destructor */

ConnectionOS::ConnectionOS()
{
    initializeConnection();
    isConnected = false;

    // Initialize connection address
    Address address(AF_INET, 8080, INADDR_LOOPBACK);
    connectionAddress = address;
}

ConnectionOS::~ConnectionOS()
{
    close();
}
