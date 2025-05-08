#pragma once
#include "Device.h"

class SmartLight: public Device
{
public:
	SmartLight(const MyString& name, const MyString& manufacturer, double price, unsigned brightnessLevel);
	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;
	virtual SmartLight* clone() const override;

	unsigned getBrightnessLevel() const;
	void setBrightnessLevel(unsigned bl);
private:
	unsigned brightnessLevel;
};

