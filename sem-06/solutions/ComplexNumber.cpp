#include "ComplexNumber.h"

ComplexNumber::ComplexNumber() : real(0), im(0)
{

}

ComplexNumber::ComplexNumber(double real, double im) : real(real), im(im)
{

}

double ComplexNumber::getReal() const
{
	return real;
}

double ComplexNumber::getIm() const
{
	return im;
}

void ComplexNumber::setReal(double real)
{
	this->real = real;
}

void ComplexNumber::setIm(double im)
{
	this->im = im;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other)
{
	real += other.real;
	im += other.im;
	return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other) 
{
	real -= other.real;
	im -= other.im;
	return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other) // формула
{
	double oldReal = real;
	real = real*other.real - im*other.im;
	im = oldReal * other.im + im * other.real;

	return *this;
}

ComplexNumber ComplexNumber::getConjugated() const // комплексно спрегнатото
{
	ComplexNumber result(*this);
	result.im *= -1;

	return result;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other) // формула
{
	ComplexNumber Conjugated = other.getConjugated(); //взимаме комплексно спрегнатата на другата дроб (b)

	ComplexNumber otherCopy(other);// копираме другата (b), за да не я промяняме.

	//Умножаваме двете по комплексно спрегнатата.
	*this *= Conjugated;
	otherCopy *= Conjugated; //Тук трябва да остане само реална част.

	if (otherCopy.real != 0)
	{
		real /= otherCopy.real;
		im /= otherCopy.real;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& r)
{
	return os << r.real << ' ' << r.im << 'i';
}

std::istream& operator>>(std::istream& is, ComplexNumber& r)
{
	return is >> r.real >> r.im;
}


ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result += rhs; // използваме вече написания ни operator+=

	return result;
}

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result -= rhs; // използваме вече написания ни operator-=

	return result;
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result *= rhs; // използваме вече написания ни operator*=

	return result;
}

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	ComplexNumber result(lhs);
	result /= rhs; // използваме вече написания ни operator/=

	return result;
}

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	return abs(lhs.getReal() - rhs.getReal()) < 0.001 && abs(lhs.getIm() - rhs.getIm()) < 0.001;
}

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	return !(lhs == rhs); // използваме вече написания ни operator==
}
