#include <iostream>
#include <cstring>

enum class Engine;

namespace Constants
{
    const size_t MAX_BRAND_LEN = 100;
    const size_t MAX_MODEL_LEN = 100;
    const size_t MAX_CAR_COUNT = 1000;
    const char *DEFAULT_NAME = "Unknown";
    const Engine DEFAULT_ENGINE = Engine::GASOLINE;

}

namespace Validation
{
    bool isValidBrand(const char *brand)
    {
        return strnlen(brand, Constants::MAX_BRAND_LEN + 1) <= Constants::MAX_BRAND_LEN;
    }

    bool isValidModel(const char *model)
    {
        return strnlen(model, Constants::MAX_MODEL_LEN + 1) <= Constants::MAX_MODEL_LEN;
    }

    bool isValidPrice(double price)
    {
        return price >= 0;
    }

    bool isValidCarCount(size_t carCount)
    {
        return carCount <= Constants::MAX_CAR_COUNT;
    }
}

enum class Engine
{
    GASOLINE,
    DIESEL,
    ELECTRICITY
};

const char *engineToString(Engine engine)
{
    switch (engine)
    {
    case Engine::GASOLINE:
        return "GASOLINE";
    case Engine::DIESEL:
        return "DIESEL";
    case Engine::ELECTRICITY:
        return "ELECTRICITY";
    default:
        return "Unknown";
    }
}

class Car
{
    char brand[Constants::MAX_BRAND_LEN + 1];
    char model[Constants::MAX_MODEL_LEN + 1];
    Engine engine;
    bool used;
    unsigned mileage;
    double price;

public:
    Car() : engine(Constants::DEFAULT_ENGINE), used(false), mileage(0), price(0)
    {
        setBrand(Constants::DEFAULT_NAME);
        setModel(Constants::DEFAULT_NAME);
    }

    Car(const char *brand, const char *model, Engine engine, double price) : engine(engine), used(false), mileage(0)
    {
        setBrand(brand);
        setModel(model);
        setPrice(price);
    }

    void print() const
    {
        std::cout << brand << " " << model << " " << engineToString(engine) << " " 
        << (used ? "Used" : "New") << " " << mileage << "km " << price << std::endl;
    }

    Engine getEngine() const
    {
        return engine;
    }

    const char *getModel() const
    {
        return model;
    }

    const char *getBrand() const
    {
        return brand;
    }

    double getPrice() const
    {
        return price;
    }

    void setBrand(const char *brand)
    {
        if (!Validation::isValidBrand(brand))
        {
            strncpy(this->brand, Constants::DEFAULT_NAME, Constants::MAX_BRAND_LEN);
            return;
        }
        strncpy(this->brand, brand, Constants::MAX_BRAND_LEN);
        this->brand[Constants::MAX_BRAND_LEN] = '\0';
    }

    void setModel(const char *model)
    {
        if (!Validation::isValidModel(model))
        {
            strncpy(this->model, Constants::DEFAULT_NAME, Constants::MAX_MODEL_LEN);
            return;
        }
        strncpy(this->model, model, Constants::MAX_MODEL_LEN);
        this->model[Constants::MAX_MODEL_LEN] = '\0';
    }

    void setPrice(const double price)
    {
        if (!Validation::isValidPrice(price))
        {
            this->price = 0;
            return;
        }
        this->price = price;
    }

    void drive(unsigned kilometers)
    {
        used = true;
        mileage += kilometers;
        price *= (1 - 0.001 * kilometers);
    }
};

class DealerShip
{
    Car cars[Constants::MAX_CAR_COUNT];
    size_t carCount;

public:
    DealerShip(Car *cars, size_t carCount)
    {
        setCarCount(carCount);
        for (size_t i = 0; i < carCount; i++)
        {
            this->cars[i] = cars[i];
        }
    }

    DealerShip(Car *cars, size_t n, Engine engine)
    {
        size_t carCount;
        for (size_t i = 0, carCount = 0; i < n && carCount < Constants::MAX_CAR_COUNT; i++)
        {
            if (cars[i].getEngine() == engine)
            {
                this->cars[carCount++] = cars[i];
            }
        }
        setCarCount(carCount);
    }

    DealerShip(Car *cars, size_t n, const char *model)
    {
        size_t carCount;
        for (size_t i = 0, carCount = 0; i < n && carCount < Constants::MAX_CAR_COUNT; i++)
        {
            if (strncmp(cars[i].getModel(), model, Constants::MAX_MODEL_LEN) == 0)
            {
                this->cars[carCount++] = cars[i];
            }
        }
        setCarCount(carCount);
    }

    void setCarCount(size_t carCount)
    {
        if (!Validation::isValidCarCount(carCount))
        {
            carCount = 0;
            return;
        }
        this->carCount = carCount;
    }

    size_t getCarCount() const
    {
        return carCount;
    }

    bool addCar(const Car &car)
    {
        if (carCount >= Constants::MAX_CAR_COUNT)
        {
            return false;
        }

        cars[carCount++] = car;
        return true;
    }

    bool deleteCar(const char *brand, const char *model)
    {
        bool found = false;
        for (size_t i = 0; i < carCount; )
        {
            Car &car = cars[i];
            if (strncmp(car.getBrand(), brand, Constants::MAX_BRAND_LEN) == 0 
                && strncmp(car.getModel(), model, Constants::MAX_MODEL_LEN) == 0)
            {
                car = cars[carCount - 1];
                carCount--;
                found = true;
                continue;
            }
            i++;
        }
        return found;
    }

    void testDrive()
    {
        for (size_t i = 0; i < carCount; i++)
        {
            cars[i].drive(1);
        }
    }

    void printByModel(const char *model) const
    {
        for (size_t i = 0; i < carCount; i++)
        {
            if (strncmp(cars[i].getModel(), model, Constants::MAX_MODEL_LEN) == 0)
            {
                cars[i].print();
            }
        }
    }

    Car highestPrice() const
    {
        Car car = Car();
        for (size_t i = 0; i < carCount; i++)
        {
            if (car.getPrice() < cars[i].getPrice())
            {
                car = cars[i];
            }
        }
        return car;
    }

    double averageByModel(const Car &car) const
    {
        double sum = 0;
        size_t count = 0;
        for (size_t i = 0; i < carCount; i++)
        {
            if (strncmp(cars[i].getModel(), car.getModel(), Constants::MAX_MODEL_LEN) == 0)
            {
                sum += cars[i].getPrice();
                count++;
            }
        }
        if (count == 0) return 0;
        return sum / carCount;
    }
};