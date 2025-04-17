#include "ArithmeticProgression.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {

	ArithmeticProgression a, b;
	a = b;

	ArithmeticProgression c(10, 2);

	c += a;

	ArithmeticProgression d = c + a;
	

	cout << d;

	ArithmeticProgression e;
	cin >> e >> d;
	cout << e + d;
	cout << endl << e[9] << endl << e();
	

	return 0;
}
