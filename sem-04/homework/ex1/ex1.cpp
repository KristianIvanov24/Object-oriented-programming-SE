#include <iostream>
#include "KBaseNumber.h"

int main()
{
    KBaseNumber num1("CE9A", 16);
    num1.print();
    num1.printConvertedTo(8);

    KBaseNumber num2("147232", 8);
    std::cout << num1.compareWith(num2) << std::endl;

    num2.update("1312", 4);
    std::cout << num2.compareWith(num1) << std::endl;

    return 0;
}