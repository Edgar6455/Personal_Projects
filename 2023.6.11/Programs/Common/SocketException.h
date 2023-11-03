#ifndef PROGRAM1_SOCKETEXCEPTION_H
#define PROGRAM1_SOCKETEXCEPTION_H

#include <stdexcept>
#include <string>

class SocketException : public std::exception {
private:
    std::string error_message_;

public:
    explicit SocketException(const std::string& error_message) :
            error_message_(error_message) {}

    const char* what() const noexcept override
    {
        return error_message_.c_str();
    }
};

#endif //PROGRAM1_SOCKETEXCEPTION_H