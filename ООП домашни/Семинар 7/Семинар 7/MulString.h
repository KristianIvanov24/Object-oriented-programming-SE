#pragma once
#include "MyString.h"
#include <iostream>

class MulString
{
private:
	MyString str;
public:
	MulString(const MyString&);

	MulString& operator*=(unsigned);
	//MulString& operator=(const MulString&);
	MulString& operator%=(const MulString&);

	friend std::ostream& operator<<(std::ostream&, const MulString&);
	friend unsigned calculateStringWeight(const MulString&);
};

MulString operator*(const MulString& obj, unsigned k);
MulString operator%(const MulString&, const MulString&);

unsigned calculateStringWeight(const MyString&);
bool operator!=(const MulString&, const MulString&);

