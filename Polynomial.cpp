#include "Polynomial.h"
#include<iostream>

void Polynomial::free()
{
	delete[]coeff;
	coeff = nullptr;
	n = 0;
}

void Polynomial::copyFrom(const Polynomial& other)
{
	n = other.n;
	coeff = new double[n + 1];
	for (int i = 0; i <= n; ++i)
	{
		coeff[i] = other.coeff[i];
	}
}

Polynomial::Polynomial(int n)
{
	setN(n);
	coeff = new double[this->n + 1] {0};
}

Polynomial::Polynomial(const Polynomial& other)
{
	copyFrom(other);
}

Polynomial& Polynomial::operator=(const Polynomial& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void Polynomial::setN(int n)
{
	if (n < 0)
		n = 0;
	this->n = n;
}

void Polynomial::setCoeff(double* coeff)
{
	for (int i = 0; i <= n; ++i)
	{
		this->coeff[i] = coeff[i];
	}
}

bool Polynomial::setCoeffOnIndex(int index,double num)
{
	if (index > n || index < 0)
	{
		return false;
	}
	coeff[index] = num;
	return true;
}

double Polynomial::returnCoeffOnIndex(int index) const
{
	if (index > n || index < 0)
	{
		return 0.0;
	}
	return coeff[index];
}

double Polynomial::calculateResult(int x) const
{
	double result = 0.0;
	double multi = 1;
	for (int i = 0; i <= n; ++i)
	{
		result += coeff[i] * multi;
		multi *= x;
	}
	return result;
}

void Polynomial::print() const
{
	std::cout << "P(x) = " << coeff[0];
	for (int i = 1; i <= n; ++i)
	{
		if(coeff[i]>=0)
		{
			std::cout << " +" << coeff[i] << "*x^" <<i;
		}
		else
		{
			std::cout << " " << coeff[i] << "*x^" << i;
		}
	}
}

Polynomial Polynomial::createConstant(double num)
{
	Polynomial p(0);
	p.setCoeffOnIndex(0, num);
	return p;
}

Polynomial::~Polynomial()
{
	free();
}
