#pragma once
#include <iostream>
#include <stdexcept>
#pragma warning: disable(4996)

class Registration
{
private:
	char registration[9];
	
	bool isLetter(char ch) const;
	bool isDigit(char ch) const;
	bool isValidRegistration(const char* reg) const;
public:
	Registration(const char* reg);
	const char* getRegistration() const;

	friend bool operator==(const Registration& lhs, const Registration& rhs);
	friend bool operator!=(const Registration& lhs, const Registration& rhs);
};

