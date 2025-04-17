#include "MulString.h"
#include "Constants.h"

MulString::MulString(const MyString& obj)
{
	str = obj;
}

MulString& MulString::operator*=(unsigned k)
{
	MyString copy = str;

	while (k)
	{
		str += copy;
		k--;
	}

	return *this;
}

//MulString& MulString::operator=(const MulString& other)
//{
//	if (this != &other)
//	{
//		str = other.str;
//	}
//
//	return *this;
//}

void markSet(uint8_t* set, const MyString& str, size_t& uniqueCharacters)
{
	for (size_t i = 0; i < str.getSize(); i++)
	{
		char current = str[i];
		size_t positionInArray = current / Constants::BITS_IN_BYTE;
		size_t positionInByte = current % Constants::BITS_IN_BYTE;
		uint8_t mask = 1;
		mask <<= (Constants::BITS_IN_BYTE - 1 - positionInByte);

		if (!(set[positionInArray] & mask))
		{
			set[positionInArray] ^= mask;
			uniqueCharacters++;
		}
	}
}

MulString& MulString::operator%=(const MulString& other)
{
	size_t setLen = 256 / Constants::BITS_IN_BYTE;

	uint8_t* characterSet = new uint8_t[setLen]{ 0 };
	size_t uniqueCharacters = 0;

	markSet(characterSet, str, uniqueCharacters);
	markSet(characterSet, other.str, uniqueCharacters);

	char* newStr = new char[uniqueCharacters + 1];
	size_t counter = 0;

	for (size_t positionInArray = 0; positionInArray < setLen; positionInArray++)
	{
		uint8_t mask = 1;
		mask <<= (Constants::BITS_IN_BYTE - 1);
		for (size_t positionInByte = 0;
			positionInByte < Constants::BITS_IN_BYTE; positionInByte++)
		{
			if (characterSet[positionInArray] & mask)
			{
				newStr[counter++] = positionInArray * Constants::BITS_IN_BYTE +
					positionInByte;
			}
			mask >>= 1;
		}
	}

	newStr[counter++] = '\0';
	str = MyString(newStr);

	delete[] characterSet;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MulString& obj)
{
	os << obj.str;

	return os;
}

MulString operator*(const MulString& obj, unsigned k)
{
	MulString res = obj;
	res *= k;

	return res;
}

unsigned calculateStringWeight(const MyString& obj)
{
	unsigned res = 0;

	for (size_t i = 0; i < obj.getSize(); i++)
	{
		res += obj.c_str()[i];
	}

	return res;
}

unsigned calculateStringWeight(const MulString& obj)
{
	return calculateStringWeight(obj.str);
}

bool operator!=(const MulString& first, const MulString& second)
{
	return (calculateStringWeight(first) != calculateStringWeight(second));
}

MulString operator%(const MulString& first, const MulString& second)
{
	MulString res = first;
	res %= second;

	return res;
}
