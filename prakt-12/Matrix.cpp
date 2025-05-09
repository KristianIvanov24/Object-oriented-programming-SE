#include "Matrix.h"

Matrix::Matrix(size_t size, const double* const* matrix) : Container(size*size, *matrix)
{
    n = size;

    size_t counter = 0; 
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            this->nums[counter++] = matrix[i][j]; // nums[i*size + j]
        }
    }
};

void Matrix::write() const
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << nums[i];
        if ((i + 1) % size != 0)
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
}

Container* Matrix::clone() const
{
    return new Matrix(*this);
}
