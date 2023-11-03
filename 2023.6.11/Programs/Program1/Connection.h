#ifndef PROGRAM1_CONNECTION_H
#define PROGRAM1_CONNECTION_H

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32)
/* Windows headers */
#include "ConnectionWindows.h"

#else
/* or check here for unix / linux & fail if OS unrecognized */
#include "ConnectionUnix.h"

#endif /* _WIN32 */

/* for visual studio */
#pragma comment(lib, "ws2_32.lib")

struct Connection
{
private:
    ConnectionOS connectionOS;

public:

    [[nodiscard]] bool connected() const noexcept
    {
        return connectionOS.connected();
    }

    void reconnect()
    {
        connectionOS.reconnect();
    }

    void handleSend(const std::string& data)
    {
        connectionOS.handleSend(data);
    }
};


#endif //PROGRAM1_CONNECTION_H