#pragma once
#include "MyString.h"

class Device
{
public:
	Device(const MyString& name, const MyString& manufacturer, double price);

	virtual void turnOn() const = 0;
	virtual void turnOff() const = 0;
	virtual void printDetails() const = 0;
	virtual Device* clone() const = 0;

	const MyString& getName() const;
	const MyString& getManufactuter() const;
	double getPrice() const;

	void setName(const MyString& name);
	void setManufacturer(const MyString& manufacturer);
	void setPrice(double price);

	virtual ~Device() = default;
protected:

	MyString name;
	MyString manufacturer;
	double price;
};

