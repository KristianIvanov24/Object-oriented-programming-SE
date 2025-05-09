#include "SmartLight.h"

SmartLight::SmartLight(const MyString& name, const MyString& manufacturer, double price, unsigned brightnessLevel) : Device(name, manufacturer, price)
{
    setBrightnessLevel(brightnessLevel);
}

void SmartLight::turnOn() const
{
    std::cout << "Smart Light device turning on..." << std::endl;

}

void SmartLight::turnOff() const
{
    std::cout << "Smart Light device turning off..." << std::endl;

}

void SmartLight::printDetails() const
{
    std::cout << "Smart Light" << std::endl;
    Device::printDetails();
    std::cout << brightnessLevel << std::endl;
}

SmartLight* SmartLight::clone() const
{
    return new SmartLight(*this);
}

unsigned SmartLight::getBrightnessLevel() const
{
    return brightnessLevel;
}

void SmartLight::setBrightnessLevel(unsigned bl)
{
    brightnessLevel = bl;
}
