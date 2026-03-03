#include <fstream>

/*
Задача 1: Напишете функция, която намира големината на файл.
*/

size_t getFileSize(std::ifstream& file)
{
    size_t currPos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(currPos);
    return fileSize;
}
