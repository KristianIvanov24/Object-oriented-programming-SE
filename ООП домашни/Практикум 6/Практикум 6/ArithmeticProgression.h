#pragma once
class ArithmeticProgression
{
private:
	int firstMember = 1;
	int diff = 1 ;
public:
	ArithmeticProgression();
	ArithmeticProgression(int, int);

	ArithmeticProgression& operator+=(const ArithmeticProgression&);
	ArithmeticProgression& operator-=(const ArithmeticProgression&);

	friend ArithmeticProgression operator^(const ArithmeticProgression&, unsigned);

	int operator[](unsigned) const;

	int operator()(unsigned) const;
};


ArithmeticProgression operator-(const ArithmeticProgression&, const ArithmeticProgression&);
ArithmeticProgression operator+(const ArithmeticProgression&, const ArithmeticProgression&);

