#pragma once
#include "DeviceFactory.h"

static size_t const INITIAL_CAPACITY = 16;

class SmartHome
{
private:
	Device** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void copyFrom(const SmartHome& other);
	void free();
	void moveFrom(SmartHome&& other);

	void resize(size_t newCapacity);
public:
	SmartHome();
	SmartHome(const SmartHome& other);
	SmartHome(SmartHome&& other);
	SmartHome* operator= (const SmartHome& other);
	SmartHome* operator= (SmartHome&& other);
	~SmartHome();

	void addDevice(Device* toAdd);
	void addDevice(const Device& toAdd);

	void removeDevice(size_t index);

	void printAllDevices() const;
	void turnOffAt(size_t index);
	void turnOnAt(size_t index);

	double findAveragePriceByManufacturer(const MyString& manufacturer) const;
};

