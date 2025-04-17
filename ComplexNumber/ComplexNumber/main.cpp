#include <iostream>
#include "ComplexNumber.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;


int main() {

	ComplexNumber a1(2,3), a2(-3,-6);

	cout << a1 << a2;


	cin >> a1;
	cout << a1;

	return 0;
}