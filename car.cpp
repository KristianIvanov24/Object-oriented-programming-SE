#include<iostream>
#include<cstring>
#pragma warning(disable:4996)



using std::cout;
using std::cin;
using std::endl;

namespace constants {
	const int MAX_BRAND_SIZE = 100;
	const int MAX_MODEL_SIZE = 100;
	const int MAX_CARS = 100;
	const int DEALER_SHIP_NAME_SIZE = 100;
}
using namespace constants;
enum Engine {
	Gasoline = 1,
	Diesel = 2,
	Electricity = 3,
}; 


namespace Char {
	bool validBrand(const char* brand) {
		if (strlen(brand) > MAX_BRAND_SIZE || !brand) return false;
		return true;
	}
	bool validModel(const char* model) {
		if (strlen(model) > MAX_MODEL_SIZE || !model) return false;
		return true;
	}
	bool validName(const char* name) {
		if (strlen(name) > DEALER_SHIP_NAME_SIZE || !name) return false;
		return true;
	}
}
using namespace Char;

void newline();

class Car {
	char brand[MAX_BRAND_SIZE + 1];
	char model[MAX_MODEL_SIZE + 1];
	Engine engine;
	bool isUsed;
	unsigned int mileage;
	double price;

public:
	Car() {
		strcpy(brand, "");
		strcpy(model, "");
		engine = Gasoline;
		isUsed = false;
		mileage = 0;
		price = 0;
	}
	Car(const char* brand, const char* model, Engine engine, const double price) {  // прави нова кола
		if (validBrand(brand) && validModel(model)) {
			strcpy(this->brand, brand);
			strcpy(this->model, model);
			this->engine = engine;
			this->price = price;
			this->isUsed = false;
			mileage = 0;
		}
		else {
			Car();
		}
	}
	void setBrand(const char* brand) {
		if (validBrand(brand)) {
			strcpy(this->brand, brand);
		}
		else {
			strcpy(this->brand, "");
		}
	}
	void setModel(const char* model) {
		if (validModel(model)) {
			strcpy(this->model, model);
		}
		else {
			strcpy(this->model, "");
		}
	}
	void setEngine(Engine engine) {
		this->engine = engine;
	}
	void setPrice(const double price) {
		this->price = price;
	}
	void setIsUsed(bool isUsed) {
		this->isUsed = isUsed;
	}
	void setMileage(const unsigned int mileage) {
		this->mileage = mileage;
	}

	const char* getBrand() const {
		return this->brand;
	}
	const char* getModel() const {
		return this->model;
	}
	void getEngine() const{
		switch (engine) {
			case Gasoline:
				cout << "Gasoline";
				break;
			case Diesel:
				cout << "Diesel";
				break;
			case Electricity:
				cout << "Electricity";
				break;
		}
	}
	void getIsUsed() const{
		if (this->isUsed) cout << "Used";
		else cout << "New";
	}
	unsigned int getMileage() const {
		return this->mileage;
	}
	double getPrice() const {
		return this->price;
	}

	void printCar() const{
		cout << "Brand:\t" << this->getBrand() << endl;
		cout << "Model:\t" << this->getModel() << endl;
		cout << "Engine:\t"; this->getEngine(); cout << endl;
		cout << "Is used: "; this->getIsUsed(); cout << endl;
		cout << "Mileage: " << this->getMileage() << endl;
		cout << "Price:\t" << this->getPrice() << endl;
	}
	
	void drive(unsigned int km) {
		this->isUsed = true;
		this->setMileage(this->getMileage() + km);
		price -= 0.001 * km;
	}
};

class CarDealership {
	char dealershipName[DEALER_SHIP_NAME_SIZE];
	Car cars[MAX_CARS];
	int count;

	int findMaxPrice() const{
		int max = cars[0].getPrice();
		for (int i = 0; i < count; i++) {
			if (cars[i].getPrice() > max) max = cars[i].getPrice();
		}
		return max;
	}

public:
	CarDealership() {
		count = 0;
		strcpy(dealershipName, "");
	}
	CarDealership(Car cars[], int count, const char* name) {
		
		if (validName(name)) strcpy(dealershipName, name);
		else strcpy(dealershipName, "");
		
		if (count > MAX_CARS) {
			count = MAX_CARS;
		}
		for (int i = 0; i < count; i++) {
			this->cars[i] = cars[i];
		}
		this->count = count;
	}
	void setDealershipName(const char* dealershipName) {
		if (validName(dealershipName)) strcpy(this->dealershipName, dealershipName);
		else strcpy(this->dealershipName, "");
	}
	const char* getDealershipName() const {
		return this->dealershipName;
	}
	int getCount()const {
		return this->count;
	}
	void addCar(const Car& car) {
		if (count < MAX_CARS) {
			cars[count++] = car;
		}
	}
	void removeCar(const char* brand, const char* model) {
		int idx = count - 1;
		for (int i = 0; i < count; i++) {
			if (strcmp(cars[i].getBrand(), brand) == 0 && strcmp(cars[i].getModel(), model) == 0) {
				std::swap(cars[i], cars[idx--]);
				count--;
			}
		}
	}
	void testDrive() {
		for (int i = 0; i < count; i++) {
			cars[i].setMileage(cars[i].getMileage() + 1);
		}
	}
	void printDealership() {
		cout << "Dealership name: " << this->getDealershipName() << endl;
		for (int i = 0; i < count; i++) {
			cars[i].printCar();
			newline();
		}
	}
	void printCar(const char* brand, const char* model) {
		for (int i = 0; i < count; i++) {
			if (strcmp(cars[i].getBrand(), brand) == 0 && strcmp(cars[i].getModel(), model) == 0) {
				cars[i].printCar();
				newline();
			}
		}
	}

	void maxPrice() const {
		int max = findMaxPrice();
		for (int i = 0; i < count; i++) {
			if (cars[i].getPrice() == max) {
				cars[i].printCar();
			}
		}
	}

	double avPriceBrand(const Car& car)const {
		double price = 0;
		int count = 0;
		for (int i = 0; i < count; i++) {
			if (strcmp(cars[i].getBrand(), car.getBrand()) == 0) {
				cout << "in";
				price += cars[i].getPrice();
				count++;
			}
		}
		return price / count;
	}
};


int main() {
	Car car("BMW","M5 competition",Engine::Gasoline,100000);
	cout << car.getBrand() << "\t" << car.getModel();
	car.setBrand("Mercedes");
	car.setModel("GT 63 AMG");

	car.drive(100000);

	newline(); newline();
	newline();
	car.printCar();
	newline();
	Car cars[3];
	cars[0] = { "BMW","M5 competition",Engine::Gasoline,100000 };
	cars[1] = { "Mercedes","GT 63 AMG",Engine::Gasoline,150000 };
	cars[2] = { "Audi","RS7",Engine::Gasoline,120000 };
	cars[2].printCar();

	CarDealership dealership(cars, 3, "Den i nosht auto");
	cout << dealership.getDealershipName();

	Car car2("Porshe", "911", Engine::Gasoline, 200000);
	Car car3("BMW", "M5 competition", Engine::Gasoline, 200000);
	Car car4("Mercedes", "G550 AMG", Engine::Gasoline, 3050000);

	dealership.addCar(car3);
	dealership.addCar(car2);
	dealership.addCar(car4);

	

	dealership.removeCar("BMW", "M5 competition");
	newline(); cout << dealership.getCount();


	newline(); newline();
	dealership.printDealership();
	dealership.testDrive();
	newline(); newline();	
	dealership.printDealership();
	newline(); newline();	
	dealership.printCar("Mercedes", "GT 63 AMG");

	newline(); newline();	
	dealership.maxPrice();

	cout << dealership.avPriceBrand(car2);

	return 0;
}
void newline() {
	cout << endl << endl;
}