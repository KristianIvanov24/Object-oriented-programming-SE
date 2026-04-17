#include <iostream>
#include "Rational.h"

int main() {
    Rational a(3, 4);
    Rational b(5, 6);

    Rational c = a + b;
    Rational d = a * b;
    Rational e = a - b;
    Rational f = a / b;
    Rational g = a++;
    Rational h = ++a;

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "a + b = " << c << "\n";
    std::cout << "a - b = " << e << "\n";
    std::cout << "a * b = " << d << "\n";
    std::cout << "a / b = " << f << "\n";
    std::cout << "a++ = " << g << "\n";
    std::cout << "++a = " << h << "\n";

    Rational x;
    std::cin >> x;
    x += a;
    std::cout << "Entered: " << x << "\n";

    if (a >= b) {
        std::cout << "a >= b";
    }
    else std::cout << "a < b";

    return 0;
}