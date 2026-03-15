// pract3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

namespace constants {
	const size_t NAME_MAX_LENGTH = 24;
	const size_t MAX_FINES_COUNT = 20;
	const char FILE_NAME[] = "cars.bin";
	const size_t FN_LENGTH = 11;
	const char FILE_NAME2[] = "students.csv";
	const size_t BUFF_SIZE = 1024;
	const size_t MIN_ROW_LEN = 5;
}


//6

enum class Brand
{
	Mercedes,
	Audi,
	Toyota,
	Kia,
	Honda
};

class Car
{
public:
	Brand brand;
	char ownerName[constants::NAME_MAX_LENGTH];
	double averageSpeed;
	double fines[constants::MAX_FINES_COUNT];
	size_t finesCount;
};

double getAllFinesSum(Car& car)
{
	double total = 0;
	int count = car.finesCount;

	for (int i = 0; i < count;i++)
	{
		total += car.fines[i];
	}

	return total;
	
}

void addFineToCar(Car& car, double fine)
{
	if (car.finesCount == constants::MAX_FINES_COUNT)
	{
		return;
	}

	car.fines[car.finesCount] = fine;
	car.finesCount++;
}

const char* printBrand(Brand brand)
{
	switch (brand)
	{
	case Brand::Mercedes: return "Mercedes";break;
	case Brand::Audi: return "Audi"; break;
	case Brand::Kia: return "Kia"; break;
	case Brand::Toyota: return "Toyota"; break;
	case Brand::Honda: return "Honda"; break;
	}
}

void printCar(Car& car)
{
	std::cout << "Brand: " << printBrand(car.brand) << " Owner: " << car.ownerName << std::endl;
	std::cout << "Fines: ";

	for (int i = 0; i < car.finesCount; i++)
	{
		std::cout << car.fines[i] << ' ';
	}

	std::cout << std::endl;
}

void saveCar(Car& car)
{
	std::ofstream stream(constants::FILE_NAME, std::ios::binary);

	if (!stream.is_open()) {
		std::cerr << "Error" << std::endl;
		return;
	}

	stream.write((const char*)&car, sizeof(car));

	stream.close();
}

Car readCar()
{
	std::ifstream stream(constants::FILE_NAME, std::ios::binary);

	if (!stream.is_open()) {
		std::cerr << "Error" << std::endl;
		return {};
	}

	Car car;

	stream.read((char*)&car, sizeof(car));

	stream.close();
}

void swapCars(Car& car1, Car& car2)
{
	Car temp = car1;
	car1 = car2;
	car2 = temp;
}

void sort(Car*& cars, size_t count)
{
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (cars[j].averageSpeed > cars[j + 1].averageSpeed) {
				swapCars(cars[j], cars[j + 1]);
			}
		}
	}
}

void sortCars(size_t count)
{
	std::ifstream stream(constants::FILE_NAME, std::ios::binary);

	if (!stream.is_open()) {
		std::cerr << "Error" << std::endl;
		return;
	}

	std::streamsize fileSize = stream.tellg();
	int carsInFile = fileSize / sizeof(Car);

	if (carsInFile == 0) {
		stream.close();
		return;
	}

	if (count > carsInFile)
	{
		return;
	}

	Car* cars = new Car[count];
	stream.seekg(0, std::ios::beg);
	stream.read((char*)cars, fileSize);

	stream.close();

	std::ofstream writeSTream(constants::FILE_NAME, std::ios::binary);

	if (!writeSTream.is_open()) {
		std::cerr << "Error" << std::endl;
		return;
	}

	sort(cars, count);

	writeSTream.seekp(0, std::ios::beg);
	writeSTream.write((const char*)cars, fileSize);

	
	delete[] cars;
	writeSTream.close();

}

//7

class Student { 
public:
	char firstName[constants::NAME_MAX_LENGTH];             
	char lastName[constants::NAME_MAX_LENGTH];
	char specialty[constants::NAME_MAX_LENGTH];
	char fn[constants::FN_LENGTH];
	int year;                       
	int group;
};


Student deserializeStudent(char* line) {

	Student s;
	char buffer[6][256]; 
	int field = 0;
	int charIdx = 0;

	for (int i = 0; line[i] != '\0'; i++) {
		if (line[i] == ',') {
			buffer[field][charIdx] = '\0';
			field++;
			charIdx = 0;
			if (field >= 6) break;
		}
		else {
			if (charIdx < 49) {
				buffer[field][charIdx++] = line[i];
			}
		}
	}
	
	buffer[field][charIdx] = '\0';

	
	strcpy_s(s.fn, buffer[0]);
	strcpy_s(s.firstName, buffer[1]);
	strcpy_s(s.lastName, buffer[2]);
	strcpy_s(s.specialty, buffer[3]);
	s.year = atoi(buffer[4]);   
	s.group = atoi(buffer[5]);  

	return s;
}

Student* deserializeStudents()
{
	std::ifstream stream(constants::FILE_NAME2);

	if (!stream.is_open())
	{
		return nullptr;
	}

	int count = 0;
	char line[constants::BUFF_SIZE];

	while (stream.getline(line, constants::BUFF_SIZE))
	{
		if (strlen(line) > constants::MIN_ROW_LEN)
			count++; 
	}

	stream.clear();
	stream.seekg(0, std::ios::beg);
	Student* students = new Student[count];

	for (int i = 0; i < count; i++)
	{
		char line[constants::BUFF_SIZE];
		stream.getline(line, constants::BUFF_SIZE);
		students[i] = deserializeStudent(line);
	}

	stream.close();
	return students;

}

void filterByYear(const Student* students, int count, int year) 
{
	for (int i = 0; i < count; i++) 
	{
		if (students[i].year == year)
		{
			std::cout << students[i].fn << ": " << students[i].firstName
				<< " " << students[i].lastName << " Group: "
				<< students[i].group << std::endl;
		}
	}
}

void updateGroup(Student* students, int count, const char* fn, int newGroup) 
{
	bool found = false;

	for (int i = 0; i < count; i++) 
	{
		if (std::strcmp(students[i].fn, fn) == 0) 
		{
			students[i].group = newGroup;
			found = true;
			break; 
		}
	}

	if (!found) {
		std::cout << "Student not found." << std::endl;
	}
}

void removeStudent(Student* students, int& count, const char* fn) 
{
	int studentAtIndex = -1;

	for (int i = 0; i < count; i++) 
	{
		if (std::strcmp(students[i].fn, fn) == 0) {
			studentAtIndex = i;
			break;
		}
	}

	
	if (studentAtIndex != -1)
	{
		for (int i = studentAtIndex; i < count - 1; i++)
		{
			students[i] = students[i + 1];
		}
		
		count--;
	}
	else 
	{
		std::cout << "Student not found." << std::endl;
	}
}



void saveStudentsToFile( const Student* students, int count) 
{
	std::ofstream stream(constants::FILE_NAME2);

	if (!stream.is_open()) return;

	for (int i = 0; i < count; i++) 
	{
		stream << students[i].fn << ","
			<< students[i].firstName << ","
			<< students[i].lastName << ","
			<< students[i].specialty << ","
			<< students[i].year << ","
			<< students[i].group << "\n";
	}

	stream.close();
}

bool compareByLastName(const Student& a, const Student& b) {
	return std::strcmp(a.lastName, b.lastName) < 0;
}

bool compareByYear(const Student& a, const Student& b) {
	return a.year < b.year;
}

void sortStudents(Student* students, int count, bool (*isBefore)(const Student&, const Student&)) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (!isBefore(students[j], students[j + 1])) {
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}

int main()
{

	Student s1 = { "Ivan", "Ivanov", "KN", "9MI0800001", 1, 3 };
	Student s2 = { "Maria", "Petrova", "SI", "9MI0800002", 2, 1 };
	Student s3 = { "Georgi", "Todorov", "IS", "9MI0800003", 3, 2 };

	Student students[3];
	students[0] = s1;
	students[1] = s2;
	students[2] = s3;

	saveStudentsToFile(students, 3);

	updateGroup(students, 3, "9MI0800002", 3);

	saveStudentsToFile(students, 3);

	Student* st = deserializeStudents();

	for (int i = 0; i < 3; i++)
	{
		std::cout << st[i].firstName
			<< ' ' << st[i].group;
	}

}

