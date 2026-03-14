#pragma once
#include "Constants.h"

class KBaseNumber
{
private:
	char number[constants::MAX_NUM_LEN+1];
	unsigned k;

	unsigned toDecimal() const;
	KBaseNumber toNewSystem(unsigned newK) const;
public:
	KBaseNumber() = default;
	KBaseNumber(const char* num, unsigned k);
	void setNumber(const char* num);
	void setSystem(unsigned k);
	void print() const;
	void printConvertedTo(unsigned newK) const;
	int compareWith(KBaseNumber& toCompare) const;
	void update(const char* newNum, unsigned newK);
	bool saveToFile(const char* FILE_NAME)const;
	bool readFromFile(const char* FILE_NAME);

};

