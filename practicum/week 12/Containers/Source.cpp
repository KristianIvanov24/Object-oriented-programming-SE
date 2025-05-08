#include <iostream>
#include "Container.h"
#include "Vector.h"
#include "Matrix.h"

int main()
{
	double arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	Container* obj1 = new Vector(arr, 10);
	obj1->write();
	std::cout << std::endl;
	std::cout << (*obj1)[2]<<std::endl;
	
	double** matrix = new double* [3];
	for (size_t i = 0; i < 3; i++)
	{
		matrix[i] = new double[3]{};
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = j;
		}
	}

	Container* obj2 = new Matrix(matrix, 3);
	obj2->write();
	std::cout << obj2->member(2) << ' ' << obj2->member(10) << ' ' << obj2->operator[](8);


	for (size_t i = 0; i < 3; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	delete obj1;
	delete obj2;
	return 0;
}
