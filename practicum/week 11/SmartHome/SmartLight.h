#pragma once
#include "Device.h"

class SmartLight : public Device
{
	unsigned brightnessLevel = 0;

public:

	SmartLight(const MyString& name, const MyString& manufacturer, double price, unsigned brightnessLevel);

	virtual void turnOn() const override;

	virtual void turnOff() const override;

	virtual void printDetails() const override;

	virtual Device* clone() const override;

};

