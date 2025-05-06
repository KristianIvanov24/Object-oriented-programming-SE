#pragma once
#include "Device.h"

class SmartHome
{
	Device** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	static constexpr size_t INITIAL_CAPACITY = 8;

	void copyFrom(const SmartHome& other);
	void moveFrom(SmartHome&& other);
	void free();

	void resize(size_t newCapacity);

public:
	SmartHome();
	SmartHome(const SmartHome& other);
	SmartHome& operator=(const SmartHome& other);
	SmartHome(SmartHome&& other) noexcept;
	SmartHome& operator=(SmartHome&& other) noexcept;
	~SmartHome();

	void addDevice(Device* obj);
	void addDevice(const Device& obj);

	void removeDevice(size_t idx);

	void printAllDevices() const;
	void turnOnAt(size_t idx) const;
	void turnOffAt(size_t idx) const;

	double findAveragePriceByManufacturer(const MyString& manufacturer) const;
};

