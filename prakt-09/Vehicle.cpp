#include "Vehicle.h"

void Vehicle::copyFrom(const Vehicle& other)
{
	int len = strlen(other.description);
	description = new char[len + 1];
	strcpy(description, other.description);
}

void Vehicle::moveFrom(Vehicle&& other)
{
	description = other.description;
	other.description = nullptr;
}

void Vehicle::free()
{
	delete[] description;
}

Registration Vehicle::getRegistration() const
{
	return registration;
}

const char* Vehicle::getDescription() const
{
	return description;
}

Vehicle::Vehicle(const char* description, const Registration& registration) : registration(registration)
{
	int len = strlen(description);
	this->description = new char[len + 1];
	strcpy(this->description, description);
}

Vehicle::Vehicle(const Vehicle& other) : registration(registration)
{
	copyFrom(other);
}

Vehicle::Vehicle(Vehicle&& other) noexcept : registration(std::move(registration))
{
	moveFrom(std::move(other));
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Vehicle::~Vehicle()
{
	free();
}
