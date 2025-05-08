#pragma once
#include "Device.h"

class SmartThermostat :public Device
{
public:
	SmartThermostat(const MyString& name, const MyString& manufacturer, double price, double currentTemp, double targetTemp);
	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;
	virtual SmartThermostat* clone() const override;

	double getTargetTemp() const;
	double getCurrentTemp() const;
	void setCurrentTemp(double ct);
	void setTargetTemp(double tt);
private:
	double currentTemp;
	double targetTemp;
};


