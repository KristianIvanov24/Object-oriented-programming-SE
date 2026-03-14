#pragma once

unsigned charToUnsigned(char sym)
{
	return sym - '0';
}

char unsignedToChar(unsigned sym)
{
	return sym + '0';
}

bool isUpper(char sym)
{
	return sym <= 'Z' && sym >= 'A';
}

char unsignedToUpperChar(unsigned sym)
{
	return sym + 'A'-10;
}

unsigned upperCharToUnsighned(char sym)
{
	return sym - 'A' + 10;
}

bool isDigit(char sym)
{
	return sym <= '9' && sym >= '0';
}

unsigned howManyDigitsIn(unsigned num,unsigned k)
{
	unsigned digits = 0;
	while (num > 0)
	{
		digits++;
		num /= k;
	}
	return digits;
}
