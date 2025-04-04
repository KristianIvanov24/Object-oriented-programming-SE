#include "Matrix.h"

void Matrix::free()
{
	delete[] matrix;
	matrix = nullptr;

	rows = 0;
	cols = 0;
}

void Matrix::copyFrom(const Matrix& other)
{
	createMatrix(other.rows, other.cols);
	copyMatrixValues(other.rows, other.cols, other.matrix);

	rows = other.rows;
	cols = other.cols;
}

void Matrix::createMatrix(size_t rows, size_t cols)
{
	matrix = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i] = new int[cols] {0};
	}
}

void Matrix::copyMatrixValues(size_t rows, size_t cols, int** matrix)
{
	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			this->matrix[r][c] = matrix[r][c];
		}
	}
}

Matrix::Matrix()
{
	rows = 2;
	cols = 2;

	createMatrix(rows, cols);
}

Matrix::Matrix(size_t rows, size_t cols, int** matrix)
{
	this->rows = rows;
	this->cols = cols;

	createMatrix(rows, cols);
	if (matrix)
		copyMatrixValues(rows, cols, matrix);
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Matrix::~Matrix()
{
	free();
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (other.rows != rows || other.cols != cols)
	{
		Matrix empty = Matrix();
		return empty;
	}

	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			matrix[r][c] += other[r][c];
		}
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (other.rows != rows || other.cols != cols)
	{
		Matrix empty = Matrix();
		return empty;
	}

	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			matrix[r][c] -= other[r][c];
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if (other.rows != cols)
	{
		Matrix empty = Matrix();
		return empty;
	}

	Matrix temp = *this;

	delete[] this->matrix;
	createMatrix(rows, other.cols);

	size_t oldCols = cols;
	cols = other.cols;

	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			for (size_t indx = 0; indx < oldCols; indx++)
			{
				matrix[r][c] += temp[r][indx] * other.matrix[indx][c];
			}
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(int scalar)
{
	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			matrix[r][c] *= scalar;
		}
	}

	return *this;
}

bool Matrix::operator==(const Matrix& other)
{
	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			if (matrix[r][c] != other.matrix[r][c])
			{
				return false;
			}
		}
	}

	return true;
}

bool Matrix::operator!=(const Matrix& other)
{
	return !(this == &other);
}

int* Matrix::operator[](size_t indx)
{
	if (indx >= rows)
		return nullptr;

	return matrix[indx];
}

const int* Matrix::operator[](size_t indx) const
{
	if (indx >= rows)
		return nullptr;

	return matrix[indx];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for (size_t r = 0; r < matrix.rows; r++)
	{
		for (size_t c = 0; c < matrix.cols; c++)
		{
			os << matrix.matrix[r][c] << " ";
		}

		os << '\n';
	}

	return os;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix temp = lhs;
	temp += rhs;

	return temp;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix temp = lhs;
	temp -= rhs;

	return temp;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix temp = lhs;
	temp *= rhs;

	return temp;
}

Matrix operator*(const Matrix& matrix, int scalar)
{
	Matrix temp = matrix;
	temp *= scalar;

	return temp;
}

Matrix operator*(int scalar, const Matrix& matrix)
{
	return operator*(matrix, scalar);
}