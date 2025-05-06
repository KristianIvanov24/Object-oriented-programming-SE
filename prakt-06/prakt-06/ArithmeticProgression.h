#pragma once
#include "Vector.h"

class ArithmeticProgression
{
private:
	int first;
	int q;
public:
	ArithmeticProgression();
	ArithmeticProgression(int first, int q);

	ArithmeticProgression& operator+=(const ArithmeticProgression& other);
	ArithmeticProgression& operator-=(const ArithmeticProgression& other);
	ArithmeticProgression& operator>>(unsigned n);
	int operator[](unsigned n);
	int operator()(unsigned n);
};

ArithmeticProgression& operator+(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs);
ArithmeticProgression& operator-(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs);
