#include "SmartSpeaker.h"

SmartSpeaker::SmartSpeaker(const MyString& name, const MyString& manufacturer, double price, unsigned volume) : 
    Device(name, manufacturer, price), volume(volume) {}

void SmartSpeaker::turnOn() const
{
    std::cout << "Smart Speaker device turning on..." << std::endl;
}

void SmartSpeaker::turnOff() const
{
    std::cout << "Smart Speaker device turning off..." << std::endl;
}

void SmartSpeaker::printDetails() const
{
    std::cout << "Smart Speaker" << std::endl;
    Device::printDetails();
    std::cout << volume << std::endl;
}

SmartSpeaker* SmartSpeaker::clone() const
{
    return new SmartSpeaker(*this);
}

void SmartSpeaker::setVolume(double volume)
{
    if (volume < 0)
        std::invalid_argument("invalid volume");

    this->volume = volume;
}

double SmartSpeaker::getVolume() const
{
    return volume;
}
