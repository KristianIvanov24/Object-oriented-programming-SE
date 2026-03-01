#include <iostream>
class ComplexNum
{
public:
	double re, im;
};
ComplexNum* complexSum(ComplexNum num1, ComplexNum num2)
{
	double re = num1.re + num2.re;
	double im = num1.im + num2.im;

	ComplexNum* result = new ComplexNum{ re,im };

	return result;
}
ComplexNum* complexMult(ComplexNum num1, ComplexNum num2)
{
	double re = num1.re * num2.re - num1.im * num2.im;
	double im = num1.re * num2.im + num1.im * num2.re;

	ComplexNum* result = new ComplexNum{ re,im };

	return result;
}
void printComplexNum(ComplexNum num)
{
	if (num.re == 0 && num.im == 0)
	{
		std::cout << 0 << std::endl;
		return;
	}

	if(num.re != 0)
		std::cout << num.re << ' ';

	if (num.im == 0)
		return;

	char sign = num.im < 0 ? '-' : '+';
	std::cout << sign << " i*" << abs(num.im) << std::endl;
}
int main()
{
	ComplexNum num1 = { 1,2 }, num2 = { -3,-4 };
	ComplexNum* sum = complexSum(num1, num2);

	printComplexNum(*sum);
	delete sum;

	ComplexNum* mult = complexMult(num1, num2);
	printComplexNum(*mult);
	delete mult;
}
