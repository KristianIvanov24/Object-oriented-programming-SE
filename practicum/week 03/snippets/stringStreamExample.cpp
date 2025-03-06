#include <iostream>
#include <sstream>

size_t getSymbolCount(const char* str, char ch)
{
	if (!str)
	{
		return 0;
	}

	size_t counter = 0;

	while (*str)
	{
		if (*str == ch)
		{
			counter++;
		}
		str++;
	}

	return counter;
}

int main()
{
	char str[] = "124 4535 3 314 535";

	size_t arrSize = getSymbolCount(str, ' ') + 1;
	int* arr = new int[arrSize] {};

	std::stringstream ss(str);

	for (size_t i = 0; i < arrSize; i++)
	{
		ss >> arr[i];
	}

	for (size_t i = 0; i < arrSize; i++)
	{
		std::cout << arr[i] << ' ';
	}

	delete[] arr;

	return 0;
}
