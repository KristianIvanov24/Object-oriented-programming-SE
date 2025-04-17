#include "ArithmeticProgression.h"

void ArithmeticProgression::free()
{
	delete[] An;
	len = 0;
	diff = 0;
}

void ArithmeticProgression::copyFrom(const ArithmeticProgression& other)
{

	len = other.len;
	diff = other.diff;

	An = new double[len];

	for (int i = 0; i < len; i++) {
		An[i] = other.An[i];
	}

}

ArithmeticProgression::ArithmeticProgression()
{
	len = 100;
	diff = 1;

	An = new double[len];

	An[0] = 0;

	for (int i = 1; i < len; i++) {
		An[i] = An[i - 1] + diff;
	}
	
}

ArithmeticProgression::ArithmeticProgression(double first, double diff)
{
	len = 100;
	this->diff = diff;

	An = new double[len];
	An[0] = first;

	for (int i = 1; i < len; i++) {
		An[i] = An[i - 1] + this->diff;
	}

}

ArithmeticProgression::~ArithmeticProgression()
{
	free();
}

ArithmeticProgression::ArithmeticProgression(const ArithmeticProgression& other)
{
	copyFrom(other);
}

ArithmeticProgression& ArithmeticProgression::operator=(const ArithmeticProgression& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

ArithmeticProgression& ArithmeticProgression::operator+=(const ArithmeticProgression& other)
{
	if (this->len != other.len)
		return *this;

	for (int i = 0; i < this->len; i++) {
		this->An[i] += other.An[i];
	}
	return *this;
}

ArithmeticProgression& ArithmeticProgression::operator-=(const ArithmeticProgression& other)
{
	if (this->len != other.len)
		return *this;

	for (int i = 0; i < this->len; i++) {
		this->An[i] -= other.An[i];
	}
	return *this;
}

double ArithmeticProgression::operator[](size_t idx) const
{
	return An[idx];
}

double& ArithmeticProgression::operator[](size_t idx)
{
	return An[idx];
}

std::ostream& operator<<(std::ostream& os, const ArithmeticProgression& a)
{
	for (int i = 0; i < a.len; i++) {
		os << a.An[i] << " ";
	}
	return os;
}

std::istream& operator>>(std::istream& is, ArithmeticProgression& ar)
{
	delete[] ar.An;

	is >> ar.len;
	is >> ar.diff;

	ar.An = new double[ar.len];

	is >> ar.An[0];

	for (int i = 1; i < ar.len; i++) {
		ar.An[i] = ar.An[i - 1] + ar.diff;
	}
	return is;
}

ArithmeticProgression operator+(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs)
{
	ArithmeticProgression curr(lhs);

	if (lhs.len != rhs.len) {
		return curr;
	}

	curr += rhs;

	return curr;

}

ArithmeticProgression operator-(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs)
{
	ArithmeticProgression curr(lhs);

	if (lhs.len != rhs.len) {
		return curr;
	}

	curr -= rhs;

	return curr;
}


int ArithmeticProgression::operator()()const {
	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += An[i];
	}
	return sum;
}
