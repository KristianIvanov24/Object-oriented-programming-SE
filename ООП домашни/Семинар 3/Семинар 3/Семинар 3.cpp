#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#pragma disable (warning:4996)

namespace constants
{
    const char MAIN_LOG_FILE_NAME[] = "logs.bin";
    const char LAST_POSITION_FILE_NAME[] = "last_read_position.bin";
    const size_t MAX_LOG_TYPE_SIZE = 8;
    const size_t BUFF_SIZE = 1024;
    const char ERROR_LOG_TYPE[] = "[ERROR]";
};

struct Log
{
    char logType[constants::MAX_LOG_TYPE_SIZE];
    char* logMessage;
};

void printLog(const Log& log)
{
    std::cout << log.logType << " " << log.logMessage;
}

void serialiseLog(std::ofstream& ofs, const char logType[], const char logMessage[])
{
    if (!ofs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    size_t messageSize = strlen(logMessage);
    ofs.write((const char*)&messageSize, sizeof(size_t));

    ofs.write(logType, constants::MAX_LOG_TYPE_SIZE);
    
    ofs.write(logMessage, messageSize);
}

Log deserialiseLog(std::ifstream& ifs)
{
    if (!ifs.is_open())
    {
        std::cout << "Error when opening file\n";
        return {};
    }

    Log log;
    size_t messageSize;
    ifs.read((char*)&messageSize, sizeof(size_t));

    ifs.read(log.logType, constants::MAX_LOG_TYPE_SIZE);

    log.logMessage = new char[messageSize + 1];
    ifs.read(log.logMessage, messageSize);
    log.logMessage[messageSize] = '\0';

    return log;
}

void input(const unsigned logCount)
{
    char logType[constants::MAX_LOG_TYPE_SIZE];
    char buff[constants::BUFF_SIZE];

    std::ofstream ofs(constants::MAIN_LOG_FILE_NAME, std::ios::binary | std::ios::app);
    if (!ofs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    for (size_t i = 0; i < logCount; i++)
    {
        std::cin >> logType;
        std::cin.ignore();
        std::cin.getline(buff, constants::BUFF_SIZE);

        serialiseLog(ofs, logType, buff);
    }

    ofs.close();
}

size_t getLastReadPosition(std::ifstream& ifs)
{
    size_t lrp;
    ifs.read((char*)&lrp, sizeof(int));

    return lrp;
}

size_t getFileSize(std::ifstream& ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(0, currentPos);

    return size;
}

void updateLastReadPosition(const int newPos)
{
    std::ofstream ofs(constants::LAST_POSITION_FILE_NAME, std::ios::binary);

    ofs.write((const char*)&newPos, sizeof(int));
    ofs.close();
}


void showErrors()
{
    std::ifstream ifs(constants::MAIN_LOG_FILE_NAME, std::ios::binary);
    std::ifstream lastReadPosIfs(constants::LAST_POSITION_FILE_NAME, std::ios::binary);

    if (!ifs.is_open() || !lastReadPosIfs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    size_t lastReadPosition = getLastReadPosition(lastReadPosIfs);

    size_t fileSize = getFileSize(ifs);
    if (lastReadPosition == fileSize)
    {
        std::cout << "Nothing new to be shown.\n";
        return;
    }

    ifs.clear();
    ifs.seekg(lastReadPosition);
    while (ifs.tellg() < fileSize)
    {
        Log log = deserialiseLog(ifs);
        if (strcmp(log.logType, constants::ERROR_LOG_TYPE) == 0)
        {
            printLog(log);
            std::cout << '\n';
        }

        delete[] log.logMessage;
        log.logMessage = nullptr;
    }

    ifs.close();
    lastReadPosIfs.close();
    updateLastReadPosition(fileSize);
}

int main()
{
    //updateLastReadPosition(0);
    
    int command;
    while (true)
    {
        std::cout << "\n1. Input logs" << '\n' << "2. Show errors" << '\n' << "3. End program\n";
        std::cout << "Enter a command: ";
        std::cin >> command;
        switch (command)
        {
            case 1:
                std::cout << "Enter log count: ";

                unsigned logCount;
                std::cin >> logCount;
                input(logCount);
                break;
            case 2:
                showErrors();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Enter a valid command";
                break;
        }
    }

    return 0;
}