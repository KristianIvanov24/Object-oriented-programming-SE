#include "ArithmeticProgression.h"

ArithmeticProgression::ArithmeticProgression()
{
	firstMember = 1;
	diff = 1;
}

ArithmeticProgression::ArithmeticProgression(int firstMember, int diff)
{
	this->firstMember = firstMember;
	this->diff = diff;
}

ArithmeticProgression& ArithmeticProgression::operator+=(const ArithmeticProgression& other)
{
	firstMember += other.firstMember;
	diff += other.diff;

	return *this;
}

ArithmeticProgression& ArithmeticProgression::operator-=(const ArithmeticProgression& other)
{
	firstMember -= other.firstMember;
	diff -= other.diff;

	return *this;
}

ArithmeticProgression operator^(const ArithmeticProgression& progression, unsigned n)
{
	int newFirst = progression.firstMember + (n - 1) * progression.diff;

	return ArithmeticProgression(newFirst, progression.diff);
}

int ArithmeticProgression::operator[](unsigned n) const
{
	return firstMember + (n - 1) * diff;
}

int ArithmeticProgression::operator()(unsigned n) const
{
	int lastMember = firstMember + (n - 1) * diff;
	return (firstMember + lastMember) * n / 2;
}

ArithmeticProgression operator-(const ArithmeticProgression& lhs, 
	const ArithmeticProgression& rhs)
{
	ArithmeticProgression res = lhs;
	res += rhs;

	return res;
}

ArithmeticProgression operator+(const ArithmeticProgression& lhs, 
	const ArithmeticProgression& rhs)
{
	ArithmeticProgression res = lhs;
	res -= rhs;

	return res;
}