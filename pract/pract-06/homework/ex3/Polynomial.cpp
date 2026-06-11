#include "Polynomial.h"
#include "constants.h"

#include <algorithm>
#include <iostream>

void Polynomial::free()
{
    delete[] coefficients;
    coefficients = nullptr;
    n = constants::DEFAULT_MIN;
}

void Polynomial::copyFrom(const Polynomial &other)
{
    n = other.n;
    setCoefficients(other.coefficients);
}

Polynomial::Polynomial(size_t n)
{
    this->n = n;
    coefficients = new double[n + 1]{};
}

Polynomial::Polynomial(const Polynomial &other)
{
    copyFrom(other);
}

Polynomial &Polynomial::operator=(const Polynomial &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Polynomial::~Polynomial()
{
    free();
}

void Polynomial::setCoefficients(const double *coefficients)
{
    if (!coefficients) {
        this->coefficients = nullptr;
        n = constants::DEFAULT_MIN;
        return;
    }
    delete[] this->coefficients;
    this->coefficients = new double[n + 1];
    for (size_t i = 0; i <= n; i++)
    {
        this->coefficients[i] = coefficients[i];
    }
}

void Polynomial::setCoefficientAt(size_t index, double coefficient)
{
    if (index > n)
        return;
    coefficients[index] = coefficient;
}

double Polynomial::getCoefficientAt(size_t index) const
{
    if (index > n)
        return 0;
    return coefficients[index];
}

double Polynomial::calculateForX(double x) const
{
    double res = 0;
    double xi = 1;
    for (size_t i = 0; i <= n; i++)
    {
        res += coefficients[i] * xi;
        xi *= x;
    }
    return res;
}

void Polynomial::print() const
{
    if (n == 0 || coefficients == nullptr)
    {
        std::cout << "0" << std::endl;
        return;
    }

    bool first = true;
    for (size_t i = 0; i <= n; i++)
    {
        double coefficient = coefficients[i];
        if (coefficient == 0)
            continue;
        if (!first)
        {
            std::cout << (coefficient < 0 ? " - " : " + ");
        }

        coefficient = std::abs(coefficient);
        if (i == 0 || coefficient != 1)
        {
            std::cout << coefficient;
        }

        if (i > 0)
        {
            std::cout << "x";
            if (i > 1)
                std::cout << "^" << i;
        }

        first = false;
    }
    if (first)
        std::cout << "0";

    std::cout << std::endl;
}

Polynomial Polynomial::createConstant(double y)
{
    Polynomial res(0);
    res.coefficients[0] = y;
    return res;
}
