#pragma once
#include <fstream>


class ArithmeticProgression {
	
	double* An;
	double diff;
	size_t len;

	void free();
	void copyFrom(const ArithmeticProgression&);

public:

	ArithmeticProgression();
	ArithmeticProgression(double, double);
	~ArithmeticProgression();
	ArithmeticProgression(const ArithmeticProgression&);
	ArithmeticProgression& operator=(const ArithmeticProgression&);

	friend std::ostream& operator<<(std::ostream&, const ArithmeticProgression&);
	friend std::istream& operator>>(std::istream&,  ArithmeticProgression&);

	friend ArithmeticProgression operator+(const ArithmeticProgression&, const ArithmeticProgression&);
	friend ArithmeticProgression operator-(const ArithmeticProgression&, const ArithmeticProgression&);

	ArithmeticProgression& operator+=(const ArithmeticProgression&);
	ArithmeticProgression& operator-=(const ArithmeticProgression&);

	double operator[](size_t idx) const; // return type const int& is also an option	
	double& operator[](size_t idx);

	int operator()()const;

};

