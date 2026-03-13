#include <iostream>
#include <fstream>

void decipher(std::ifstream &file, std::ifstream &keyFile)
{
    if (!file || !keyFile)
    {
        std::cout << "Can't open file!" << std::endl;
        return;
    }

    unsigned char key;
    keyFile.read((char *)&key, sizeof(key));

    unsigned number;
    while (file.read((char *)&number, sizeof(number)))
    {
        unsigned result = number + key;
        std::cout << result << " ";
    }
    std::cout << std::endl;
}