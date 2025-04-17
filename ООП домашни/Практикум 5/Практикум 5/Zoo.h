#pragma once
#include "Animal.h"

class Zoo
{
private:
	char* name = nullptr;
	Animal* animals = nullptr;
	size_t maxCapacity = 0;
	size_t currentCount = 0;

	void copyFrom(const Zoo&);
	void free();
public:
	Zoo();
	Zoo(const char*, size_t);
	Zoo(const char*, Animal*, size_t, size_t);
	Zoo(const Zoo&);
	Zoo& operator=(const Zoo&);
	~Zoo();

	void setName(const char*);
	void setAnimals(const Animal*, size_t);

	const char* getName() const;
	const Animal* getAnimals() const;
	size_t getZooCapacity() const;
	size_t getCurrentCount() const;

	void addAnimal(const Animal&);
	void removeAnimal(const char*);
	size_t getCountOfAnimalsFromType(AnimalType) const;
	void printZooInfo() const;

	void saveToCsvFile(const char*) const;
};

