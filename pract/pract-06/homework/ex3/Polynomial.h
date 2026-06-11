#pragma once

#include <cstdio>

class Polynomial
{
    double *coefficients;
    size_t n;

    void free();
    void copyFrom(const Polynomial &);

public:
    explicit Polynomial(size_t n);
    Polynomial(const Polynomial &other);
    Polynomial &operator=(const Polynomial &other);
    ~Polynomial();

    void setCoefficients(const double *coefficients);

    void setCoefficientAt(size_t, double);
    double getCoefficientAt(size_t) const;
    double calculateForX(double) const;
    void print() const;
    static Polynomial createConstant(double);
};
