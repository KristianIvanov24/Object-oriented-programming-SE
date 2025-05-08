#include "Matrix.h"
#include <iostream>

Matrix::Matrix(const double* const* data, size_t N) : DynamicContainer(N*N)
{
    size_t counter = 0;
    size = N;

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            this->data[counter++] = data[i][j];
        }
    }
}

void Matrix::write() const
{
    for (size_t i = 0; i < N; i++)
    {
        std::cout << data[i];

        if ((i + 1) % size != 0)
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << std::endl;
        }
    }
}

Container* Matrix::clone() const
{
    return new Matrix(*this);
}
