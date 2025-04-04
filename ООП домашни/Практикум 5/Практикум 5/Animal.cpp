#include "Animal.h"
#include <cstring>
#include <iostream>
#pragma warning (disable:4996)

void Animal::copyFrom(const Animal& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	age = other.age;
	type = other.type;
}

void Animal::free()
{
	delete[] name;

	name = nullptr;
	age = 0;
}

Animal::Animal()
{
	name = nullptr;
	age = 0;
	type = AnimalType::AMPHIBIAN;
}

Animal::Animal(const char* name, unsigned age, AnimalType type)
{
	if (!name)
		return;

	setName(name);
	setAge(age);
	setAnimalType(type);
}

Animal::Animal(const Animal& other)
{
	copyFrom(other);
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	
	return *this;
}

Animal::~Animal()
{
	free();
}

void Animal::setName(const char* name)
{
	if (!name)
		return;

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Animal::setAge(unsigned age)
{
	this->age = age;
}

void Animal::setAnimalType(AnimalType type)
{
	this->type = type;
}

const char* Animal::getName() const
{
	return name;
}

unsigned Animal::getAge() const
{
	return age;
}

AnimalType Animal::getType() const
{
	return type;
}

void Animal::printAnimalType() const
{
	switch (type)
	{
		case AnimalType::AMPHIBIAN:
			std::cout << "Amphibian";
			break;
		case AnimalType::BIRD:
			std::cout << "Bird";
			break;
		case AnimalType::FISH:
			std::cout << "Fish";
			break;
		case AnimalType::INSECT:
			std::cout << "Insect";
			break;
		case AnimalType::INVERTEBRATES:
			std::cout << "Inverterbrates";
			break;
		case AnimalType::MAMMAL:
			std::cout << "Mammal";
			break;
		case AnimalType::REPTILE:
			std::cout << "Reptile";
			break;
	}
}

void Animal::printAnimalInfo() const
{
	std::cout << "Name: " << name << '\n';
	std::cout << "Age: " << age << '\n';
	std::cout << "Animal type: ";
	printAnimalType();
}

void Animal::saveToCsvFile(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		return;

	ofs << name << ";" << age << ";" << (int)type << '\n';
}

