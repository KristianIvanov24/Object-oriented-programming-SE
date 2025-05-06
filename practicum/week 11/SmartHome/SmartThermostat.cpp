#include "SmartThermostat.h"

SmartThermostat::SmartThermostat(const MyString& name, const MyString& manufacturer, double price, double currentTemp, double targetTemp):
    Device(name, manufacturer, price), currentTemp(currentTemp), targetTemp(targetTemp)
{
}

void SmartThermostat::turnOn() const
{
    std::cout << "Smart Thermostat device turning on..." << std::endl;
}

void SmartThermostat::turnOff() const
{
    std::cout << "Smart Thermostat device turning off..." << std::endl;
}

void SmartThermostat::printDetails() const
{
    std::cout << "Smart Thermostat" << std::endl;
    Device::printDetails();
    std::cout << targetTemp << ", " << currentTemp << std::endl;
}

Device* SmartThermostat::clone() const
{
    return new SmartThermostat(*this);
}
