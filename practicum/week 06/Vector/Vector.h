#pragma once
#include <iostream>

class Vector
{
private:

	int* data = nullptr;
	size_t size = 0;

	void copyFrom(const Vector& other);
	void free();

public:
	Vector();
	Vector(size_t size);
	Vector(const int* data, size_t size);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	Vector& operator+=(const Vector& vector);
	Vector& operator-=(const Vector& vector);
	Vector& operator*=(int num);

	int operator[](size_t idx) const; // return type const int& is also an option
	int& operator[](size_t idx);

	bool operator!() const;
	double operator~() const;

	void saveToFile(const char* file) const;
	void saveToFile(std::ofstream& ofs) const;

	void readFromFile(const char* file);
	void readFromFile(std::ifstream& ifs);

	friend std::ostream& operator<<(std::ostream& os, const Vector& vector);
	friend std::istream& operator>>(std::istream& is, Vector& vector);
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(int num, const Vector& vector);
Vector operator*(const Vector& vector, int num);

