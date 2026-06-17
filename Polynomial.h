#pragma once
class Polynomial
{
private:
	double* coeff;
	int n;
	void free();
	void copyFrom(const Polynomial& other);
public:
	Polynomial(int n);
	Polynomial(const Polynomial& other);
	Polynomial& operator=(const Polynomial& other);
	void setN(int n);
	void setCoeff(double* coeff);
	bool setCoeffOnIndex(int index,double num);
	double returnCoeffOnIndex(int index)const;
	double calculateResult(int x)const;
	void print()const;
	static Polynomial createConstant(double );

	~Polynomial();
};

