#include "Zoo.h"
#include <cstring>
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

void Zoo::copyFrom(const Zoo& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	maxCapacity = other.maxCapacity;
	animals = new Animal[maxCapacity];
	currentCount = other.currentCount;

	for (size_t i = 0; i < currentCount; i++)
	{
		animals[i] = other.animals[i];
	}
}

void Zoo::free()
{
	delete[] name;
	delete[] animals;

	name = nullptr;
	animals = nullptr;
	maxCapacity = 0;
	currentCount = 0;
}

Zoo::Zoo()
{
	name = nullptr;
	animals = nullptr;
	maxCapacity = 0;
	currentCount = 0;
}

Zoo::Zoo(const char* name, size_t maxCapacity)
{
	if (!name)
		return;

	setName(name);
	this->maxCapacity = maxCapacity;
	this->animals = new Animal[maxCapacity];
	this->currentCount = 0;
}

Zoo::Zoo(const char* name, Animal* animals, size_t currentCount, size_t maxCapacity)
{
	if (!name || !animals || currentCount > maxCapacity)
		return;

	setName(name);
	this->maxCapacity = maxCapacity;
	this->animals = new Animal[maxCapacity];

	setAnimals(animals, currentCount);
}

Zoo::Zoo(const Zoo& other)
{
	copyFrom(other);
}

Zoo& Zoo::operator=(const Zoo& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Zoo::~Zoo()
{
	free();
}

void Zoo::setName(const char* name) 
{
	if (!name)
		return;

	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Zoo::setAnimals(const Animal* animals, size_t count)
{
	if (count > maxCapacity)
		return;

	for (size_t current = 0; current < count; current++)
	{
		this->animals[current] = animals[current];
	}

	this->currentCount = count;
}


const char* Zoo::getName() const
{
	return name;
}

const Animal* Zoo::getAnimals() const
{
	return animals;
}

size_t Zoo::getZooCapacity() const 
{
	return maxCapacity;
}

size_t Zoo::getCurrentCount() const
{
	return currentCount;
}

void Zoo::addAnimal(const Animal& animal)
{
	if (currentCount >= maxCapacity)
	{
		std::cout << "Max capacity reached, cannot add a new animal\n";
		return;
	}

	animals[currentCount++] = animal;
}

void Zoo::removeAnimal(const char* name)
{
	if (!name)
		return;

	for (size_t current = 0; current < currentCount; current++)
	{
		if (strcmp(animals[current].getName(), name) == 0)
		{
			std::swap(animals[current], animals[currentCount - 1]);
			currentCount--;
			return;
		}
	}

	std::cout << "There isn't an animal to remove\n";
}

size_t Zoo::getCountOfAnimalsFromType(AnimalType type) const
{
	size_t count = 0;

	for (size_t current = 0; current < currentCount; current++)
	{
		if (animals[current].getType() == type)
		{
			count++;
		}
	}

	return count;
}

void Zoo::printZooInfo() const
{
	for (size_t current = 0; current < currentCount; current++)
	{
		animals[current].printAnimalInfo();
		std::cout << '\n';
	}
}


void Zoo::saveToCsvFile(const char* fileName) const
{
	if (!fileName)
		return;

	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	for (size_t current = 0; current < currentCount; current++)
	{
		animals[current].saveToCsvFile(ofs);
	}

	ofs.close();
}