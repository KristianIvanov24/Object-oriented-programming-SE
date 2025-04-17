#pragma once
#include<fstream>

class Matrix {
	int** matrix;
	int row;
	int cols;

	void copyFrom(const Matrix& other);
	void free();

public:

	Matrix();
	Matrix(int row, int cols);
	~Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);

	int getRow() const;
	int getCols() const;

	void setRow(int row);
	void setCols(int cols);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
	friend std::istream& operator>>(std::istream& is, Matrix& mat);

	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);

	Matrix& operator*=(const Matrix& other);
	
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

	bool operator()() const;

	int* operator[](int row);
	const int* operator[](int row) const;

	Matrix& operator*=(int num);

	friend Matrix operator*(const Matrix& mat, int num);
	friend Matrix operator*(int num, const Matrix& mat);

};



