#include "ComplexNumber.h"

ComplexNumber::ComplexNumber()
{
	im = 0;
	re = 0;
}

ComplexNumber::ComplexNumber(double re, double im) {
	setIm(im);
	setRe(re);
}

void ComplexNumber::setRe(double re)
{
	this->re = re;
}

void ComplexNumber::setIm(double im)
{
	this->im = im;
}

double ComplexNumber::getRe() const
{
	return re;
}

double ComplexNumber::getIm() const
{
	return im;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other)
{
	this->re += other.re;
	this->im += other.im;
	return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other)
{
	this->re -= other.re;
	this->im -= other.im;
	return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other)
{
	this->re /= other.re;
	this->im /= other.im;
	return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other)
{
	this->re *= other.re;
	this->im *= other.im;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& r)
{
	if (r.im >= 0) {
		return os << r.re << " + " << r.im << "i\n";
	}
	else {
		return os << r.re << " - " << r.im*-1 << "i\n";
	}
	
}

std::istream& operator>>(std::istream& is, ComplexNumber& r)
{
	return is >> r.re >> r.im;
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber curr(lhs);

	curr += rhs;

	return curr;
}

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber curr(lhs);

	curr -= rhs;

	return curr;
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber curr(lhs);

	curr *= rhs;

	return curr;
}

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber curr(lhs);

	curr /= rhs;

	return curr;
}

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs)
{

	if (lhs.getIm() == rhs.getIm() && lhs.getRe() == rhs.getRe())
		return true;

	return false;
}

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	if (lhs.getIm() != rhs.getIm() || lhs.getRe() != rhs.getRe())
		return true;
	
	return false;
}

