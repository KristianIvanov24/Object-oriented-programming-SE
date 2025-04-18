#include <iostream>
#include <fstream>

/*
Задача 3: Напишете програма, която отпечатва собствения си код.
*/

namespace constants
{
    const int BUFF_SIZE = 1024;
}

void selfPrinting()
{
    std::ifstream file("main.cpp");
    if(!file.is_open())
        return;

    while(!file.eof())
    {
        char buff[constants::BUFF_SIZE];
        file.getline(buff, constants::BUFF_SIZE);
        std::cout << buff << std::endl;
    }
}
