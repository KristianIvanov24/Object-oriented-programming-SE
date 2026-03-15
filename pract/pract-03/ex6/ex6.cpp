#include <iostream>
#include <fstream>

namespace constants{
    const size_t MAX_SIZE_NAME = 24;
	const size_t MAX_SIZE_FINES = 20;
}

enum class CarModel{
    BMW,
    Audi,
    Mercedes,
    Ferrari,
	Unknown
};

const char* carModelToString(CarModel model){
    switch (model) {
        case CarModel::BMW: 
            return "BMW";
        case CarModel::Audi: 
            return "Audi";
        case CarModel::Mercedes: 
            return "Mercedes";
        case CarModel::Ferrari: 
            return "Ferrari";
        default: 
            return "Unknown";
    }
}
bool validName(const char* name) {
    return name && strlen(name) < constants::MAX_SIZE_NAME;
}
bool validAvrSpeed(double avrSpeed) {
    return avrSpeed > 0;
}

bool validCarModel(CarModel model) {
    return model == CarModel::BMW
        || model == CarModel::Audi
        || model == CarModel::Mercedes
        || model == CarModel::Ferrari;
}

class Car{ 
private:

    double fines[constants::MAX_SIZE_FINES];
    char name[constants::MAX_SIZE_NAME];
    double avrSpeed;
    int finesCount;
    CarModel model;

public:

    Car() : fines{0}, finesCount(0), avrSpeed(0), model(CarModel::Unknown) {
        strcpy_s(name, "Unknown");
	}

    Car(const char* name, double avrSpeed, CarModel model) : finesCount(0){
		setName(name);
		setAvrSpeed(avrSpeed);
		setModel(model);
    }

    void setName(const char* name){
        if (validName(name)) {
            strcpy_s(this->name, name);
        }
        else {
            strcpy_s(this->name, "Unknown");
        }
	}

    void setAvrSpeed(double avrSpeed){
        if (validAvrSpeed(avrSpeed)) {
            this->avrSpeed = avrSpeed;
        }
        else {
            this->avrSpeed = 0;
        }
    }

    void setModel(CarModel model){
        if (validCarModel(model)) {
            this->model = model;
        }
        else {
            this->model = CarModel::Unknown;
        }
	}

    double getAvrSpeed() const {
        return this->avrSpeed;
	}

    void addFine(double fine){
        if (finesCount < constants::MAX_SIZE_FINES) {
            fines[finesCount] = fine;
            finesCount++;
        }
	}

    double getTotalFines() const {
        double total = 0;
        for (int i = 0; i < finesCount; i++) {
            total += fines[i];
        }

        return total;
    }

    void printCar() const {
		std::cout << name << " " << avrSpeed << " " << carModelToString(model) << " " << getTotalFines() << std::endl;
    }

    void serializeToBinaryFile(std::ofstream& file) const {
        file.write((const char*)this, sizeof(Car));
	}

    void deserializeFromBinaryFile(std::ifstream& file) {
        file.read((char*)this, sizeof(Car));
	}
};

size_t getFileSize(const char* fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()){
        std::cout << "File cannot be openned" << std::endl;
        return 0;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.close();

    return fileSize;
}

void swapCars(Car& car1, Car& car2) {
    Car temp = car1;
    car1 = car2;
    car2 = temp;
}

void sortCarsByAvrSpeed(Car* cars, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (cars[j].getAvrSpeed() > cars[j + 1].getAvrSpeed()) {
				swapCars(cars[j], cars[j + 1]);
            }
        }
    }
}

void getCarsFromFileSortThemAndPutThemInFile(const char* fileName) {
	
    std::ifstream fileIn(fileName, std::ios::binary);
    if (!fileIn.is_open()) {
        std::cout << "File cannot be opened" << std::endl;
        return;
	}

	size_t size = getFileSize(fileName) / sizeof(Car);
    if(size == 0) {
        std::cout << "No cars in file" << std::endl;
        return;
	}

    Car* cars = new Car[size];
    for (int i = 0; i < size; i++) {
        cars[i].deserializeFromBinaryFile(fileIn);
    }
    fileIn.close();

	sortCarsByAvrSpeed(cars, size);


    std::ofstream fileOut(fileName, std::ios::binary | std::ios::trunc);
    if (!fileOut.is_open()) {
        std::cout << "File cannot be opened" << std::endl;
        delete[] cars;
        return;
    }

    for (int i = 0; i < size; i++) {
        cars[i].serializeToBinaryFile(fileOut);
    }
    fileOut.close();

	delete[] cars;
}

int main(){

    const char* fileName = "cars.dat";

    std::ofstream out(fileName, std::ios::binary | std::ios::trunc);
    Car c1("Fast", 20, CarModel::Ferrari);
    Car c2("Slow", 12, CarModel::Audi);

    c1.serializeToBinaryFile(out);
    c2.serializeToBinaryFile(out);
    out.close();

    getCarsFromFileSortThemAndPutThemInFile(fileName);

    std::ifstream in(fileName, std::ios::binary);
    Car temp;

    std::cout << "Sorted Cars by Speed:" << std::endl;
    while (in.read((char*)& temp, sizeof(Car))) {
        temp.printCar();
    }
    in.close();

    return 0;
}