#include <iostream>
#include <cstring>
#pragma warning (disable : 4996)

enum class TypeOfEngine
{
	Gasoline,
	Diesel,
	Electricity,
	Unknown
};

namespace constants
{
	const size_t MAX_MARK_LEN = 100;
	const size_t MAX_MODEL_LEN = 100;
	const char* const DEFAULT_MARK = "Unknown";
	const char* const DEFAULT_MODEL = "Unknown";
	const unsigned MIN_PRICE = 0;
	const TypeOfEngine DEFAULT_TYPE = TypeOfEngine::Unknown;
	const bool DEFAULT_IS_USED = false;
	const unsigned DEFAULT_MILEAGE = 0;
	const size_t MAX_CAPACITY_OF_CARS = 1000;
}

class Car
{
	char mark[constants::MAX_MARK_LEN + 1];
	char model[constants::MAX_MODEL_LEN + 1];
	TypeOfEngine type;
	bool isUsed;
	unsigned mileage;
	double price;

public:
	Car()
	{
		setMark(constants::DEFAULT_MARK);
		setModel(constants::DEFAULT_MODEL);
		setEngineType(constants::DEFAULT_TYPE);
		setIsUsed(constants::DEFAULT_IS_USED);
		setMileage(constants::DEFAULT_MILEAGE);
		setPrice(constants::MIN_PRICE);
	}

	Car(const char* mark, const char* model, TypeOfEngine type, double price)
	{
		setMark(mark);
		setModel(model);
		setEngineType(type);
		setPrice(price);
		isUsed = false;
		mileage = 0;
	}

	TypeOfEngine getType()const 
	{
		return type;
	}

	const char* getModel()const
	{
		return model;
	}

	const char* getMark()const
	{
		return mark;
	}

	const unsigned getMileage()const
	{
		return mileage;
	}

	const double getPrice()const
	{
		return price;
	}

	void setMark(const char* mark)
	{
		strcpy(this->mark, mark);
	}

	void setModel(const char* model)
	{
		strcpy(this->model, model);
	}

	void setEngineType(TypeOfEngine type)
	{
		this->type = type;
	}

	void setPrice(double price)
	{
		this->price = price;
	}

	void setIsUsed(bool isUsed)
	{
		this->isUsed = isUsed;
	}

	void setMileage(unsigned mileage)
	{
		this->mileage = mileage;
	}

	void printCar()const
	{
		std::cout << mark << std::endl;
		std::cout << model << std::endl;
		switch (type)
		{
		case TypeOfEngine::Gasoline:std::cout << "Gasoline" << std::endl; break;
		case TypeOfEngine::Diesel:std::cout << "Diesel" << std::endl; break;
		case TypeOfEngine::Electricity:std::cout << "Electricity" << std::endl; break;
		}
		std::cout << isUsed << std::endl;
		std::cout << mileage << std::endl;
		std::cout << price << std::endl;
	}

	void drive(unsigned kilometers)
	{
		if (!isUsed)
		{
			isUsed = true;
		}
		mileage += kilometers;
		price -= price * kilometers * 0.1 / 100;
	}
};

class Dealership
{
	Car cars[constants::MAX_CAPACITY_OF_CARS];
	size_t count = 0;

public:
	Dealership(const Car* cars, size_t count)
	{
		if (count > constants::MAX_CAPACITY_OF_CARS)
		{
			return;
		}
		this->count = count;
		for (size_t i = 0; i < count; i++)
		{
			this->cars[i] = cars[i];
		}
	}

	Dealership(const Car* cars, size_t count, TypeOfEngine type)
	{
		if (count > constants::MAX_CAPACITY_OF_CARS)
		{
			return;
		}
		for (size_t i = 0; i < count; i++)
		{
			if (cars[i].getType() == type)
			{
				this->cars[this->count++] = cars[i];
			}
		}
	}

	Dealership(const Car* cars, size_t count, const char* model)
	{
		if (count > constants::MAX_CAPACITY_OF_CARS)
		{
			return;
		}

		for (size_t i = 0; i < count; i++)
		{
			if (strcmp(cars[i].getModel(), model) == 0)
			{
				this->cars[this->count++] = cars[i];
			}
		}
	}

	size_t getCount()
	{
		return count;
	}

	void addCar(const Car& car)
	{
		if (count >= constants::MAX_CAPACITY_OF_CARS)
		{
			std::cout << "Exceeded limit";
			return;
		}
		cars[count] = car;
		count++;
	}

	void removeCar(const char* mark, const char* model)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (strcmp(cars[i].getMark(), mark) == 0 && strcmp(cars[i].getModel(), model) == 0)
			{
				for (int j = i; j < count - 1; j++)
				{
					std::swap(cars[j], cars[j + 1]);
				}
				i--;
				count--;
			}
		}
	}

	void testDrive()
	{
		for (size_t i = 0; i < count; i++)
		{
			cars[i].drive(1);
		}
	}

	void printInfoForModel(const char* model)const
	{
		for (size_t i = 0; i < count; i++)
		{
			if (strcmp(cars[i].getModel(), model) == 0)
			{
				cars[i].printCar();
			}
		}
	}

	Car highestPriceCar()const
	{
		Car highest = cars[0];
		for (size_t i = 1; i < count; i++)
		{
			if (cars[i].getPrice() > highest.getPrice())
			{
				highest = cars[i];
			}
		}

		return highest;
	}

	double returnAveragePrice(const Car& car)
	{
		double sum = 0;
		int counter = 0;
		for (size_t i = 0; i < count; i++)
		{
			if (strcmp(cars[i].getMark(), car.getMark())==0)
			{
				counter++;
				sum += cars[i].getPrice();
			}
		}

		if (counter == 0)
		{
			return 0;
		}

		return sum / counter;
	}
};
int main()
{
	std::cout << "Hello World!\n";
}