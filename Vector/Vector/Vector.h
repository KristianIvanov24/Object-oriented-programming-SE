#pragma once

#include<fstream>

class Vector {
	int* data;
	int size;

	void free();
	void copyFrom(const Vector&);

public:
	
	Vector();
	Vector(int size);
	Vector(int size, int* arr);
	~Vector();
	Vector(const Vector&);
	Vector& operator=(const Vector&);

	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);


	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator*=(int);

	friend std::ostream& operator<<(std::ostream&, const Vector&);
	friend std::istream& operator>>(std::istream&, Vector&);

	int operator[](size_t idx) const; // return type const int& is also an option
	int& operator[](size_t idx);

	bool isNull() const;

	int getSize() const;

};

Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
//Vector operator*(const Vector&, int);