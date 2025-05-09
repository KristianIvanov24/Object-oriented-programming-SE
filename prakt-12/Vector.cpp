#include "Vector.h"

Vector::Vector(const double* nums, size_t size) : Container(size, nums) {};

void Vector::write() const
{
    std::cout << '(';
    for (size_t i = 0; i < size; i++)
    {
        std::cout << nums[i];
        if (i != size - 1)
            std::cout << ',';
    }
    std::cout << ')' << '\n';
}

Container* Vector::clone() const
{
    return new Vector(*this);
}
