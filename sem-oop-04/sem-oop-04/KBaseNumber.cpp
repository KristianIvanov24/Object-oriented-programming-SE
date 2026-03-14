#define _CRT_SECURE_NO_WARNINGS
#include "KBaseNumber.h"
#include <cstring>
#include "charFunctions.h"
#include <iostream>
#include <fstream>

unsigned KBaseNumber::toDecimal() const
{
	unsigned result = 0;
	unsigned len = strlen(number);
	unsigned multi = 1;
	for (int i = len-1; i >=0; --i)
	{
		if (isDigit(number[i]))
		{
			result += multi * charToUnsigned(number[i]);
		}
		else if (isUpper(number[i]))
		{
			result += multi * upperCharToUnsighned(number[i]);
		}
		multi *= k;
	}
	return result;
}

KBaseNumber KBaseNumber::toNewSystem(unsigned newK) const
{
	unsigned decimal = toDecimal();
	char newNum[constants::MAX_NUM_LEN];
	unsigned digits = howManyDigitsIn(decimal, newK);
	for (int i = digits - 1; i >= 0; --i)
	{
		unsigned left = decimal % newK;
		if (left < 10)
		{
			newNum[i] = unsignedToChar(left);
		}
		else if (left >= 10)
		{
			newNum[i] = unsignedToUpperChar(left);
		}
		decimal /= newK;
	}
	newNum[digits] = '\0';
	KBaseNumber newKbaseNumber(newNum, newK);
	return newKbaseNumber;
}

KBaseNumber::KBaseNumber(const char* num, unsigned k)
{
	setNumber(num);
	setSystem(k);
}

void KBaseNumber::setNumber(const char* num)
{
	if (strlen(num) >= constants::MAX_NUM_LEN)
	{
		this->number[0] = '\0';
		return;
	}
	strcpy(this->number, num);
}

void KBaseNumber::setSystem(unsigned k)
{
	this->k = k;
}

void KBaseNumber::print() const
{
	std::cout << number << '(' << k << ')'<<std::endl;
}

void KBaseNumber::printConvertedTo(unsigned newK) const
{
	KBaseNumber newNum = toNewSystem(newK);
	newNum.print();
}

int KBaseNumber::compareWith(KBaseNumber& toCompare) const
{
	unsigned decimal1 = toDecimal();
	unsigned decimal2 = toCompare.toDecimal();
	if (decimal1 == decimal2)
		return 0;
	else if (decimal1 >= decimal2)
		return 1;
	else return -1;
}

void KBaseNumber::update(const char* newNum, unsigned newK)
{
	setNumber(newNum);
	setSystem(newK);
}

bool KBaseNumber::saveToFile(const char* FILE_NAME) const
{
	std::ofstream ofs(FILE_NAME, std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Error while writing to binary file!" << std::endl;
		return false;
	}
	unsigned len = strlen(number);
	ofs.write((const char*)&k, sizeof(unsigned));
	ofs.write((const char*)&len, sizeof(unsigned));
	ofs.write((const char*)number, len+1);
	ofs.close();
	return true;
}

bool KBaseNumber::readFromFile(const char* FILE_NAME) {
	std::ifstream ifs(FILE_NAME, std::ios::binary);
	if (!ifs.is_open()) return false;

	unsigned len;
	ifs.read((char*)&k, sizeof(unsigned));
	ifs.read((char*)&len, sizeof(unsigned));

	if (len >= constants::MAX_NUM_LEN) len = constants::MAX_NUM_LEN - 1;

	ifs.read((char*)number, len);
	number[len] = '\0';

	ifs.close();
	return true;
}