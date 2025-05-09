#include "SmartThermostat.h"

SmartThermostat::SmartThermostat(const MyString& name, const MyString& manufacturer, double price, double currentTemp, double targetTemp): Device(name, manufacturer, price)
{
    setTargetTemp(targetTemp);
    setCurrentTemp(currentTemp);
}

void SmartThermostat::turnOn() const
{
    std::cout << "Smart Thermostat turning on..." << std::endl;

}

void SmartThermostat::turnOff() const
{
    std::cout << "Smart Thermostat turning off..." << std::endl;

}

void SmartThermostat::printDetails() const
{
    std::cout << "Smart Thermostat" << std::endl;
    Device::printDetails();
    std::cout << currentTemp << targetTemp << std::endl;
}

SmartThermostat* SmartThermostat::clone() const
{
    return new SmartThermostat(*this);
}

double SmartThermostat::getTargetTemp() const
{
    return targetTemp;
}

double SmartThermostat::getCurrentTemp() const
{
    return currentTemp;
}

void SmartThermostat::setCurrentTemp(double ct)
{
    currentTemp = ct;
}

void SmartThermostat::setTargetTemp(double tt)
{
    targetTemp = tt;
}
