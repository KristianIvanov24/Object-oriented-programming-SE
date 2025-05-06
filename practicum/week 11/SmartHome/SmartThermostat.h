#pragma once
#include "Device.h"

class SmartThermostat : public Device
{
	double currentTemp = 0;
	double targetTemp = 0;

public:

	SmartThermostat(const MyString& name, const MyString& manufacturer, double price,
		double currentTemp, double targetTemp);

	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;
	virtual Device* clone() const override;
};

