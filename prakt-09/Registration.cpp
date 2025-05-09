
#include "Registration.h"

bool Registration::isLetter(char ch) const
{
	return 'A' <= ch && ch <= 'Z';
}

bool Registration::isDigit(char ch) const
{
	return '0' <= ch && ch <= '9';
}

bool Registration::isValidRegistration(const char* reg) const
{
	bool firstLetter = true;
	int len = strlen(reg);
	if (len == 8) firstLetter == true;
	if (len == 7) firstLetter == false;

	for (int i = 0; i <= len; i++)
	{
		if (i < firstLetter + 1)
		{
			if (!isLetter(reg[i]))
				return false;
		}
		if (firstLetter < i && i <= firstLetter + 4)
		{
			if (!isDigit(reg[i]))
				return false;
		}
		else
		{
			if (!isLetter(reg[i]))
				return false;
		}
	}

	return true;
}

Registration::Registration(const char* reg)
{
	if(!isValidRegistration(reg))
		throw std::invalid_argument("invalid registration");

	strcpy(registration, reg);
}

bool operator==(const Registration& lhs, const Registration& rhs)
{
	return !strcmp(lhs.registration, rhs.registration);
}

bool operator!=(const Registration& lhs, const Registration& rhs)
{
	return !(lhs==rhs);
}

const char* Registration::getRegistration() const 
{
	return registration;
}
