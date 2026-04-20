#pragma once
#include "Constants.h"

class KBaseNumber {
private:
	char number[Constants::MAX_LEN+1];
	int base;
	long long toDecimal() const;

	static void fromDecimal(long long value, int base, char* out);
public:
	KBaseNumber();
	KBaseNumber(const char* digits, int base);

	int compareWith(const KBaseNumber& other) const;
	void update(const char* digits, int base);
	void print() const;
	void printConvertedTo(int targetBase) const;
	void saveToFile(const char* filename) const;
	void readFromFile(const char* filename);
};