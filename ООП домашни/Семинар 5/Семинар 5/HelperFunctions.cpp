#include "HelperFunctions.h"
#include <cstring>
#include <iostream>
#pragma warning (disable:4996)

unsigned charToDigit(char symbol)
{
	if ('0' <= symbol && symbol <= '9')
		return symbol - '0';
	else if ('A' <= symbol && symbol <= 'F')
		return symbol - 'A' + 10;

	return 0;
}

char digitToChar(unsigned num)
{
	return num + '0';
}

unsigned toPower(unsigned number, unsigned power)
{
	int result = 1;

	while (power--)
		result *= number;

	return result;
}

size_t digitCount(unsigned number)
{
	if (number == 0)
		return 1;

	size_t count = 0;
	while (number)
	{
		count++;
		number /= 10;
	}

	return count;
}

char* numberToString(unsigned number)
{
	size_t digits = digitCount(number);
	char* str = new char[digits + 1];

	for(size_t i = 0; i < digits; i++)
	{
		unsigned current = number % 10;
		str[digits - i - 1] = digitToChar(current);

		number /= 10;
	}

	str[digits] = '\0';
	return str;
}

unsigned stringToNumber(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;

	while (*str)
	{
		result *= 10;
		result += charToDigit(*str);

		str++;
	}

	return result;
}

void reverseString(char* str)
{
	if (!str)
		return;

	size_t size = strlen(str);

	for (size_t i = 0; i < size / 2; i++)
	{
		std::swap(*(str + i), *(str + size - 1 - i));
	}
}