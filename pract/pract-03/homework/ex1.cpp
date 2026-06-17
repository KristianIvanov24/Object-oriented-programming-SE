#include <iostream>
#include <fstream>

const size_t MAX_FILE_NAME = 50;
const size_t BUFFER_SIZE = 1024;

int main()
{
    char fileName[MAX_FILE_NAME];
    std::cin >> fileName;

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error!" << std::endl;
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (file.getline(buffer, BUFFER_SIZE))
    {
        std::cout << buffer << std::endl;
    }

    file.close();
    return 0;
}