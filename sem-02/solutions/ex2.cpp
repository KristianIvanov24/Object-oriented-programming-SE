#include <fstream>

/*
Задача 2: Напишете функция, която приема име на съществуващ файл и връща броя на редовете в него.
*/

unsigned getCharCountFromFile(std::ifstream& file, char ch)
{
    size_t currPos = file.tellg();
    file.seekg(0, std::ios::beg);

    unsigned count = 0;

    while(true)
    {
        char curr = file.get();

        if(file.eof())
            break;

        if(curr == ch)
            count++;
    }

    file.clear(); // eofbit is true and we need to clear the bits
    file.seekg(currPos);

    return count;
}

unsigned countFileLines(const char* filename)
{
    if(!filename)
        return 0;
    
    std::ifstream file(filename);
    
    if(!file.is_open())
        return 0;

    unsigned result = getCharCountFromFile(file, '\n') + 1;

    file.close();

    return result;
}
