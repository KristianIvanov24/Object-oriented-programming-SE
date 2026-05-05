#include <iostream>
#include <fstream>

void calculateSumAndProductToFile(const char* fromFile, const char* toFile) {
	std::ifstream fileIn(fromFile);
	if(!fileIn.is_open()) 
	{
		std::cout << "File with nums cannot be openned" << std::endl;
		return;
	}
	double a, b;
	fileIn >> a >> b;

	fileIn.close();

	std::ofstream fileOut(toFile, std::ios::trunc);
	if(!fileOut.is_open()) 
	{
		std::cout << "File for output cannot be openned" << std::endl;
		return;
	}

	fileOut << "Sum: " << a + b << std::endl;
	fileOut << "Product: " << a * b << std::endl;

	fileOut.close();
}

int main()
{
	calculateSumAndProductToFile("nums.txt", "results.txt");

    return 0;
}