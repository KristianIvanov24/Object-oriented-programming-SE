#include <iostream>
#include <cstring>
#pragma warning (disable : 4996)

namespace constants {
	const size_t BRAND_LEN = 100;
	const size_t MODEL_LEN = 100;
	const size_t ENGINES_TYPE_COUNT = 100;
	const char* DEFAULT_NAME = "Unknown";
	const size_t AMOUNT_OF_CARS_IN_DIALERSHIP = 1000;
}

enum class Engine
{
	GASOLINE,
	DIESEL,
	ELECTRICITY,
	UNKNOWN
};

const char* EngineToString(Engine engine)
{
	switch (engine)
	{
	case Engine::GASOLINE:return "Gasoline";
	case Engine::DIESEL:return "Disel";
	case Engine::ELECTRICITY:return "Electricity";
	default:return "Unknown";
	}
}

namespace validation {
	bool isValidBrandAndModelLen(const char* str)
	{
		return str && strlen(str) <= constants::BRAND_LEN;
	}

	bool isValidEngine(Engine engine)
	{
		return (size_t)engine <= constants::ENGINES_TYPE_COUNT && (size_t)engine >= 0;
	}

	bool isValidPrice(double price)
	{
		return price > 0;
	}

}

class Car
{
private:
	char brand[constants::BRAND_LEN+1];
	char model[constants::MODEL_LEN+1];
	bool isSecondHand;
	Engine engine;
	unsigned mileage;
	double price;

	double calculatePriceChangeAfterDriving(unsigned km)
	{
		return price - (price / 1000 * km);
	}
public:
	Car()=default;

	Car(const char* brand, const char* model, Engine engine, double price):isSecondHand(0),mileage(0)
	{
		setBrand(brand);
		setModel(model);
		setEngine(engine);
		setPrice(price);
	}

	void setBrand(const char* brand)
	{
		if (!validation::isValidBrandAndModelLen(brand))
		{
			strcpy(this->brand, constants::DEFAULT_NAME);
			return;
		}
		strcpy(this->brand, brand);
	}

	void setModel(const char* model)
	{
		if (!validation::isValidBrandAndModelLen(model))
		{
			strcpy(this->model, constants::DEFAULT_NAME);
			return;
		}
		strcpy(this->model, model);
	}

	void setEngine(Engine engine)
	{
		if (!validation::isValidEngine(engine))
		{
			this->engine = Engine::UNKNOWN;
			return;
		}
		this->engine = engine;

	}

	void setPrice(double price)
	{
		if (!validation::isValidPrice(price))
		{
			this->price = 0;
			return;
		}
		this->price = price;
	}

	void print()const
	{
		std::cout << brand << '-' << model<<' '<<" with"<<EngineToString(engine)<<" engine ";
		if (!isSecondHand)std::cout << "The car is brand new ";
		else std::cout << "The car is used for"<<mileage <<"km  ";
		std::cout << "Selling for:" << price;
	}

	Engine getEngineType() const
	{
		return engine;
	}

	const char* getBrand() const
	{
		return brand;
	}

	const char* getModel() const
	{
		return model;
	}

	double getPrice()const
	{
		return price;
	}

	void drive(unsigned kilometers)
	{
		this->mileage += kilometers;
		this->isSecondHand = true;
		this->price = calculatePriceChangeAfterDriving(kilometers);
	}
};

class Dealership
{
private:
	Car cars[constants::AMOUNT_OF_CARS_IN_DIALERSHIP];
	size_t amountOfCars=0;
public:
	Dealership() = default;

	Dealership(const Car cars[], size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			this->cars[amountOfCars++] = cars[i];
		}
	}

	Dealership(const Car cars[], size_t size, Engine engine)
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (cars[i].getEngineType() ==engine)
			{
				this->cars[amountOfCars++] = cars[i];
			}
		}
	}

	Dealership(const Car cars[], size_t size, const char* model)
	{
		for (size_t i = 0; i < size; ++i)
		{
			if ((strcmp(model, cars[i].getModel()) == 0))
			{
				this->cars[amountOfCars++] = cars[i];
			}
			
		}
	}

	size_t getiCarsCount()const
	{
		return amountOfCars;
	}

	bool addCar(const Car& car)
	{
		if (amountOfCars >= constants::AMOUNT_OF_CARS_IN_DIALERSHIP)
		{
			return false;
		}
		cars[amountOfCars++] = car;
		return true;
	}

	bool removeCar(const char* brand, const char* model)
	{
		int currentIndex = -1;
		for (int i = 0; i < amountOfCars; ++i)
		{
			if ((strcmp(cars[i].getBrand(), brand) == 0 && (strcmp(cars[i].getModel(), model) == 0)))
			{
				currentIndex = i;
				break;
			}
		}
		if (currentIndex == -1)
			return false;

		for (int i = currentIndex; i < amountOfCars - 1; ++i)
		{
			cars[i] = cars[i + 1];
		}
		amountOfCars--;
		return true;
	}

	void testDrive()
	{
		for (int i = 0; i < amountOfCars; ++i)
		{
			cars[i].drive(1);
		}
	}

	void printCarsOfModel(const char* model) const
	{
		for (int i = 0; i < amountOfCars; ++i)
		{
			if (strcmp(cars[i].getModel(), model) == 0)
			{
				cars[i].print();
			}
		}
	}

	Car getMostExpensiveCar() const
	{
		if (amountOfCars == 0) return {};
		int mostExpensiveIdx = 0;
		for (size_t i = 1; i < amountOfCars; ++i) 
		{ 
			if (cars[i].getPrice() > cars[mostExpensiveIdx].getPrice()) {
				mostExpensiveIdx = i;
			}
		}
		return cars[mostExpensiveIdx];
	}

	double getAveragePriceOfBrand(const Car& c)const
	{
		char brand[constants::BRAND_LEN+1];
		strcpy(brand, c.getBrand());
		double sum = 0;
		int count = 0;
		for (int i = 0; i < amountOfCars; ++i)
		{
			if (strcmp(cars[i].getBrand(), brand) == 0)
			{
				count++;
				sum += cars[i].getPrice();
			}
		}
		if (count == 0)
			return 0;

		return sum/count;
	}
};


int main()
{
	std::cout << 5;
}