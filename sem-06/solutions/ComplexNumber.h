#pragma once
#include <iostream>

class ComplexNumber
{
	double real;
	double im;

public:
	ComplexNumber();
	ComplexNumber(double real, double im);

	double getReal() const;
	double getIm() const;

	void setReal(double real);
	void setIm(double im);

	ComplexNumber getConjugated() const;

	ComplexNumber& operator+=(const ComplexNumber&);
	ComplexNumber& operator-=(const ComplexNumber&);
	ComplexNumber& operator*=(const ComplexNumber&);
	ComplexNumber& operator/=(const ComplexNumber&);

	friend std::ostream& operator<<(std::ostream&, const ComplexNumber&);
	friend std::istream& operator>>(std::istream&, ComplexNumber&);
};

ComplexNumber operator+(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator-(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator*(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator/(const ComplexNumber&, const ComplexNumber&);

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs);
bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs);
