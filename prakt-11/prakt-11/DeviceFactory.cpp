#include "DeviceFactory.h"

Device* DeviceFactory::createDevice()
{
    std::cout << "a - light, b - thermostat, c - speaker";
    char choice;
    std::cin >> choice;

    switch (choice)
    {
    case 'a':
        return createLight();
    case 'b':
        return createThermostat();
    case 'c':
        return createSpeaker();
    default:
        return nullptr;
    }
}

SmartLight* DeviceFactory::createLight()
{
    MyString name, manufacturer;
    double price;
    unsigned brightnessLevel;
    
    std::cin >> name >> manufacturer >> price >> brightnessLevel;
    return new SmartLight(name, manufacturer, price, brightnessLevel);
}

SmartThermostat* DeviceFactory::createThermostat()
{
    MyString name, manufacturer;
    double price;
    double currentTemp, targetTemp;

    std::cin >> name >> manufacturer >> price >> currentTemp >> targetTemp;
    return new SmartThermostat(name, manufacturer, price, currentTemp, targetTemp);
}

SmartSpeaker* DeviceFactory::createSpeaker()
{
    MyString name, manufacturer;
    double price;
    double volume;

    std::cin >> name >> manufacturer >> price >> volume;
    return new SmartSpeaker(name, manufacturer, price, volume);
}
