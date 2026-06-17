#include "Dealership.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

Dealership::Dealership(const Car* cars, unsigned count) : carsCount(0) {
    for (unsigned i = 0; i < count && carsCount < CarConstants::MAX_CARS; i++)
        this->cars[carsCount++] = cars[i];
}

Dealership::Dealership(const Car* cars, unsigned count, EngineType engineType) : carsCount(0) {
    for (unsigned i = 0; i < count && carsCount < CarConstants::MAX_CARS; i++)
        if (cars[i].getEngineType() == engineType)
            this->cars[carsCount++] = cars[i];
}

Dealership::Dealership(const Car* cars, unsigned count, const char* model) : carsCount(0) {
    for (unsigned i = 0; i < count && carsCount < CarConstants::MAX_CARS; i++)
        if (strcmp(cars[i].getModel(), model) == 0)
            this->cars[carsCount++] = cars[i];
}

unsigned Dealership::getCarsCount() const {
    return carsCount;
}

bool Dealership::addCar(const Car& car) {
    if (carsCount >= CarConstants::MAX_CARS)
        return false;
    cars[carsCount++] = car;
    return true;
}

bool Dealership::removeCar(const char* brand, const char* model) {
    for (unsigned i = 0; i < carsCount; i++) {
        if (strcmp(cars[i].getBrand(), brand) == 0 &&
            strcmp(cars[i].getModel(), model) == 0) {
            cars[i] = cars[--carsCount];
            return true;
        }
    }
    return false;
}

void Dealership::testDriveAll() {
    for (unsigned i = 0; i < carsCount; i++)
        cars[i].drive(1);
}

void Dealership::printByModel(const char* model) const {
    bool found = false;
    for (unsigned i = 0; i < carsCount; i++) {
        if (strcmp(cars[i].getModel(), model) == 0) {
            cars[i].print();
            found = true;
        }
    }
    if (!found)
        std::cout << "No cars found with model: " << model << "\n";
}

Car* Dealership::getMostExpensive() {
    if (carsCount == 0)
        return nullptr;
    Car* best = &cars[0];
    for (unsigned i = 1; i < carsCount; i++)
        if (cars[i].getPrice() > best->getPrice())
            best = &cars[i];
    return best;
}

double Dealership::getAveragePriceByBrand(const Car& car) const {
    double total = 0.0;
    unsigned count = 0;
    for (unsigned i = 0; i < carsCount; i++) {
        if (strcmp(cars[i].getBrand(), car.getBrand()) == 0) {
            total += cars[i].getPrice();
            count++;
        }
    }
    if (count == 0)
        return 0.0;
    return total / count;
}