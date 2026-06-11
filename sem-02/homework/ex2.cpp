#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

namespace constants
{
    const char *ERROR = "[ERROR]";
    const char *INFO = "[INFO]";
    const char *INPUT = "input";
    const char *SHOW_ERRORS = "show_errors";
    const char *FILE_NAME = "logs.bin";
    const char *LAST_POS_FILE = "last_read_position.bin";
    const size_t BUFFER_SIZE = 1024;
}

enum class Type
{
    ERROR,
    INFO
};

struct Log
{
    Type type;
    size_t length;
};

void saveLog(Type type, const char *text)
{
    std::ofstream file(constants::FILE_NAME, std::ios::binary | std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }

    Log log;
    log.type = type;
    log.length = strlen(text);

    file.write((const char *)&log, sizeof(log));
    file.write(text, log.length);
    file.close();
}

void saveLastPosition(size_t pos)
{
    std::ofstream file(constants::LAST_POS_FILE, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }

    file.write((const char *)&pos, sizeof(pos));
    file.close();
}

size_t loadLastPosition()
{
    std::ifstream file(constants::LAST_POS_FILE, std::ios::binary);
    if (!file.is_open())
    {
        return 0;
    }

    size_t pos;
    file.read((char *)&pos, sizeof(pos));
    file.close();
    return pos;
}

void showErrors()
{
    std::ifstream file(constants::FILE_NAME, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }

    size_t pos = loadLastPosition();
    file.seekg(pos);

    bool newErrorFound = false;
    Log log;

    while (file.read((char *)&log, sizeof(log)))
    {
        char* buffer = new char[log.length + 1];
        file.read(buffer, log.length);
        buffer[log.length] = '\0';

        if (log.type == Type::ERROR)
        {
            std::cout << constants::ERROR << " " << buffer << std::endl;
            newErrorFound = true;
        }
        delete[] buffer;
    }

    saveLastPosition(file.tellg());
    if (!newErrorFound)
    {
        std::cout << "Nothing new to be shown!" << std::endl;
    }
}

void readLog()
{
    std::string line;
    while (true)
    {
        std::getline(std::cin, line);

        if (strncmp(line.c_str(), constants::ERROR, strlen(constants::ERROR)) == 0)
        {
            saveLog(Type::ERROR, line.c_str() + strlen(constants::ERROR) + 1);
        }
        else if (strncmp(line.c_str(), constants::INFO, strlen(constants::INFO)) == 0)
        {
            saveLog(Type::INFO, line.c_str() + strlen(constants::INFO) + 1);
        }
        else
        {
            break;
        }
    }
}

int main()
{
    char command[constants::BUFFER_SIZE];
    while (true)
    {
        std::cin >> command;
        std::cin.ignore();

        if (strcmp(command, constants::INPUT) == 0)
        {
            readLog();
        }
        else if (strcmp(command, constants::SHOW_ERRORS) == 0)
        {
            showErrors();
        }
        else
        {
            break;
        }
    }

    return 0;
}