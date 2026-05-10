#pragma once
#include <iostream>

class MyDouble
{
	int integer;
	unsigned fractional;

	static size_t countDigits(unsigned number);
	static unsigned addDigits(size_t exponent);

public:
	MyDouble();
	MyDouble(int integer, unsigned fractional);

	MyDouble& operator+=(const MyDouble& other);
	MyDouble& operator-=(const MyDouble& other);
	MyDouble& operator/=(const MyDouble& other);
	MyDouble& operator*=(const MyDouble& other);

	MyDouble& operator++();
	MyDouble operator++(int);

	friend std::istream& operator>>(std::istream& is, MyDouble& d);
	friend std::ostream& operator<<(std::ostream& os, const MyDouble& d);

	friend bool operator==(const MyDouble& lhs, const MyDouble& rhs);
	friend bool operator!=(const MyDouble& lhs, const MyDouble& rhs);
	friend std::strong_ordering operator<=>(const MyDouble& lhs, const MyDouble& rhs);
};

MyDouble operator+(const MyDouble& lhs, const MyDouble& rhs);
MyDouble operator*(const MyDouble& lhs, const MyDouble& rhs);
MyDouble operator-(const MyDouble& lhs, const MyDouble& rhs);
MyDouble operator/(const MyDouble& lhs, const MyDouble& rhs);