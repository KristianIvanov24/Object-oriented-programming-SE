#pragma once
#include "Device.h"

class SmartSpeaker : public Device
{
public:
	SmartSpeaker(const MyString& name, const MyString& manufacturer,
		double price, unsigned volume);

	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;
	virtual SmartSpeaker* clone() const override;

	void setVolume(double volume);
	double getVolume() const;

private:
	double volume;
};

