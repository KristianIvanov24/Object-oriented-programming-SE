#include <iostream>
#include <fstream>

const size_t MAX_FILE_NAME = 30;

size_t getFileSize(std::ifstream &f)
{
    size_t currentPos = f.tellg();
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();

    f.seekg(currentPos);
    return size;
}

int main()
{
    char fileName[MAX_FILE_NAME];
    std::cin >> fileName;

    std::ifstream in(fileName);
    if (!in.is_open())
    {
        std::cout << "Error!" << std::endl;
        return 1;
    }

    size_t halfSize = getFileSize(in) / 2;
    char* buffer = new char[halfSize + 1];
    
    in.read(buffer, halfSize);
    in.close();

    std::ofstream out(fileName);
    if (!out.is_open())
    {
        std::cout << "Error!" << std::endl;
        return 1;
    }

    out.write(buffer, halfSize);
    out.close();

    delete[] buffer;

    return 0;
}