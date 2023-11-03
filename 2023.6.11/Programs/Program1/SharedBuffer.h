#ifndef PROGRAM1_SHAREDBUFFER_H
#define PROGRAM1_SHAREDBUFFER_H

#include <mutex>
#include <regex>
#include <string>
#include <condition_variable>

class SharedBuffer
{
private:
    std::string buffer;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void updateBufferState()
    {
        cv.notify_one();
    }

    void waitForBuffer()
    {
        std::unique_lock<std::mutex> ul(mtx);
        cv.wait(ul, [&]{ return !buffer.empty(); });
    }

    void waitForEmptyBuffer()
    {
        std::unique_lock<std::mutex> ul(mtx);
        cv.wait(ul, [&]{ return buffer.empty(); });
    }

    std::string readFromBuffer()
    {
        std::string s = buffer;
        buffer.clear();
        return s;
    }

    void writeToBuffer(std::string data)
    {
        buffer = data;
    }

};

#endif //PROGRAM1_SHAREDBUFFER_H