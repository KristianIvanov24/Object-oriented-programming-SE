#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable : 4996)

namespace Constants
{
	//задача 1
	constexpr size_t MAX_NAME_LEN = 32;
	constexpr unsigned MIN_AGE = 18;
	constexpr unsigned MIN_SALARY = 2500;
	constexpr unsigned MAX_SALARY = 5000;
	constexpr size_t PROGRAMMING_LANGUAGES_COUNT = 5;

	//задача 2
	constexpr size_t MAX_PROGRAMMERS_IN_COMPANY = 50;

	//задача 3
	constexpr size_t MAX_MATRIX_FILE_NAME_SIZE = 64;
	constexpr size_t MAX_MATRIX_SIZE = 100;

	//задача 4
	constexpr size_t MAX_CAR_BRAND_NAME_SIZE = 100;
	constexpr size_t MAX_CAR_MODEL_NAME_SIZE = 100;
	constexpr double PRICE_PER_KM_REDUCTION = 0.001;
	constexpr size_t MAX_CARS_IN_DEALERSHIP = 1000;
	constexpr unsigned TEST_DRIVE_KM = 1;
}

enum class ProgrammingLanguages
{
	Cpp,
	Python,
	Java,
	Csharp,
	Javascript
};

const char* getLanguageString(ProgrammingLanguages langauge)
{
	switch (langauge)
	{
	case ProgrammingLanguages::Cpp:
		return "C++";
	case ProgrammingLanguages::Python:
		return "Python";
	case ProgrammingLanguages::Java:
		return "Java";
	case ProgrammingLanguages::Csharp:
		return "C#";
	case ProgrammingLanguages::Javascript:
		return "Javascript";
	}

	return "Unknown";
}

class Programmer
{
private:
	char name[Constants::MAX_NAME_LEN + 1]{};
	unsigned age = 0;
	unsigned salary = 0;
	uint8_t languages = 0;

	void setName(const char* name)
	{
		if (!name || strlen(name) > Constants::MAX_NAME_LEN)
		{
			strcpy(this->name, "Unknown");
		}

		strcpy(this->name, name);
	}

	void setAge(unsigned age)
	{
		if (age < Constants::MIN_AGE)
		{
			this->age = Constants::MIN_AGE;
			return;
		}

		this->age = age;
	}

	void printProgrammingLanguages() const
	{
		for (size_t i = 0; i < Constants::PROGRAMMING_LANGUAGES_COUNT; i++)
		{
			if (languages & (1 << i))
			{
				std::cout << getLanguageString((ProgrammingLanguages)i) << ' ';
			}
		}
	}

public:

	Programmer() = default;

	Programmer(const char* name, unsigned age, unsigned salary)
	{
		setName(name);
		setAge(age);
		setSalary(salary);
	}

	void setSalary(unsigned salary)
	{
		if (Constants::MIN_SALARY > salary || salary > Constants::MAX_SALARY)
		{
			this->salary = Constants::MIN_SALARY;
			return;
		}

		this->salary = salary;
	}

	const char* getName() const
	{
		return name;
	}

	unsigned getAge() const
	{
		return age;
	}

	unsigned getSalary() const
	{
		return salary;
	}

	void learnProgrammingLanguage(ProgrammingLanguages language)
	{
		languages |= 1 << (int)language;
	}

	bool knowsProgrammingLanguage(ProgrammingLanguages language) const
	{
		return languages & (1 << (int)languages);
	}

	void print() const
	{
		std::cout << name << " | " << age << " | " << salary << " | ";
		printProgrammingLanguages();
	}
};

class SoftwareCompany
{
private:
	Programmer programmers[Constants::MAX_PROGRAMMERS_IN_COMPANY]{};
	size_t hired = 0;
public:
	SoftwareCompany()
	{
		hired = 0;
	}

	size_t getHired() const
	{
		return hired;
	}

	void setHired(const size_t hired)
	{
		if (hired < 0)
			this->hired = 0;

		this->hired = hired;
	}

	void addProgrammer(const Programmer& programmer)
	{
		if (hired >= Constants::MAX_PROGRAMMERS_IN_COMPANY)
		{
			std::cout << "Cannot add a new programmer to the company\n";
			return;
		}

		programmers[hired++] = programmer;
	}

	void printAllProgrammersInCompany() const
	{
		for (size_t current = 0; current < hired; current++)
		{
			programmers[current].print();
			std::cout << '\n';
		}
	};

	void printProgrammersThatKnowLang(ProgrammingLanguages lang) const
	{
		for (size_t current = 0; current < hired; current++)
		{
			if (programmers[current].knowsProgrammingLanguage(lang))
			{
				programmers[current].print();
				std::cout << '\n';
			}
		}
	}

	double calculateAverageSalary() const
	{
		double average = 0;
		for (size_t current = 0; current < hired; current++)
		{
			average += programmers[current].getSalary();
		}

		return average / hired;
	}

	double calculateAverageAge() const
	{
		double average = 0;
		for (size_t current = 0; current < hired; current++)
		{
			average += programmers[current].getAge();
		}

		return average / hired;
	}

	void changeProgrammerSalary(const char* programmerName, unsigned (*changeSalary)(const Programmer&))
	{
		for (size_t current = 0; current < hired; current++)
		{
			if (strcmp(programmers[current].getName(), programmerName) == 0)
			{
				programmers[current].setSalary(changeSalary(programmers[current]));
				return;
			}
		}
	}

	void sortBySalary()
	{
		for (size_t first = 0; first < hired - 1; first++)
		{
			size_t minIndex = first;
			for (size_t second = first; second < hired; second++)
			{
				if (programmers[second].getSalary() < programmers[minIndex].getSalary())
				{
					minIndex = second;
				}
			}

			if (minIndex != first)
			{
				std::swap(programmers[first], programmers[minIndex]);
			}
		}
	}

	void sortByAge()
	{
		for (size_t first = 0; first < hired - 1; first++)
		{
			size_t minIndex = first;
			for (size_t second = first; second < hired; second++)
			{
				if (programmers[second].getAge() < programmers[minIndex].getAge())
				{
					minIndex = second;
				}
			}

			if (minIndex != first)
			{
				std::swap(programmers[first], programmers[minIndex]);
			}
		}
	}
};

//задача 3
class MatrixFile
{
	private:
		size_t rows = 0;
		size_t cols = 0;
		int matrix[Constants::MAX_MATRIX_SIZE][Constants::MAX_MATRIX_SIZE]{};
		char file[Constants::MAX_MATRIX_FILE_NAME_SIZE + 1]{};

	public:
		MatrixFile(const char* fileName)
		{
			if (!fileName)
			{
				rows = 0;
				cols = 0;
				return;
			}

			strcpy(file, fileName);

			std::ifstream ifs(file);
			if (!ifs.is_open())
				return;

			ifs >> rows >> cols;
			for (size_t r = 0; r < rows; r++)
			{
				for (size_t c = 0; c < cols; c++)
				{
					ifs >> matrix[r][c];
				}
			}

			ifs.close();
		}

		void setFileName(const char* fileName)
		{
			if (!fileName)
				return;

			strcpy(file, fileName);
		}

		const char* getFileName() const
		{
			return file;
		}

		void setRows(size_t rows)
		{
			this->rows = rows;
		}

		size_t getRows() const
		{
			return rows;
		}

		void setCols(size_t cols)
		{
			this->cols = cols;
		}

		size_t getCols() const
		{
			return cols;
		}

		void printMatrix() const
		{
			for (size_t r = 0; r < rows; r++)
			{
				for (size_t c = 0; c < cols; c++)
				{
					std::cout << matrix[r][c] << " ";
				}

				std::cout << '\n';
			}
		}

		void transposeMatrix()
		{
			for (size_t r = 0; r < rows; r++)
			{
				for (size_t c = 0; c < cols; c++)
				{
					if (r > c)
					{
						std::swap(matrix[r][c], matrix[c][r]);
					}
				}
			}
		}

		void multiplyMatrix(int number)
		{
			for (size_t r = 0; r < rows; r++)
			{
				for (size_t c = 0; c < cols; c++)
				{
					matrix[r][c] *= number;
				}
			}
		}

		void changeMatrixValue(size_t i, size_t j, size_t number)
		{
			if ((i < 0 || i > rows) || (j < 0 || j > cols))
				return;

			matrix[i][j] = number;
		}

		void saveMatrix() const
		{
			std::ofstream ofs(file);
			if (!ofs.is_open())
				return;

			ofs << rows << " " << cols << '\n';
			for (size_t r = 0; r < rows; r++)
			{
				for (size_t c = 0; c < cols; c++)
				{
					ofs << matrix[r][c] << " ";
				}

				if(r != rows - 1)
					ofs << '\n';
			}

			ofs.close();
		}

		~MatrixFile()
		{
			saveMatrix();
			rows = 0;
			cols = 0;
			strcpy(file, "");
		}
};

//задача 4
enum class EngineType
{
	GASOLINE,
	DIESEL, 
	ELECTRICITY
};

void printEngineType(EngineType engine)
{
	switch (engine)
	{
		case EngineType::DIESEL:
			std::cout << "Diesel";
			break;
		case EngineType::GASOLINE:
			std::cout << "Gasoline";
			break;
		case EngineType::ELECTRICITY:
			std::cout << "Electricity";
			break;
	}
}

class Car
{
private:
	char brand[Constants::MAX_CAR_BRAND_NAME_SIZE + 1]{};
	char model[Constants::MAX_CAR_MODEL_NAME_SIZE + 1]{};
	EngineType engine;
	bool used = false;
	unsigned mileage = 0;
	double price = 0;
public:
	Car()
	{
		strcpy(brand, "Unknown");
		strcpy(model, "Unknown");
		engine = EngineType::DIESEL;
		used = false;
		mileage = 0;
		price = 0;
	}

	Car(const char* brand, const char* model, EngineType engine, double price)
	{
		if (!brand || !model 
			|| (strlen(brand) > Constants::MAX_CAR_BRAND_NAME_SIZE) 
			|| (strlen(model) > Constants::MAX_CAR_MODEL_NAME_SIZE))
			return;

		strcpy(this->brand, brand);
		strcpy(this->model, model);
		this->engine = engine;
		this->price = price;
		used = false;
		mileage = 0;
	}

	const char* getBrand() const
	{
		return brand;
	}

	const char* getModel() const
	{
		return model;
	}

	unsigned getMileage() const
	{
		return mileage;
	}

	double getPrice() const
	{
		return price;
	}

	bool getUsed() const
	{
		return used;
	}

	EngineType getEngineType() const
	{
		return engine;
	}

	/*
	void setBrand(const char* brand)
	{
		if (!brand)
			return;

		strcpy(this->brand, brand);
	}

	void setModel(const char* model)
	{
		if (!model)
			return;

		strcpy(this->model, model);
	}

	void setPrice(double price)
	{
		this->price = price;
	}

	void setMileage(unsigned mileage)
	{
		this->mileage = mileage;
	}

	void setUsed(bool used)
	{
		this->used = used;
	}

	void setEngine(EngineType engine)
	{
		this->engine = engine;
	}
	
	*/

	void printCarInfo() const
	{
		std::cout << "Car brand: " << brand << '\n';
		std::cout << "Car model: " << model << '\n';
		std::cout << "Engine type: ";
		printEngineType(engine);
		std::cout << '\n';
		std::cout << "Used: " << (used ? "Yes" : "No") << '\n';
		std::cout << "Price: " << price << '\n';
		std::cout << "Mileage: " << mileage << '\n';
	}

	void drive(unsigned kilometers)
	{
		mileage += kilometers;
		used = true;
		for (size_t i = 0; i < kilometers; i++)
			price *= (1 - Constants::PRICE_PER_KM_REDUCTION);
	}

};

class CarDealership
{
private:
	Car cars[Constants::MAX_CARS_IN_DEALERSHIP];
	size_t carCount = 0;

public:
	CarDealership(const Car* cars, size_t carCount)
	{
		if (!cars || carCount > Constants::MAX_CARS_IN_DEALERSHIP)
			return;

		for (size_t current = 0; current < carCount; current++)
			this->cars[current] = cars[current];

		this->carCount = carCount;
	}

	CarDealership(const Car* cars, size_t carCount, EngineType engine)
	{
		if (!cars || carCount > Constants::MAX_CARS_IN_DEALERSHIP)
			return;

		size_t carsInDealership = 0;

		for (size_t current = 0; current < carCount; current++)
		{
			if (cars[current].getEngineType() == engine)
			{
				this->cars[carsInDealership++] = cars[current];
			}
		}

		this->carCount = carsInDealership  + 1;
	}

	CarDealership(const Car* cars, size_t carCount, const char* model)
	{
		if (!cars || carCount > Constants::MAX_CARS_IN_DEALERSHIP || !model)
			return;

		size_t carsInDealership = 0;

		for (size_t current = 0; current < carCount; current++)
		{
			if (strcmp(cars[current].getModel(), model) == 0)
			{
				this->cars[carsInDealership++] = cars[current];
			}
		}

		this->carCount = carsInDealership + 1;
	}

	size_t getCarsInDealership() const
	{
		return carCount;
	}

	void addCar(const Car& car)
	{
		if (carCount >= Constants::MAX_CARS_IN_DEALERSHIP)
		{
			std::cout << "Cannot add a new car\n";
			return;
		}

		cars[carCount++] = car;
	}

	void removeCar(const char* brand, const char* model)
	{
		if (!brand || !model)
			return;
		
		size_t removed = 0;
		size_t current = 0;

		while (current < carCount - removed)
		{
			if (strcmp(cars[current].getBrand(), brand) == 0
				&& strcmp(cars[current].getModel(), model) == 0)
			{
				std::swap(cars[current], cars[carCount - 1 - removed]);
				removed++;
			}
			else
			{
				current++;
			}
		}

		//for (size_t current = 0; current < carCount; current++)
		//{
		//	if (strcmp(cars[current].getBrand(), brand) == 0
		//		&& strcmp(cars[current].getModel(), model) == 0)
		//	{
		//		std::swap(cars[current], cars[carCount - 1 - removed]);
		//		removed++;
		//	}
		//}

		carCount -= removed;

		if(!removed)
			std::cout << "There are no cars to remove";
	}

	void testDrive()
	{
		for (size_t current = 0; current < carCount; current++)
		{
			cars[current].drive(Constants::TEST_DRIVE_KM);
		}
	}

	void printModel(const char* model) const
	{
		if (!model)
			return;
		
		for (size_t current = 0; current < carCount; current++)
		{
			if (strcmp(cars[current].getModel(), model) == 0)
			{
				cars[current].printCarInfo();
				std::cout << '\n';
			}
		}
	}

	Car getCarWithHighestPrice() const
	{
		size_t maxIndex = 0;

		for (size_t current = 1; current < carCount; current++)
		{
			if (cars[maxIndex].getPrice() < cars[current].getPrice())
				maxIndex = current;
		}

		return cars[maxIndex];
	}

	double averagePriceOfCarsWithTheSameBrandAs(const Car& car) const
	{
		double average = 0;
		size_t count = 0;

		for (size_t current = 0; current < carCount; current++)
		{
			if (strcmp(car.getBrand(), cars[current].getBrand()) == 0)
			{
				average += cars[current].getPrice();
				count++;
			}
		}
		
		return (count == 0 ? 0 : average / count);
	}
};

int main()
{
	Car car1("BMW", "M8", EngineType::DIESEL, 100000);
	Car car2("BMW", "M5", EngineType::GASOLINE, 90000);
	Car car3("BMW", "E36", EngineType::DIESEL, 10000);
	Car car4("Mercedes", "S-Class", EngineType::ELECTRICITY, 200000);
	Car car5("Mercedes", "C-Class", EngineType::ELECTRICITY, 200000);
	Car car6("Mercedes", "E-Class", EngineType::ELECTRICITY, 150000);
	Car car7("Mercedes", "A-Class", EngineType::ELECTRICITY, 30000);
	Car car8("Mercedes", "B-Class", EngineType::ELECTRICITY, 20000);
	Car car9("Mercedes", "G-Class", EngineType::ELECTRICITY, 300000);
	Car car10("BMW", "M8", EngineType::DIESEL, 150000);

	Car cars[] = {
		car1,
		car2,
		car3,
		car4,
		car5,
		car6,
		car7,
		car8,
		car9,
		car10
	};

	CarDealership cd(cars, 10);
	/*cd.printModel("M8");
	cd.testDrive();
	cd.printModel("G-Class");*/

	cd.getCarWithHighestPrice().printCarInfo();
	std::cout << '\n';

	std::cout << cd.averagePriceOfCarsWithTheSameBrandAs(car2);
	cd.removeCar("BMW", "M8");
	std::cout << '\n';
	std::cout << cd.averagePriceOfCarsWithTheSameBrandAs(car2);
	std::cout << '\n';
	std::cout << cd.getCarsInDealership();
	std::cout << '\n';

	cd.getCarWithHighestPrice().printCarInfo();
	return 0;
}