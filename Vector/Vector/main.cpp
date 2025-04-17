#include "Vector.h"
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {

	int i[] = {1,2,3,4,5,6};

	Vector v1(6,i);
	Vector v2(10);
	Vector v3(6);

	std::ofstream ofs("Vector.bin", std::ios::binary);

	v1.saveToBinaryFile(ofs);

	ofs.close();

	std::ifstream ifs("Vector.bin", std::ios::binary);

	v2.readFromBinaryFile(ifs);

	ifs.close();

	v2 += v1;
	v2 -= v1;

	v3 = v2 - v1;

	cout << v3;

	Vector v4;
	cin >> v4;
	cout << endl << v4 << "\t" << v4.getSize();

	return 0;
}