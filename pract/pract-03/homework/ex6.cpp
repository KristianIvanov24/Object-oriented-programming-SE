#include <iostream>
#include <fstream>

const size_t MAX_NAME_LEN = 24;
const size_t MAX_FEES = 20;

enum class Brand
{
    PORSCHE,
    FERRARI,
    BMW
};

struct Car
{
    Brand brand;
    char owner[MAX_NAME_LEN];
    double averageSpeed;
    double fees[MAX_FEES];
    unsigned numberOfFees;
};

double totalFees(const Car &car)
{
    double total = 0;
    for (size_t i = 0; i < car.numberOfFees; i++)
    {
        total += car.fees[i];
    }
    return total;
}

void addFee(Car &car, double fee)
{
    if (car.numberOfFees == MAX_FEES)
    {
        std::cout << "Max fees reached!" << std::endl;
        return;
    }

    car.fees[car.numberOfFees++] = fee;
}

const char *brandToString(Brand brand)
{
    switch (brand)
    {
    case Brand::PORSCHE:
        return "Porsche";
    case Brand::BMW:
        return "BMW";
    case Brand::FERRARI:
        return "Ferrari";
    default:
        return "??";
    }
}

void printFees(const Car &car)
{
    for (size_t i = 0; i < car.numberOfFees; i++)
    {
        std::cout << car.fees[i] << " ";
    }
}

void printCar(const Car &car)
{
    std::cout << "Brand: " << brandToString(car.brand)
              << "\nOwner: " << car.owner
              << "\nAverage speed: " << car.averageSpeed
              << "\nNumber of fees: " << car.numberOfFees
              << "\nFees: ";
    printFees(car);
}

Car read(std::ifstream &f)
{
    Car car{};
    f.read((char *)&car, sizeof(car));
    return car;
}

void write(std::ofstream &f, const Car &car)
{
    f.write((char *)&car, sizeof(car));
}

size_t getFileSize(std::ifstream &f)
{
    size_t current_pos = f.tellg();
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    f.seekg(current_pos);
    return size;
}

void sort(Car *cars, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (cars[j].averageSpeed > cars[j + 1].averageSpeed)
            {
                std::swap(cars[j], cars[j + 1]);
            }
        }
    }
}

void sortAndSave(const char *fileName)
{
    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Error!" << std::endl;
        return;
    }

    size_t fileSize = getFileSize(in);
    size_t numberOfCars = fileSize / sizeof(Car);
    Car *cars = new Car[numberOfCars];

    for (size_t i = 0; i < numberOfCars; i++)
    {
        cars[i] = read(in);
    }
    in.close();

    sort(cars, numberOfCars);

    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open())
    {
        std::cout << "Error!" << std::endl;
        delete[] cars;
        return;
    }

    for (size_t i = 0; i < numberOfCars; i++)
    {
        write(out, cars[i]);
    }
    delete[] cars;
}