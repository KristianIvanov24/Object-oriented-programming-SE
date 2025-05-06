#pragma once
#include "Device.h"
#include "SmartLight.h"
#include "SmartThermostat.h"
#include "SmartSpeaker.h"

class DeviceFactory
{
public:
	static Device* createDevice();
private:
	static SmartLight* createLight();
	static SmartThermostat* createThermo();
	static SmartSpeaker* createSpeaker();
};

