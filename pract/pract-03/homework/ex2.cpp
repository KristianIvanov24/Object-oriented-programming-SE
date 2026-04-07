#include <iostream>
#include <fstream>

void fun(const char *input, const char *output)
{
    std::ifstream in(input);
    std::ofstream out(output);
    if (!in.is_open() || !out.is_open())
    {
        std::cout << "Error!" << std::endl;
        return;
    }

    int a, b;
    in >> a >> b;

    out << a + b << " " << a * b;

    in.close();
    out.close();
}