#pragma once
#include "Component.h"

class CPU : public Component
{
private:
	unsigned short cores;
	unsigned short clockSpeed;
public:
	CPU(const char* lable, unsigned short cores, unsigned short speed);

	void setCores(unsigned short cores);

	Component* clone() const override;
	double price() const override;
	void output(std::ostream& os) const override;
	~CPU() override = default;;
};

