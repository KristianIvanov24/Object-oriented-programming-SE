#include "Matrix.h"

Matrix::Matrix()
{
    n = m = 2;
    matrix = new int*[n];

    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
    }
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    if (n != other.n || m != other.m)
        return *this;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    if (n != other.n || m != other.m)
        return *this;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    if (m != other.n)
        return *this;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(int scalar)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] *= scalar;
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other)
{
    if (n != other.n || m != other.m)
        return false;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != other.matrix[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other)
{
    return !(this->matrix == other.matrix);
}

const int* Matrix::operator[](int rowIndex) const
{
    return matrix[rowIndex];
}

int* Matrix::operator[](int rowIndex)
{
    return matrix[rowIndex];
}

Matrix::operator bool() const
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != 0)
                return true;
        }
    }
    return false;
}

unsigned int Matrix::getRows() const
{
    return n;
}

unsigned int Matrix::getColls() const
{
    return m;
}

Matrix& operator+(Matrix& lhs, const Matrix& rhs)
{
    return lhs += rhs;
}

Matrix& operator-(Matrix& lhs, const Matrix& rhs)
{
    return lhs -= rhs;
}

Matrix& operator*(Matrix& lhs, const Matrix& rhs)
{
    /*if (lhs.getColls() != rhs.getRows())
        return;*/

    return lhs *= rhs;
}

Matrix& operator*(Matrix& lhs, int scalar)
{
    return lhs *= scalar;
}
