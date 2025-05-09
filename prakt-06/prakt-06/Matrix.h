#pragma once
class Matrix
{
private:
	unsigned int n, m;
	int** matrix;
public:
	Matrix();
	Matrix& operator+= (const Matrix& other);
	Matrix& operator-= (const Matrix& other);
	Matrix& operator*= (const Matrix& other);
	Matrix& operator*= (int scalar);
	bool operator== (const Matrix& other);
	bool operator!= (const Matrix& other);
	const int* operator[] (int rowIndex) const ;
	int* operator[] (int rowIndex);
	operator bool() const;

	unsigned int getRows() const;
	unsigned int getColls() const;
};
Matrix& operator+ (Matrix& lhs, const Matrix& rhs);
Matrix& operator- (Matrix& lhs, const Matrix& rhs);
Matrix& operator* (Matrix& lhs, const Matrix& rhs);
Matrix& operator* (Matrix& lhs, int scalar);