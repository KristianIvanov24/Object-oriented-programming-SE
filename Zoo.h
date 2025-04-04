#pragma once
#include "Animal.h"

namespace constants {
	constexpr int MAX_SIZE = 100;
}

class Zoo
{
private:
	Animal* animals;
	int count;

public:
	Zoo();
	Zoo(const Zoo& other);
	Zoo& operator=(const Zoo& other);
	~Zoo();

	void free();
	void copyFrom(const Zoo& other);

	void addAnimal(const Animal& animal);
	void removeAnimal(char* name);
	int findInd(char* name);
	int getCountOfAnimal() const;

};

