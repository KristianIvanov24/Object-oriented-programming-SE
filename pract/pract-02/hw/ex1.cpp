#include <iostream>

/*
1. Създайте структура, която представя комплексно число. Реализирайте следните функции:

Функция, която връща сбора на 2 комплексни числа.
Функция, която връща произведението на 2 комплексни числа.
Принтиране на комплексно число.
*/

struct Complex
{
    double a;
    double b;
};

Complex sum(const Complex &x, const Complex &y)
{
    return {x.a + y.a, x.b + y.b};
}

Complex mult(const Complex &x, const Complex &y)
{
    double real = x.a * y.a - x.b * y.b;
    double imag = x.a * y.a + x.b * y.b;
    return {real, imag};
}

void printComplex(const Complex &x)
{
    std::cout << x.a;
    if (x.b >= 0)
        std::cout << " + " << x.b << "i";
    else
        std::cout << " - " << -x.b << "i";
}

int main()
{
    Complex x = {2, 3}, y = {3, 4};
    printComplex(sum(x, y));
    std::cout << std::endl;
    printComplex(mult(x, y));

    return 0;
}