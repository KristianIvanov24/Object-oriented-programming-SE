#include <iostream>
#include "DeviceFactory.h"
#include "SmartHome.h"

int main() 
{
	SmartHome home;
	home.addDevice(DeviceFactory::createDevice());
	home.addDevice(DeviceFactory::createDevice());
	home.addDevice(DeviceFactory::createDevice());

	home.printAllDevices();

	return 0;
}