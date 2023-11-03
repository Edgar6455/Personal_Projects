#include "ConnectionUnix.h"


/* Private functions */

void ConnectionOS::createSocket()
{
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        throw SocketException("Failed to create socket!");
    }
}

void ConnectionOS::connectToProgram2()
{
    if (connect(sockfd, (struct sockaddr*)(&program2),
                sizeof(program2)) == -1)
    {
        ::close(sockfd);
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
    createSocket();
}

void ConnectionOS::close() const
{
    ::close(sockfd);
}


/* Public functions */

void ConnectionOS::reconnect()
{
    ::close(sockfd);
    createSocket();
    connectToProgram2();
}

bool ConnectionOS::connected() const
{
    return isConnected;
}

void ConnectionOS::handleSend(const std::string &message)
{
    struct pollfd pollfds[1];
    pollfds[0].fd = sockfd;
    pollfds[0].events = POLLOUT | POLLHUP | POLLERR;

    int ready = poll(pollfds, 1, -1); // Wait indefinitely until an event occurs
    if (ready == -1)
    {
        throw SocketException("Error polling response!");
    }

    // Socket has an event, check for send readiness or disconnection
    if (pollfds[0].revents & POLLHUP)
    {
        std::cerr << "Program 2 disconnected! Not sent!" << std::endl;
        isConnected = false;
    }
    else if (pollfds[0].revents & POLLERR)
    {
        throw SocketException("Failed to create socket!");
    }
    else if (pollfds[0].revents & POLLOUT)
    {
        // Socket is ready for sending
        ssize_t bytesSent = send(sockfd, message.c_str(), message.size(), 0);
        if (bytesSent == -1)
        {
            std::cerr << "Program 2 disconnected! Not sent!" << std::endl;
            isConnected = false;
        }
        else
        {
            std::cout << "Sent!" << std::endl;
        }
    }
}


/* Constructor / Destructor */

ConnectionOS::ConnectionOS()
{
    initializeConnection();
    isConnected = false;
    program2.sun_family = AF_UNIX;
    strcpy(program2.sun_path, "/tmp/my_socket");
}

ConnectionOS::~ConnectionOS()
{
    close();
}
