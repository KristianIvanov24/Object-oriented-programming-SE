#pragma once
#include <cstddef>

class Vector
{
    double* coords;
    size_t dimension;

public:
    Vector();
    Vector(size_t dimension);
    Vector(const double* coords, size_t dimension);

    Vector(const Vector& other);
    Vector(Vector&& other);

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);

    size_t getDimension() const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);
    
    double operator[](size_t index) const;
    double& operator[](size_t index);
    operator bool() const;
    
    friend bool operator==(const Vector& lhs, const Vector& rhs);
    friend bool operator!=(const Vector& lhs, const Vector& rhs);

    ~Vector();

private:
    void setData(const double* coords, size_t dimension);
    void upsizeDimension(size_t newDimension);
    void arithmeticHelper(const Vector& other, double (*op)(double lhs, double rhs));

    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other);
    void free();
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(const Vector& lhs, double scalar);
Vector operator*(double scalar, const Vector& rhs);
Vector operator/(const Vector& lhs, double scalar);