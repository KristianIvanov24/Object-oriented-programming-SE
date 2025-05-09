#include "Device.h"
#include <iostream>
#include <stdexcept>

Device::Device(const MyString& name, const MyString& manufacturer, double price) :
	name(name), manufacturer(manufacturer), price(price) {}

const MyString& Device::getName() const
{
	return name;
}

const MyString& Device::getManufactuter() const
{
	return manufacturer;
}

double Device::getPrice() const
{
	return 0.0;
}

void Device::setName(const MyString& name)
{
	if (name != " ")
		this->name = name;

	else
		std::invalid_argument("invalid name");
}

void Device::setManufacturer(const MyString& manufacturer)
{

	if (name != " ")
		this->manufacturer = manufacturer;

	else
		std::invalid_argument("invalid manufacturer");
}

void Device::setPrice(double price)
{
	if (price < 0)
		std::invalid_argument("invalid price");
	else
		this->price = price;
}



