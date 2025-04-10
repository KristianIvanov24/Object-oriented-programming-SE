#pragma once
#include <iostream>


class Matrix
{
private:
	size_t rows = 0;
	size_t cols = 0;
	int** matrix = nullptr;

	void free();
	void copyFrom(const Matrix&);
	void createMatrix(size_t, size_t);
	void copyMatrixValues(size_t, size_t, int**);

public:
	Matrix();
	Matrix(size_t, size_t, int**);
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	~Matrix();

	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(int);

	bool operator==(const Matrix&);
	bool operator!=(const Matrix&);

	int* operator[](size_t);
	const int* operator[](size_t) const;

	friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, int);
Matrix operator*(int, const Matrix&);

