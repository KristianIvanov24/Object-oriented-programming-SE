#pragma once

class Polynomial {
private:
	int degree;
	double* coefficients;

	void copyFrom(const Polynomial& other);
	void free();
public:
	Polynomial(int degree);
	Polynomial(const Polynomial& other);
	Polynomial& operator=(const Polynomial& other);
	~Polynomial();

	void setCoefficients(int degree, double value);
	double getCoefficients(int degree) const;
	double evaluate(double x) const;
	void print() const;
	static Polynomial createConstant(double value);

};