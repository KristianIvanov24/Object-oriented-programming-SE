#pragma once
#include "Component.h"

class Memory : public Component
{
private:
	unsigned short capacity;
public:
	Memory(const char* lable, unsigned short cap);

	void setCapacity (unsigned short cap);

	Component* clone() const override;
	double price() const override;
	void output(std::ostream& os) const override;

	~Memory() override = default;
};

