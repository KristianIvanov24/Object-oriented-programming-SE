#include "Vector.h"
#include <cstring>
#include <iostream>
#pragma warning (disable:4996)

void Vector::free()
{
	delete[] data;

	data = nullptr;
	size = 0;
}

void Vector::copyFrom(const Vector& other)
{
	size = other.size;
	data = new int[size];

	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

Vector::Vector()
{
	data = nullptr;
	size = 0;
}

Vector::Vector(int size)
{
	this->size = size;
	data = new int[size];
	for (int i = 0; i < this->size; i++) {
		data[i] = 0;
	}
}

Vector::Vector(int size, int* arr)
{
	this->size = size;
	data = new int[this->size];

	for (int i = 0; i < this->size; i++) {
		data[i] = arr[i];
	}
}

Vector::~Vector()
{
	free();
}

Vector::Vector(const Vector& other)
{
	copyFrom(other);
}

Vector& Vector::operator=(const Vector& other)
{
	
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;

}

void Vector::saveToBinaryFile(std::ofstream& ofs) const
{
	if (!ofs) 
		throw std::runtime_error("Could not open file for writing");

	ofs.write((const char*)&size, sizeof(size)); // записваме размера
	ofs.write((const char*)data, sizeof(int) * size); // записваме самите елементи

}

void Vector::readFromBinaryFile(std::ifstream& ifs)
{
	if (!ifs) 
		throw std::runtime_error("Could not open file for reading");

	int newSize;
	ifs.read((char*)&newSize, sizeof(newSize)); // четем размера

	int* newData = new int[newSize];

	ifs.read((char*)newData, sizeof(int) * newSize);

	free();
	data = newData;
	size = newSize;
}

Vector& Vector::operator+=(const Vector& other)
{
	
	if (this->size != other.size) {
		return *this;
	}
	for (int i = 0; i < this->size; i++) {
		data[i] += other.data[i];
	}
	return *this;

}

Vector& Vector::operator-=(const Vector& other)
{
	if (this->size != other.size) {
		return *this;
	}
	for (int i = 0; i < this->size; i++) {
		data[i] -= other.data[i];
	}
	return *this;

}

Vector& Vector::operator*=(int num)
{
	for (int i = 0; i < size; i++) {
		data[i] *= num;
	}
	return *this;
}

int Vector::getSize() const
{
	return size;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
	os << "( ";
	for (int i = 0; i < v.size; i++) {
		if (i != v.size - 1)
			os << v.data[i] << ", ";
		else
			os << v.data[i];
	}
	os << " )";
	return os;
}

std::istream& operator>>(std::istream& is, Vector& vec)
{
	delete[] vec.data;

	is >> vec.size;

	vec.data = new int[vec.size];

	for (int i = 0; i < vec.size; i++) {
		is >> vec.data[i];
	}
	return is;
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	Vector vector(lhs);

	vector += rhs;

	return vector;

}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	Vector vector(lhs);

	vector -= rhs;

	return vector;
}

int Vector::operator[](size_t idx) const
{
	return data[idx];
}

int& Vector::operator[](size_t idx)
{
	return data[idx];
}

bool Vector::isNull() const
{
	if (data == nullptr)
		return true;

	for (int i = 0; i < size; i++) {
		if (data[i] != 0) return false;
	}
	return true;
}
