#pragma once
#include <iostream>
#include <fstream>

class ComplexNumber {

	double re;
	double im;

public:

	ComplexNumber();
	ComplexNumber(double, double);


	void setRe(double);
	void setIm(double);

	double getRe() const;
	double getIm() const;



	ComplexNumber& operator+=(const ComplexNumber&);
	ComplexNumber& operator-=(const ComplexNumber&);
	ComplexNumber& operator/=(const ComplexNumber&);
	ComplexNumber& operator*=(const ComplexNumber&);

	friend std::ostream& operator<<(std::ostream&, const ComplexNumber&);
	friend std::istream& operator>>(std::istream&, ComplexNumber&);

};

ComplexNumber operator+(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator-(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator*(const ComplexNumber&, const ComplexNumber&);
ComplexNumber operator/(const ComplexNumber&, const ComplexNumber&);

bool operator==(const ComplexNumber&, const ComplexNumber&);
bool operator!=(const ComplexNumber&, const ComplexNumber&);