#include "VehicleList.h"

void VehicleList::resize()
{
	size_t newCapacity = capacity * 2;
	Vehicle** temp = new Vehicle * [newCapacity] {nullptr};
	for (int i = 0; i < capacity; i++)
	{
		temp[i] = vehicleList[i];
	}

	delete[] vehicleList;
	vehicleList = temp;
	temp = nullptr;
	capacity = newCapacity;
}

void VehicleList::copyFrom(const VehicleList& other)
{
	this->capacity = other.capacity;
	this->vehicleCnt = other.vehicleCnt;
	vehicleList = new Vehicle * [capacity];
	for (int i = 0; i < capacity; i++)
	{
		vehicleList[i] = new Vehicle(*other.vehicleList[i]);
	}
}

void VehicleList::moveFrom(VehicleList&& other)
{
	this->capacity = other.capacity;
	this->vehicleCnt = other.vehicleCnt;
	vehicleList = other.vehicleList;
	other.vehicleList = nullptr;
}

void VehicleList::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete vehicleList[i];
	}
	delete[] vehicleList;
	vehicleList = nullptr;
}

VehicleList::VehicleList()
{
	capacity = startCapasity;
	vehicleCnt = 0;
	vehicleList = new Vehicle* [capacity] {nullptr};
}

VehicleList::VehicleList(const VehicleList& other)
{
	copyFrom(other);
}

VehicleList::VehicleList(VehicleList&& other)
{
	moveFrom(std::move(other));
}

VehicleList& VehicleList::operator=(const VehicleList& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

VehicleList& VehicleList::operator=(VehicleList&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

VehicleList::~VehicleList()
{
	free();
}

void VehicleList::AddVehicle(Vehicle* vehicle)
{
	if (vehicleCnt == capacity)
		resize();

	vehicleList[vehicleCnt++] = vehicle;
}

const Vehicle* VehicleList::operator[](size_t index) const
{
	return vehicleList[index];
}

const Vehicle* VehicleList::getVehicleAtIndex(size_t index) const
{
	if(index >= vehicleCnt)
		return nullptr;

	return vehicleList[index];
}

const Vehicle* VehicleList::findVehicleByRegistration(const Registration& reg) const
{
	for (int i = 0; i < vehicleCnt; i++)
	{
		if ( reg == vehicleList[i]->getRegistration())
			return vehicleList[i];
	}
	return nullptr;
}

bool VehicleList::isEmptyList() const
{
	return vehicleCnt;
}

size_t VehicleList::getVehicleCount() const
{
	return vehicleCnt;
}

size_t VehicleList::getCapacity() const
{
	return capacity;
}

