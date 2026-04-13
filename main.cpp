#include "Dealership.h"
#include <iostream>

int main() {
    Car c1("Toyota", "Corolla", EngineType::GASOLINE, 25000);
    Car c2("Toyota", "Yaris", EngineType::DIESEL, 18000);
    Car c3("BMW", "M3", EngineType::GASOLINE, 80000);
    Car c4("Tesla", "Model 3", EngineType::ELECTRICITY, 60000);
    Car c5("Toyota", "Supra", EngineType::GASOLINE, 55000);

    Car allCars[] = { c1, c2, c3, c4, c5 };
    unsigned count = 5;

    std::cout << "=== All cars ===\n";
    Dealership d1(allCars, count);
    d1.printByModel("Corolla");

    std::cout << "=== Only Gasoline ===\n";
    Dealership d2(allCars, count, EngineType::GASOLINE);
    std::cout << "Count: " << d2.getCarsCount() << "\n";

    std::cout << "\n=== Test drive all ===\n";
    d1.testDriveAll();

    std::cout << "\n=== Most expensive ===\n";
    Car* best = d1.getMostExpensive();
    if (best) best->print();

    std::cout << "\n=== Avg price Toyota ===\n";
    std::cout << d1.getAveragePriceByBrand(c1) << " lv\n";

    std::cout << "\n=== Remove Corolla ===\n";
    d1.removeCar("Toyota", "Corolla");
    std::cout << "Cars remaining: " << d1.getCarsCount() << "\n";
}