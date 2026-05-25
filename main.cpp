#include "Polynomial.h"
#include <iostream>

int main() {
    Polynomial p(3);
    p.setCoefficients(0, 2);
    p.setCoefficients(1, 3);
    p.setCoefficients(2, 0);
    p.setCoefficients(3, 5);

    p.print();                                     
    std::cout << "P(2) = " << p.evaluate(2) << "\n"; 

    Polynomial constant = Polynomial::createConstant(7.0);
    constant.print();
}