#include "KBaseNumber.h";
#include <iostream>
#include <fstream>

int main() {
	KBaseNumber num1("CE9A", 16);
	num1.print();
	num1.printConvertedTo(8);

	KBaseNumber num2("147232", 8);
	std::cout << num1.compareWith(num2) << std::endl;

	num2.update("1312", 4);
	std::cout << num2.compareWith(num1) << std::endl;

	KBaseNumber num3;
	num1.saveToFile("file.bin");
	num3.readFromFile("file.bin");
	num3.print();
}