#pragma once
#include "Car.h"

class Dealership {
    Car cars[CarConstants::MAX_CARS];
    unsigned carsCount;

public:
    Dealership(const Car* cars, unsigned count);
    Dealership(const Car* cars, unsigned count, EngineType engineType);
    Dealership(const Car* cars, unsigned count, const char* model);

    unsigned getCarsCount() const;

    bool addCar(const Car& car);
    bool removeCar(const char* brand, const char* model);

    void testDriveAll();

    void printByModel(const char* model) const;

    Car* getMostExpensive();

    double getAveragePriceByBrand(const Car& car) const;
};