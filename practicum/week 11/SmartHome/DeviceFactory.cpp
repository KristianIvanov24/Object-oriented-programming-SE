#include "DeviceFactory.h"

Device* DeviceFactory::createDevice()
{
    std::cout << "a- light, b- thermo, c- speaker"<<std::endl;
    char choice;
    std::cin >> choice;

    switch (choice) {
    case 'a':
        return createLight();
    case 'b':
        return createThermo();
    case 'c':
        return createSpeaker();
    default:
        return nullptr;
    }
}

SmartLight* DeviceFactory::createLight() {
    MyString name, manufacturer;
    double price = 0;
    unsigned brightnessLevel = 0;

    std::cin >> name >> manufacturer >> price >> brightnessLevel;
    return new SmartLight(name, manufacturer, price, brightnessLevel);
}

SmartThermostat* DeviceFactory::createThermo() {
    MyString name, manufacturer;
    double price= 0;
    double currentTemp = 0;
    double targetTemp = 0;

    std::cin >> name >> manufacturer >> price >> currentTemp >> targetTemp;
    return new SmartThermostat(name, manufacturer, price, currentTemp, targetTemp);
}

SmartSpeaker* DeviceFactory::createSpeaker()
{
    MyString name, manufacturer;
    double price = 0;
    unsigned volume = 0;

    std::cin >> name >> manufacturer >> price >> volume;
    return new SmartSpeaker(name, manufacturer, price, volume);
}
