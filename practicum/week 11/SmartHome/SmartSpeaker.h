#pragma once
#include "Device.h"

class SmartSpeaker : public Device
{
	unsigned volume = 0;

public:

	SmartSpeaker(const MyString& name, const MyString& manufacturer,
		double price, unsigned volume);

	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;
	virtual Device* clone() const override;
};

