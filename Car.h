#pragma once
#include "Constants.h"

enum class EngineType {
    GASOLINE,
    DIESEL,
    ELECTRICITY
};

const char* engineTypeToString(EngineType type);

class Car {
    char brand[CarConstants::MAX_NAME_LEN + 1];
    char model[CarConstants::MAX_NAME_LEN + 1];
    EngineType engineType;
    bool isUsed;
    unsigned mileage;
    double price;

public:
    Car(const char* brand = "Unknown", const char* model = "Unknown",
        EngineType engineType = EngineType::GASOLINE, double price = 0.0);

    void drive(unsigned kilometers);
    void print() const;

    const char* getBrand() const;
    const char* getModel() const;
    EngineType getEngineType() const;
    double getPrice() const;
    unsigned getMileage() const;
    bool getIsUsed() const;
};