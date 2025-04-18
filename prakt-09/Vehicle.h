#pragma once
#include "Registration.h"
#include <utility>

class Vehicle
{
private:
	Registration registration;
	char* description;

	void copyFrom(const Vehicle& other);
	void moveFrom(Vehicle&& other);
	void free();
public:
	Registration getRegistration() const;
	const char* getDescription() const;

	Vehicle(const char* description, const Registration& registration);
	Vehicle(const Vehicle& other);
	Vehicle(Vehicle&& other) noexcept;
	Vehicle& operator=(const Vehicle& other);
	Vehicle& operator=(Vehicle&& other) noexcept;
	~Vehicle();
};

