#pragma once
#include <iostream>
#include <stdexcept>
 
namespace constants
{
	unsigned short constexpr MINCoresCnt = 1, MAXCoresCnt = 8;
	double constexpr coresPrice = 29.99;
	unsigned short constexpr MINCapacity = 1, MAXCapacity = 100000;
	double constexpr GBPrice = 89.99;
}

class Component
{
protected:
	char* lable;

	void free();
	void moveFrom(Component&& other) noexcept;
	void copyFrom(const Component& other);
public:
	Component();
	Component(const char* lable);
	Component(const Component& other);
	Component(Component&& other) noexcept;
	Component& operator= (const Component& other);
	Component& operator= (Component&& other) noexcept;
	virtual ~Component();

	const char* getLable() const;

	virtual Component* clone() const = 0;
	virtual double price() const = 0;
	virtual void output(std::ostream& os) const = 0;
};

