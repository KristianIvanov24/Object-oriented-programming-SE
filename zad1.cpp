#include <iostream>

struct Complex
{
	double real;
	double imaginary;
};

Complex sumOfTwoDigits(const Complex& num1, const Complex& num2)
{
	return{ num1.real + num2.real , num1.imaginary + num2.imaginary };
}

Complex multiplication(const Complex& num1, const Complex& num2)
{
	return{ num1.real * num2.real - num1.imaginary * num2.imaginary, num1.real * num2.imaginary + num1.imaginary * num1.real };
}

void printComplexNumber(const Complex& num)
{
	std::cout << num.real;
	if (num.imaginary > 0)
	{
		std::cout << "+" << num.imaginary<<"i";
	}
	else
	{
		std::cout << "-" << num.imaginary<<"i";
	}
	std::cout << std::endl;
}
int main()
{
	Complex num1, num2;
	std::cin >> num1.real >> num1.imaginary;
	std::cin >> num2.real >> num2.imaginary;
	printComplexNumber(num1);
	printComplexNumber(sumOfTwoDigits(num1, num2));
	std::cout << std::endl;
	printComplexNumber(multiplication(num1, num2));
	std::cout << std::endl;
}