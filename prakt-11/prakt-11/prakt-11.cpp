#include "SmartHome.h"
#include "Device.h"
#include "DeviceFactory.h"
#include <iostream>

int main()
{
    SmartHome home;
    home.addDevice(DeviceFactory::createDevice());
	home.addDevice(DeviceFactory::createDevice());
	home.addDevice(DeviceFactory::createDevice());

	home.printAllDevices();

	return 0;
}
