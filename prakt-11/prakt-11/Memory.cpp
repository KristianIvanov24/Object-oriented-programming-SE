#include "Memory.h"

Memory::Memory(const char* lable, unsigned short cap) : Component(lable)
{
	setCapacity;
}

void Memory::setCapacity(unsigned short cap)
{
	if (constants::MAXCapacity > cap && constants::MINCapacity < cap)
		capacity = cap;
	else
		throw std::invalid_argument("invalid capacity");
}

Component* Memory::clone() const
{
	return new Memory(*this);
}

double Memory::price() const
{
	return capacity * constants::GBPrice;
}

void Memory::output(std::ostream& os) const
{
	std::cout << lable << ' ' << capacity << '\n';
}

