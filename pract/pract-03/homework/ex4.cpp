#include <iostream>
#include <fstream>

bool isWhitespace(char c)
{
    return c == ' ' || c == '\n' || c == '\t';
}

int *wc(const char *fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error" << std::endl;
        return nullptr;
    }

    int *count = new int[3]{};
    char c;
    bool inWord = false;

    while (file.get(c))
    {
        if (c == '\n')
        {
            count[0]++;
        }
        count[2]++;

        if (isWhitespace(c))
        {
            inWord = false;
        }
        else
        {
            if (!inWord)
            {
                count[1]++;
                inWord = true;
            }
        }
    }

    return count;
}