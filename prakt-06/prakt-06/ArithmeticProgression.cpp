#include "ArithmeticProgression.h"

ArithmeticProgression::ArithmeticProgression()
{
	q = 1;
	first = 0;
}

ArithmeticProgression::ArithmeticProgression(int first, int q)
{
	this->q = q;
	this->first = first;
}

ArithmeticProgression& ArithmeticProgression::operator+=(const ArithmeticProgression& other)
{
	q += other.q;
	first += other.first;
	return *this;
}

ArithmeticProgression& ArithmeticProgression::operator-=(const ArithmeticProgression& other)
{
	q -= other.q;
	first -= other.first;
	return *this;
}

ArithmeticProgression& ArithmeticProgression::operator>>(unsigned n)
{
	first += n * q;
	return *this;
}

int ArithmeticProgression::operator[](unsigned n)
{
	return first + (n - 1) * q;
}

int ArithmeticProgression::operator()(unsigned n)
{
	return ((2 * first + (n - 1) * q) * n) / 2;
}

ArithmeticProgression& operator+(ArithmeticProgression& lhs, const ArithmeticProgression& rhs)
{
	lhs += rhs;
	return lhs;
}

ArithmeticProgression& operator- (ArithmeticProgression& lhs, const ArithmeticProgression& rhs)
{
	lhs -= rhs;
	return lhs;
}
