#pragma once
#include "Vehicle.h"

size_t constexpr startCapasity = 16;

class VehicleList
{
private:
	Vehicle** vehicleList;
	size_t capacity;
	size_t vehicleCnt;

	void resize();
	void copyFrom(const VehicleList& other);
	void moveFrom(VehicleList&& other);
	void free();
public:
	VehicleList();
	VehicleList(const VehicleList& other);
	VehicleList(VehicleList&& other);
	VehicleList& operator=(const VehicleList& other);
	VehicleList& operator=(VehicleList&& other);
	~VehicleList();

	void AddVehicle(Vehicle* vehicle);
	const Vehicle* operator[](size_t index) const;
	const Vehicle* getVehicleAtIndex(size_t index) const;
	const Vehicle* findVehicleByRegistration(const Registration& reg) const;
	bool isEmptyList() const;
	size_t getVehicleCount() const;
	size_t getCapacity() const;
};

