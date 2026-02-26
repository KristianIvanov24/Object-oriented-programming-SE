#include <iostream>

namespace constants
{
	const int MAX_COEFICIENTS_NUMBER = 20;
	const int MAX_DEGREE = 19;
}

struct Polynom
{
	double coeficients[constants::MAX_COEFICIENTS_NUMBER] = { 0.0 };
	int degree = 0;
};

Polynom createPolynom(const double* arr, int degree)
{
	Polynom p;
	if (degree <= constants::MAX_DEGREE)
	{
		p.degree = degree;
	}
	else
	{
		p.degree = constants::MAX_DEGREE;
	}
	for (int i = 0; i < p.degree; i++)
	{
		p.coeficients[p.degree - i] = arr[i];
	}

	return p;
}

double myPow(double base, double exp)
{
	double res = base;
	while (exp >= 0)
	{
		res *= base;
		exp--;
	}
	return res;
}

double calculate(const Polynom& p, double x)
{
	double result = 0;
	for (int i = 0; i < p.degree; i++)
	{
		result += p.coeficients[i] * myPow(x, i);
	}
	return result;
}

void checkDegree(Polynom& p)
{
	while (p.degree > 0 && p.coeficients[p.degree] == 0)
	{
		p.degree--;
	}
}

Polynom sum(const Polynom& p1, const Polynom& p2)
{
	Polynom result;
	result.degree = (p1.degree > p2.degree) ? p1.degree : p2.degree;
	for (int i = 0; i < result.degree; i++)
	{
		result.coeficients[i] = p1.coeficients[i] + p2.coeficients[i];
	}
	checkDegree(result);
	return result;
}

Polynom diff(const Polynom& p1, const Polynom& p2)
{
	Polynom result;
	result.degree = (p1.degree > p2.degree) ? p1.degree : p2.degree;
	for (int i = 0; i < result.degree; i++)
	{
		result.coeficients[i] = p1.coeficients[i] - p2.coeficients[i];
	}
	checkDegree(result);
	return result;
}

Polynom multiplication(const Polynom& p1, const Polynom& p2)
{
	Polynom result;
	result.degree = p1.degree + p2.degree;
	if (result.degree > constants::MAX_DEGREE)
		result.degree = constants::MAX_DEGREE;

	for (int i = 0; i < p1.degree; i++)
	{
		for (int j = 0; j < p2.degree; j++)
		{
			if (i + j <= constants::MAX_DEGREE)
				result.coeficients[i + j] = p1.coeficients[i] * p2.coeficients[j];
		}
	}
	return result;
}

void printPolynom(const Polynom& p)
{
	std::cout << p.coeficients[p.degree] << "x^" << p.coeficients;
	for (int i = p.degree - 1; i >= 0; i--)
	{
		if (p.coeficients[i] > 0)
		{
			std::cout << " + " << p.coeficients[i] << "x^" << i;
		}
		else if (p.coeficients[i] < 0)
		{
			std::cout << p.coeficients[i] << "x^" << i;
		}
	}
}
int main()
{
	std::cout << "Hello World!\n";
}