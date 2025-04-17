#include "Matrix.h"

void Matrix::copyFrom(const Matrix& other)
{
	row = other.row;
	cols = other.cols;

	matrix = new int* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new int[cols];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = other.matrix[i][j];
		}
	}

}

void Matrix::free()
{
	for (int i = 0; i < row; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}

Matrix::Matrix()
{
	row = 2;
	cols = 2;

	matrix = new int* [row];

	for (int i = 0; i < row; i++) {
		matrix[i] = new int[cols];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(int row, int cols) {
	this->row = row;
	this->cols = cols;
	matrix = new int* [row];

	try {
		for (int i = 0; i < row; i++) {
			matrix[i] = new int[cols];
		}
	}
	catch (...) {
		// Освобождаваме всичко, което е заделено до момента
		for (int i = 0; i < row; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		throw; // преизпращаме изключението
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
	free();
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

int Matrix::getRow() const
{
	return row;
}

int Matrix::getCols() const
{
	return cols;
}

void Matrix::setRow(int row)
{
	if (row > 0)
		this->row = row;
}

void Matrix::setCols(int cols)
{
	if (cols > 0)
		this->cols = cols;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (row == other.row && cols == other.cols) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < cols; j++) {
				matrix[i][j] += other.matrix[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (row == other.row && cols == other.cols) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < cols; j++) {
				matrix[i][j] -= other.matrix[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	Matrix curr(this->row, other.cols);

	if (this->cols != other.row) {
		return *this;
	}

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < other.cols; j++) {
			for (int k = 0; k < this->cols; k++) {
				curr.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
			}
		}
	}
	free();

	copyFrom(curr);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
	for (int i = 0; i < mat.row; i++) {
		for (int j = 0; j < mat.cols; j++) {
			os << mat.matrix[i][j] << " ";
		}
		os << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, Matrix& mat)
{
	is >> mat.row;
	is >> mat.cols;

	mat.matrix = new int* [mat.row];
	for (int i = 0; i < mat.row; i++) {
		mat.matrix[i] = new int[mat.cols];
	}

	for (int i = 0; i < mat.row; i++) {
		for (int j = 0; j < mat.cols; j++) {
			is >> mat.matrix[i][j];
		}
	}
	return is;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix mat(lhs);

	if (lhs.cols != rhs.cols || lhs.row != rhs.row)
		return mat;

	mat += rhs;
	
	return mat;
	
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix mat(lhs);

	if (lhs.cols != rhs.cols || lhs.row != rhs.row)
		return mat;

	mat -= rhs;

	return mat;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix mat(lhs);

	mat *= rhs;
	return mat;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.cols != rhs.cols || lhs.row != rhs.row) return false;

	for (int i = 0; i < rhs.row; i++) {
		for (int j = 0; j < rhs.cols; j++) {
			if (lhs.matrix[i][j] != rhs.matrix[i][j]) return false;
		}
	}
	return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
	if (!(lhs == rhs)) return true;
	return false;
}

Matrix operator*(const Matrix& mat, int num)
{
	Matrix curr(mat);

	curr *= num;

	return curr;
}

Matrix operator*(int num, const Matrix& mat)
{
	Matrix curr(mat);

	curr *= num;

	return curr;
}

bool Matrix::operator()() const{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != 0) return false;
		}
	}
	return true;
}

int* Matrix::operator[](int row)
{
	return matrix[row];
}

const int* Matrix::operator[](int row) const
{
	return matrix[row];
}

Matrix& Matrix::operator*=(int num)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			matrix[i][j] *= num;
		}
	}
	return *this;
}


