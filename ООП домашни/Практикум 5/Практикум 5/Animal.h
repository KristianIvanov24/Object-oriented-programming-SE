#pragma once
#include <fstream>

enum class AnimalType
{
	MAMMAL,
	REPTILE,
	FISH, 
	BIRD, 
	AMPHIBIAN, 
	INVERTEBRATES,
	INSECT
};

class Animal
{
private:
	char* name = nullptr;
	unsigned age = 0;
	AnimalType type = AnimalType::AMPHIBIAN;

	void copyFrom(const Animal&);
	void free();

	void printAnimalType() const;

public:
	Animal();
	Animal(const char*, unsigned, AnimalType);
	Animal(const Animal&);
	Animal& operator=(const Animal&);
	~Animal();

	void setName(const char*);
	void setAge(unsigned);
	void setAnimalType(AnimalType);

	const char* getName() const;
	unsigned getAge() const;
	AnimalType getType() const;

	void printAnimalInfo() const;

	void saveToCsvFile(std::ofstream&) const;
};

