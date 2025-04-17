#include <iostream>
#include "Matrix.h"

int main() {


	Matrix m1(3, 3);
	Matrix m2(4, 3);

	std::cin >> m1 >> m2;

	m1 *= 0;
	m2 = m1 * 0;

	std::cout << m1 << m2;

	return 0;
}