#include "Vector.h"
#include <iostream>
#include <fstream>

void Vector::copyFrom(const Vector& other)
{
	size = other.size;
	data = new int[other.size];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void Vector::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
}

Vector::Vector()
{
	size = 3;
	data = new int[3]{};
}

Vector::Vector(size_t size)
{
	this->size = size;
	this->data = new int[this->size]{};
}

Vector::Vector(const int* data, size_t size)
{
	if (!data)
	{
		return;
	}
	this->size = size;
	this->data = new int[this->size]{};
	for (size_t i = 0; i < size; i++)
	{
		this->data[i] = data[i];
	}
}

Vector::Vector(const Vector& other)
{
	copyFrom(other);
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Vector::~Vector()
{
	free();
}

Vector& Vector::operator+=(const Vector& vector)
{
	if (this->size != vector.size)
	{
		return *this;
	}

	for (size_t i = 0; i < size; i++)
	{
		data[i] += vector.data[i];
	}

	return *this;
}

Vector& Vector::operator-=(const Vector& vector)
{
	if (this->size != vector.size)
	{
		return *this;
	}

	for (size_t i = 0; i < size; i++)
	{
		data[i] -= vector.data[i];
	}

	return *this;
}

Vector& Vector::operator*=(int num)
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] *= num;
	}
	return *this;
}

int Vector::operator[](size_t idx) const
{
	return data[idx];
}

int& Vector::operator[](size_t idx)
{
	return data[idx];
}

bool Vector::operator!() const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] != 0)
		{
			return false;
		}
	}

	return true;
}

double Vector::operator~() const
{
	double len = 0;

	for (size_t i = 0; i < size; i++)
	{
		len += data[i] * data[i];
	}

	len = std::sqrt(len);
	return len;
}

void Vector::saveToFile(const char* file) const
{
	if (!file)
	{
		return;
	}

	std::ofstream ofs(file, std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	saveToFile(ofs);

	ofs.close();
}

void Vector::saveToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&size, sizeof(size_t));
	ofs.write((const char*)data, sizeof(int) * size);
}

void Vector::readFromFile(const char* file)
{
	if (!file)
	{
		return;
	}

	std::ifstream ifs(file, std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	readFromFile(ifs);

	ifs.close();
}

void Vector::readFromFile(std::ifstream& ifs)
{
	free(); // !!!!!!!!!!
			// clean the current state of the object to set new data in it properly

	ifs.read((char*)&size, sizeof(size_t));
	data = new int[size] {};
	ifs.read((char*)data, sizeof(int) * size);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
	os << "(";
	for (size_t i = 0; i < vector.size; i++)
	{
		os << vector.data[i];

		if (i != vector.size - 1)
		{
			os << ", ";
		}
	}
	os << ")";
	return os;
}

std::istream& operator>>(std::istream& is, Vector& vector)
{
	for (size_t i = 0; i < vector.size; i++)
	{
		is >> vector.data[i];
	}
	return is;
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	Vector result = lhs;
	result += rhs;
	return result;
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	Vector result=lhs;
	result -= rhs;
	return result;
}

Vector operator*(int num, const Vector& vector)
{
	Vector result = vector;
	result *= num;
	return result;
}

Vector operator*(const Vector& vector, int num)
{
	return num * vector;
}
