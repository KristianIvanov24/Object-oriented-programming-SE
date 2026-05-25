# include "Polynomial.h"
# include <iostream>

void Polynomial::copyFrom(const Polynomial& other) {
	this->degree = other.degree;
	coefficients = new double[degree + 1];
	for (int i = 0; i <= degree; i++)
		coefficients[i] = other.coefficients[i];
}

void Polynomial::free() {
	delete[] coefficients;
}

Polynomial::Polynomial(int degree) {
	if (degree < 0) {
		std::cout << "Invalid degree! Degree must be >= 0. Degree set to 0.";
		this->degree = 0;
	}
	this->degree = degree;
	coefficients = new double[degree + 1];
	for (int i = 0; i <= degree; i++)
		coefficients[i] = 0.0;
}

Polynomial::Polynomial(const Polynomial& other) {
	copyFrom(other);
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Polynomial::~Polynomial() {
	free();
}

void Polynomial::setCoefficients(int degree, double value) {
	if (degree < 0 || degree > this->degree)
	{
		std::cout << "Degree out of range! Degree set to 0.";
		degree = 0;
	}
	coefficients[degree] = value;
}

double Polynomial::getCoefficients(int degree) const {
	if (degree < 0 || degree > this->degree)
	{
		std::cout << "Degree out of range! Degree set to 0.";
		degree = 0;
	}
	return coefficients[degree];
}

double Polynomial::evaluate(double x) const {
	double result = 0.0;
	double power = 1.0;

	for (int i = 0; i <= this->degree; i++) {
		result += coefficients[i] * power;
		power *= x;
	}
	return result;
}

void Polynomial::print() const {
	bool first = true;
	for (int i = 0; i <= this-> degree; i++) {
		if (coefficients[i] == 0.0) continue;

		if (!first) std::cout << " + ";
		std::cout << coefficients[i];

		if (i == 1) std::cout << "x";
		else if (i >= 2) std::cout << "x^" << i;

		first = false;
	}
	if (first) std::cout << "0";
	std::cout << "\n";
}

Polynomial Polynomial::createConstant(double value) {
	Polynomial p(0);
	p.setCoefficients(0, value);
	return p;
}