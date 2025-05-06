#pragma once
#include "MyString.h"
#include <iostream>

class Device
{
private:
	MyString name;
	MyString manufacturer;
	double price = 0;

public:

	Device(const MyString& name, const MyString& manufacturer, double price);

	virtual void turnOn() const = 0;
	virtual void turnOff() const = 0;
	virtual void printDetails() const = 0;
	virtual Device* clone() const = 0;

	const MyString& getName() const;
	const MyString& getManufacturer() const;
	double getPrice() const;

	virtual ~Device() = default;
};

