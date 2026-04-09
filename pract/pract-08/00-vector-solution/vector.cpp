#include "vector.h"
#include "arrayUtils.h"
#include "resources.h"
#include <utility>

Vector::Vector()
{
    setData(resources::vector::DEFAULT_COORDS, resources::vector::DEFAULT_DIMENSION);
}

Vector::Vector(size_t dimension)
{
    double* coords = new double[dimension];
    for (size_t i = 0; i < dimension; i++)
    {
        coords[i] = resources::vector::DEFAULT_VALUE;
    }
    setData(coords, dimension);
    delete[] coords;
}

Vector::Vector(const double* coords, size_t dimension)
{
    setData(coords, dimension);
}

Vector::Vector(const Vector& other)
{
    copyFrom(other);
}

Vector::Vector(Vector&& other)
{
    moveFrom(std::move(other));
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

size_t Vector::getDimension() const
{
    return dimension;
}

Vector::~Vector()
{
    free();
}

void Vector::setData(const double* coords, size_t dimension)
{
    if (!coords)
    {
        coords = resources::vector::DEFAULT_COORDS;
        dimension = resources::vector::DEFAULT_DIMENSION;
    }

    this->dimension = dimension;

    delete[] this->coords;
    this->coords = new double[dimension];
    arrayUtils::copy(coords, this->coords, dimension);
}

void Vector::upsizeDimension(size_t newDimension)
{
    if (newDimension <= dimension)
    {
        return;
    }
    double* upsizedCoords = new double[newDimension]{};
    arrayUtils::copy(coords, upsizedCoords, dimension);

    delete[] coords;
    coords = upsizedCoords;
    dimension = newDimension;
}

void Vector::arithmeticHelper(const Vector& other, double (*op)(double lhs, double rhs))
{
    if (dimension < other.dimension)
    {
        upsizeDimension(other.dimension);
    }

    for (size_t i = 0; i < other.dimension; i++)
    {
        coords[i] = op(coords[i], other.coords[i]);
    }
}

void Vector::copyFrom(const Vector& other)
{
    setData(other.coords, other.dimension);
}

void Vector::moveFrom(Vector&& other)
{
    this->dimension = other.dimension;
    this->coords = other.coords;

    other.coords = nullptr;
}

void Vector::free()
{
    delete[] coords;
    coords = nullptr;

    this->dimension = 0;
}

Vector& Vector::operator+=(const Vector& other)
{
    arithmeticHelper(other, [](double lhs, double rhs)
                     { return lhs + rhs; });
    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    arithmeticHelper(other, [](double lhs, double rhs)
                     { return lhs - rhs; });
    return *this;
}

Vector& Vector::operator*=(double scalar)
{
    for (size_t i = 0; i < dimension; i++)
    {
        coords[i] *= scalar;
    }
    return *this;
}

Vector& Vector::operator/=(double scalar)
{
    if (scalar == 0)
    {
        return *this;
    }

    for (size_t i = 0; i < dimension; i++)
    {
        coords[i] /= scalar;
    }
    return *this;
}

double Vector::operator[](size_t index) const
{
    if (index >= dimension)
    {
        // We can do better in the future!
        return resources::vector::DEFAULT_VALUE;
    }

    return coords[index];
}

double& Vector::operator[](size_t index)
{
    if (index >= dimension)
    {
        // We can do better in the future!
        return coords[0];
    }

    return coords[index];
}

Vector::operator bool() const
{
    for (size_t i = 0; i < dimension; i++)
    {
        if (coords[i] != resources::vector::DEFAULT_VALUE)
        {
            return true;
        }
    }
    return false;
}

bool operator==(const Vector& lhs, const Vector& rhs)
{
    if (lhs.dimension != rhs.dimension)
    {
        return false;
    }

    for (size_t i = 0; i < lhs.dimension; i++)
    {
        if (lhs.coords[i] != rhs.coords[i])
        {
            return false;
        }
    }

    return true;
}

bool operator!=(const Vector& lhs, const Vector& rhs)
{
    return !(lhs == rhs);
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
    Vector result = lhs;
    return result += rhs;
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
    Vector result = lhs;
    return result -= rhs;
}

Vector operator*(const Vector& lhs, double scalar)
{
    Vector result = lhs;
    return result *= scalar;
}

Vector operator*(double scalar, const Vector& rhs)
{
    return rhs * scalar;
}

Vector operator/(const Vector& lhs, double scalar)
{
    Vector result = lhs;
    return result /= scalar;
}
