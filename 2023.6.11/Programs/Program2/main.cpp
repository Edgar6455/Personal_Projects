#include "Connection.h"
#include "SocketException.h"

// Check is received data valid or not, print if valid
void handleData(const std::string& rawData);

int main()
{
    try
    {
        // Initialize connection
        Connection connection;

        std::cout << "Waiting for Program 1 to connect..." << std::endl;
        while (true)
        {
            // If lost connection, try to connect again
            connection.connect();

            while (true)
            {
                // Get the data from Program 1
                std::string rawData;
                rawData = connection.getData();

                // If connection error and invalid data received
                if (rawData.empty())
                    break;

                else
                    handleData(rawData);
            }
        }
    }
    catch (const SocketException& ex)
    {
        std::cerr << "Socket Exception caught: " << ex.what() << std::endl;
    }

    return 0;
}

// Check is received data valid or not, print if valid
void handleData(const std::string& rawData)
{
    // Convert rawData to integer number
    int data = std::stoi(rawData);

    // Check is data valid or not
    if (data % 32 == 0 && data > 99)
        // Valid case
        std::cout << "Received from Program 1: " << data << std::endl;
    else
        // Invalid case
        std::cout << "Received some data from Program 1, but format is not valid."
                  << std::endl;
}