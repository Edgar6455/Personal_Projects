#include "Connection.h"
#include "SharedBuffer.h"
#include <SocketException.h>

#include <thread>
#include <vector>
#include <regex>


// Calculate the sum of the numbers in the given string
int calculateSum(const std::string& codedData);

// Sort the given string and replace all even numbers by symbols "KB"
std::string sortAndReplace(std::string userInput);

// Return false, if length is more than 64 and there are not only numbers
bool userInputIsValid(const std::string& userInput);


void secondThread(SharedBuffer& sharedBuffer)
{
    try
    {
        // Initialize connection
        Connection connection;

        while(true)
        {
            // Wait until there is data in the buffer
            sharedBuffer.waitForBuffer();

            // Get data from buffer. Quit if it's "/exit", else print
            std::string codedData = sharedBuffer.readFromBuffer();
            if (codedData == "/exit")
                break;

            std::cout << "Coded data is: " << codedData << std::endl;

            // Calculate the sum of the numbers in the given string
            int sum = calculateSum(codedData);

            // If connection lost, reconnect
            if (!connection.connected())
                connection.reconnect();

            // Send data to Program 2
            connection.handleSend(std::to_string(sum));

            // Notify thread 1 to get new user input after handling current
            sharedBuffer.updateBufferState();
        }
    }
    catch (const SocketException& ex)
    {
        std::cerr << "Socket Exception caught: " << ex.what() << std::endl;
    }
}


int main()
{
    // Shared buffer logic with mutexes to synchronize threads
    SharedBuffer sharedBuffer;

    // Run second thread
    std::thread second(secondThread, std::ref(sharedBuffer));

    while (true)
    {
        // Wait for thread 2 to handle buffer data, then receive new
        sharedBuffer.waitForEmptyBuffer();

        // Get user input
        std::string userInput;
        std::cout << std::endl <<
                  "Type data to send to Program 2 (or '/exit' to quit):"
                  << std::endl;
        std::getline(std::cin, userInput);

        // Handle user input
        if (userInput == "/exit")
        {
            sharedBuffer.writeToBuffer("/exit");
            sharedBuffer.updateBufferState();
            break;
        }

        // Check if user input is valid
        if (!userInputIsValid(userInput))
        {
            std::cerr << "Invalid input! Data must contain only numbers and"
                         " maximum 64 characters!" << std::endl;
            continue;
        }

        // Sort the given string and replace all even numbers by symbols "KB"
        std::string readyData = sortAndReplace(userInput);

        // Write the given data to the buffer and update buffer state
        sharedBuffer.writeToBuffer(readyData);
        sharedBuffer.updateBufferState();
    }

    // Exit thread 2
    second.join();

    return 0;
}



// Return false, if length is more than 64 and there are not only numbers
bool userInputIsValid(const std::string& userInput)
{
    std::regex onlyNumbersAndNotLong("^[0-9]{1,64}$");

    return std::regex_match(userInput, onlyNumbersAndNotLong);
}

// Sort the given string and replace all even numbers by symbols "KB"
std::string sortAndReplace(std::string userInput)
{
    // Sort the given string in descending order
    std::sort(userInput.begin(), userInput.end(), std::greater<int>());

    // Copy in this user input, but replace all even numbers by symbols "KB"
    std::vector<char> charVector;
    charVector.reserve(128);

    for (const auto& it : userInput)
    {
        if (it % 2 == 0)
        {
            charVector.push_back('K');
            charVector.push_back('B');
        }
        else
        {
            charVector.push_back(it);
        }
    }

    // Convert char vector to string
    std::string readyData(charVector.begin(), charVector.end());

    return readyData;
}

// Calculate the sum of the numbers in the given string
int calculateSum(const std::string& codedData)
{
    int sum = 0;
    for (const auto& it : codedData)
    {
        if (it == 'K' || it == 'B')
            continue;
        sum += it - '0';
    }
    return sum;
}