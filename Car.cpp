#include "Car.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

const char* engineTypeToString(EngineType type) {
    switch (type) {
    case EngineType::GASOLINE:    return "Gasoline";
    case EngineType::DIESEL:      return "Diesel";
    case EngineType::ELECTRICITY: return "Electric";
    default:                      return "Unknown";
    }
}

Car::Car(const char* brand, const char* model, EngineType engineType, double price) {
    strcpy(this->brand, brand);
    this->brand[CarConstants::MAX_NAME_LEN] = '\0';
    strcpy(this->model, model);
    this->model[CarConstants::MAX_NAME_LEN] = '\0';
    this->engineType = engineType;
    this->price = price;
    this->isUsed = false;
    this->mileage = 0;
}

void Car::drive(unsigned kilometers) {
    mileage += kilometers;
    if (!isUsed)
        isUsed = true;
    for (unsigned i = 0; i < kilometers; i++)
        price *= CarConstants::PRICE_REDUCTION_PER_KM;
}

void Car::print() const {
    std::cout << "Brand:   " << brand << "\n"
        << "Model:   " << model << "\n"
        << "Engine:  " << engineTypeToString(engineType) << "\n"
        << "Used:    " << (isUsed ? "Yes" : "No") << "\n"
        << "Mileage: " << mileage << " km\n"
        << "Price:   " << price << " lv\n"
        << "-------------------\n";
}

const char* Car::getBrand()        const { return brand; }
const char* Car::getModel()        const { return model; }
EngineType  Car::getEngineType()   const { return engineType; }
double      Car::getPrice()        const { return price; }
unsigned    Car::getMileage()      const { return mileage; }
bool        Car::getIsUsed()       const { return isUsed; }