#pragma once

class SpecialCustomFunction {
private:
	int* specialValues;
	size_t size;
	int (*funcPrint)(int);

	void copyFrom(const SpecialCustomFunction& other);
	void free();
	bool isSpecial(int x) const;

public:
	SpecialCustomFunction(int* arr, size_t n, int (*f)(int));
	SpecialCustomFunction(const SpecialCustomFunction& other);
	SpecialCustomFunction& operator=(const SpecialCustomFunction& other);
	~SpecialCustomFunction();

	int operator()(int x) const;
	
	SpecialCustomFunction& operator++();
	SpecialCustomFunction operator++(int x);

	SpecialCustomFunction& operator--();
	SpecialCustomFunction operator--(int x);

	SpecialCustomFunction operator!() const;
};