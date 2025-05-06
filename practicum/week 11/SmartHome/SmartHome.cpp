#include "SmartHome.h"
#include <utility>

void SmartHome::copyFrom(const SmartHome& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new Device * [capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void SmartHome::moveFrom(SmartHome&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

void SmartHome::free()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void SmartHome::resize(size_t newCapacity)
{
	Device** temp = new Device * [newCapacity] {nullptr};

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
	capacity = newCapacity;
}

SmartHome::SmartHome()
{
	capacity = INITIAL_CAPACITY;
	size = 0;
	data = new Device*[capacity]{ nullptr };
}

SmartHome::SmartHome(const SmartHome& other)
{
	copyFrom(other);
}

SmartHome& SmartHome::operator=(const SmartHome& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

SmartHome::SmartHome(SmartHome&& other) noexcept
{
	moveFrom(std::move(other));
}

SmartHome& SmartHome::operator=(SmartHome&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SmartHome::~SmartHome()
{
	free();
}

void SmartHome::addDevice(Device* obj)
{
	if (!obj)
	{
		return;
	}

	if (size == capacity)
	{
		resize(2 * capacity);
	}

	data[size++] = obj;
}

void SmartHome::addDevice(const Device& obj)
{
	addDevice(obj.clone());
}

void SmartHome::removeDevice(size_t idx)
{
	if (idx >= size)
	{
		return;
	}

	std::swap(data[idx], data[size - 1]);
	delete data[size - 1];
	data[size - 1] = nullptr;
	--size;
}

void SmartHome::printAllDevices() const
{
	for (size_t i = 0; i < size; i++)
	{
		data[i]->printDetails();
		
		if (i != size - 1)
		{
			std::cout << "-------------------------" << std::endl;
		}
	}
}

void SmartHome::turnOnAt(size_t idx) const
{
	if (idx >= size)
	{
		return;
	}

	data[idx]->turnOn();
}

void SmartHome::turnOffAt(size_t idx) const
{
	if (idx >= size)
	{
		return;
	}

	data[idx]->turnOff();
}

double SmartHome::findAveragePriceByManufacturer(const MyString& manufacturer) const
{
	int counter = 0;
	double total = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i]->getManufacturer() == manufacturer)
		{
			counter++;
			total += data[i]->getPrice();
		}
	}

	if (counter == 0)
	{
		return 0;
	}

	return total / counter;
}
