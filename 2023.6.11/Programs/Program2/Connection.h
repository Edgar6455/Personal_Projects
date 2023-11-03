#ifndef PROGRAM2_CONNECTION_H
#define PROGRAM2_CONNECTION_H

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

    void connect()
    {
        connectionOS.connect();
    }

    std::string getData()
    {
        return connectionOS.getData();
    }
};



#endif //PROGRAM2_CONNECTION_H
