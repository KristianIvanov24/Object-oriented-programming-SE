#include "KBaseNumber.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "HelperFunctions.h"

#pragma warning (disable:4996)

void KBaseNumber::free()
{
	delete[] numberInKBase;

	numberInKBase = nullptr;
	base = 10;
}

void KBaseNumber::copyFrom(const KBaseNumber& other)
{
	numberInKBase = new char[strlen(other.numberInKBase) + 1];

	strcpy(numberInKBase, other.numberInKBase);
	base = other.base;
}

KBaseNumber::KBaseNumber()
{
	numberInKBase = nullptr;
	base = 10;
}

KBaseNumber::KBaseNumber(const char* number, unsigned base)
{
	if (!number)
		return;

	update(number, base);
}

KBaseNumber::KBaseNumber(const KBaseNumber& other)
{
	copyFrom(other);
}

KBaseNumber& KBaseNumber::operator=(const KBaseNumber& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

KBaseNumber::~KBaseNumber()
{
	//std::cout << numberInKBase << std::endl;
	free();
}

void KBaseNumber::update(const char* number, unsigned base)
{
	if (!number)
		return;

	delete[] numberInKBase;
	numberInKBase = new char[strlen(number) + 1];

	strcpy(numberInKBase, number);
	this->base = base;
}

void KBaseNumber::print() const
{
	std::cout << numberInKBase << "(" << base << ")";
}

char* KBaseNumber::getNumber() const
{
	return this->numberInKBase;
}

KBaseNumber KBaseNumber::convertToDecimal() const
{
	unsigned resultNumber = 0;
	size_t ptr = 0;
	size_t digitCount = strlen(numberInKBase);

	while (*(numberInKBase + ptr))
	{
		resultNumber += toPower(base, digitCount - 1 - ptr) * charToDigit(*(numberInKBase + ptr));
		ptr++;
	}

	KBaseNumber result = KBaseNumber(numberToString(resultNumber), 10);

	return result;
}

KBaseNumber KBaseNumber::convertTo(unsigned baseToConvert)
{
	if (baseToConvert == 10)
	{
		if (base == 10)
			return *this;
		else
			return convertToDecimal();
	}

	KBaseNumber numberInDecimal = convertToDecimal();
	unsigned onlyNumber = stringToNumber(numberInDecimal.numberInKBase);
	unsigned resultNum = 0;

	while (onlyNumber)
	{
		resultNum *= 10;
		resultNum += (onlyNumber % baseToConvert);

		onlyNumber /= baseToConvert;
	}

	char* resultAsString = numberToString(resultNum);
	reverseString(resultAsString);

	KBaseNumber result(resultAsString, baseToConvert);

	return result;
}

int KBaseNumber::compareWith(const KBaseNumber& other)
{
	KBaseNumber thisInDecimal = this->convertToDecimal();
	KBaseNumber otherInDecimal = other.convertToDecimal();

	unsigned thisAsNum = stringToNumber(thisInDecimal.numberInKBase);
	unsigned otherAsNum = stringToNumber(otherInDecimal.numberInKBase);

	if (thisAsNum < otherAsNum)
		return -1;
	else if (thisAsNum > otherAsNum)
		return 1;
	else
		return 0;

}

void KBaseNumber::saveToFile(const char* fileName) const
{
	if (!fileName)
		return;

	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	size_t numberLen = strlen(this->numberInKBase);
	ofs.write((const char*)&numberLen, sizeof(size_t));
	ofs.write((const char*)numberInKBase, numberLen);
	ofs.write((const char*)&base, sizeof(unsigned));

	ofs.close();
}

void KBaseNumber::readFromFile(const char* fileName)
{
	if (!fileName)
		return;

	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	size_t numberLen;
	ifs.read((char*)&numberLen, sizeof(size_t));

	delete[] numberInKBase;
	numberInKBase = new char[numberLen + 1];

	ifs.read((char*)numberInKBase, numberLen);
	numberInKBase[numberLen] = '\0';

	ifs.read((char*)&base, sizeof(unsigned));

	ifs.close();
}


