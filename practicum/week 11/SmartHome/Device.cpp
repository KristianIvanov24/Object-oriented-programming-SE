#include "Device.h"

Device::Device(const MyString& name, const MyString& manufacturer, double price) :
	name(name), manufacturer(manufacturer), price(price)
{
}

void Device::printDetails() const
{
	std::cout << name << ", " << manufacturer << ", " << price << std::endl;
}

const MyString& Device::getName() const
{
	return name;
}

const MyString& Device::getManufacturer() const
{
	return manufacturer;
}

double Device::getPrice() const
{
	return price;
}
