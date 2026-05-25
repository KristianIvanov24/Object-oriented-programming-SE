#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

enum class EngineType {
    GASOLINE,
    DIESEL,
    ELECTRICITY
};

namespace constants {
    const size_t MAX_SIZE_BRAND = 100;
	const size_t MAX_SIZE_MODEL = 100;

	const char* DEFAULT_NAME = "Unknown";
	const EngineType DEFAULT_ENGINE_TYPE = EngineType::GASOLINE;
	const double DEFAULT_PRICE = 0.0;
	const unsigned DEFAULT_MILEAGE = 0;
	const bool DEFAULT_IS_USED = false;

	const size_t MAX_CARS_IN_DEALERSHIP = 1000;
}

namespace validation {
    bool isValidPrice(double price) {
        return price > 0;
    }

    bool isValidBrandOrModel(const char* str, size_t maxSize) {
        return str != nullptr && strlen(str) > 0 && strlen(str) <= maxSize;
	}

    bool isValidEngineType(EngineType type) {
        return type == EngineType::GASOLINE
            || type == EngineType::DIESEL
            || type == EngineType::ELECTRICITY;
    }

    bool isValidDealershipSize(size_t size) {
        return size > 0 && size <= constants::MAX_CARS_IN_DEALERSHIP;
	}
}

const char* engineTypeToString(EngineType type) {
    switch (type) {
        case EngineType::GASOLINE: 
            return "Gasoline";
        case EngineType::DIESEL: 
            return "Diesel";
        case EngineType::ELECTRICITY: 
            return "Electricity";
        default: return "Unknown";
    }
}

class Car {
private:

    char brand[constants::MAX_SIZE_BRAND + 1];
    char model[constants::MAX_SIZE_MODEL + 1];
    double price;
    unsigned mileage;
	EngineType engineType;
    bool isUsed;

    void setBrand(const char* brand) {
        if (validation::isValidBrandOrModel(brand, constants::MAX_SIZE_BRAND)) {
            strncpy(this->brand, brand, constants::MAX_SIZE_BRAND);
        }
        else {
            strncpy(this->brand, constants::DEFAULT_NAME, constants::MAX_SIZE_BRAND);
        }
    }

    void setModel(const char* model) {
        if (validation::isValidBrandOrModel(model, constants::MAX_SIZE_MODEL)) {
            strncpy(this->model, model, constants::MAX_SIZE_MODEL);
        }
        else {
            strncpy(this->model, constants::DEFAULT_NAME, constants::MAX_SIZE_MODEL);
        }
    }
    void setPrice(double price) {
        if (validation::isValidPrice(price)) {
            this->price = price;
        }
        else {
            this->price = constants::DEFAULT_PRICE;
        }
    }

    void setEngineType(EngineType type) {
        if (validation::isValidEngineType(type)) {
            this->engineType = type;
        }
        else {
            this->engineType = constants::DEFAULT_ENGINE_TYPE;
        }
    }

public:

	Car() : price(constants::DEFAULT_PRICE), engineType(constants::DEFAULT_ENGINE_TYPE), 
            isUsed(constants::DEFAULT_IS_USED), mileage(constants::DEFAULT_MILEAGE) {
		setBrand(constants::DEFAULT_NAME);
		setModel(constants::DEFAULT_NAME);
    }

    Car(const char* brand, const char* model, double price, EngineType engineType) : 
        isUsed(constants::DEFAULT_IS_USED), mileage(constants::DEFAULT_MILEAGE) {
		setBrand(brand);
        setModel(model);
        setPrice(price);
		setEngineType(engineType);
    }

    void printCarInfo() const {
        std::cout << "Brand: " << brand << " -> "
                  << "Model: " << model << " -> "
                  << "Price: " << price << " -> "
                  << "Engine Type: " << engineTypeToString(engineType) << " -> "
                  << "Mileage: " << mileage << " km -> "
                  << "Used: " << (isUsed ? "Yes" : "No") << std::endl << std::endl;
    }

    void drive (unsigned kilometers) {
        this->isUsed = true;
		this->mileage += kilometers;

		setPrice(price * pow(0.999, kilometers));
    }

    EngineType getEngineType() const {
        return engineType;
	}

    const char* getModel() const {
        return model;
	}

    const char* getBrand() const {
        return brand;
    }

    double getPrice() const {
        return price;
	}

};

class Dealership {
private:	

    Car cars[constants::MAX_CARS_IN_DEALERSHIP + 1];
    unsigned carsCount;

    void removeCarAtIndex(size_t index) {
        for (size_t j = index; j < carsCount - 1; j++) {
            cars[j] = cars[j + 1];
        }

        carsCount--;
    }

public:

    Dealership(const Car* cars, size_t size) {
        if (validation::isValidDealershipSize(size)) {
            for (size_t i = 0; i < size; i++) {
                this->cars[i] = cars[i];
            }
            this->carsCount = size;
        }
        else {
            this->carsCount = 0;
        }
    }

    Dealership(const Car* cars, size_t size, EngineType engineType) : carsCount(0){
		for(size_t i = 0; i < size; i++) {
            if (cars[i].getEngineType() == engineType) {
                this->cars[carsCount++] = cars[i];
            }

            if(carsCount == constants::MAX_CARS_IN_DEALERSHIP) {
                break;
			}
		}
    }

    Dealership(const Car* cars, size_t size, const char* model) : carsCount(0){
        for (size_t i = 0; i < size; i++) {
            if (strcmp(cars[i].getModel(), model) == 0) {
                this->cars[carsCount++] = cars[i];
            }
            if (carsCount == constants::MAX_CARS_IN_DEALERSHIP) {
                break;
            }
        }
    }

    unsigned getCarsCount() const {
        return carsCount;
	}

    void addCar(const Car& car) {
        if(validation::isValidDealershipSize(carsCount + 1)) {
            cars[carsCount++] = car;
		}
	}

    void removeCarByBrandAndModel(const char* brand, const char* model) {
        for (size_t i = 0; i < carsCount; i++) {
            if (strcmp(cars[i].getModel(), model) == 0 && strcmp(cars[i].getBrand(), brand) == 0) {
        
				removeCarAtIndex(i);
                break;
            }
        }
	}

    void testDriveCars() {
        for(size_t i = 0; i < carsCount; i++) {
            cars[i].drive(1);
		}
    }

    void printCarsByModel(const char* model) const {
        for (size_t i = 0; i < carsCount; i++) {
            if (strcmp(cars[i].getModel(), model) == 0) {
                cars[i].printCarInfo();
            }
        }
	}

    Car getMostExpensiveCar() const {
        if (carsCount == 0) {
            return Car();
        }

        Car res = cars[0];
        for (size_t i = 1; i < carsCount; i++) {
            if (cars[i].getPrice() > res.getPrice()) {
                res = cars[i];
            }
        }
        return res;
	}

    double getAveragePriceWithSameBrandAsCar(const Car& car) const{
		double totalPrice = 0;
        unsigned count = 0;

        for(size_t i = 0; i < carsCount; i++) {
            if (strcmp(cars[i].getBrand(), car.getBrand()) == 0) {
                totalPrice += cars[i].getPrice();
                count++;
            }
		}

		return count > 0 ? totalPrice / count : 0;
    }

};


int main()
{
    return 0;
}