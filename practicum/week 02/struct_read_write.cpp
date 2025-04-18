#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable : 4996)

namespace CONSTANTS
{
	const size_t MAX_NAME = 50;
	const int MAX_PETS = 20;
};

enum class AnimalType
{
	UNKNOWN,
	DOG,
	CAT,
	PARROT
};

struct Pet
{
	char name[CONSTANTS::MAX_NAME + 1]{};
	AnimalType type = AnimalType::UNKNOWN;
	unsigned age = 0;
};

struct Petstore
{
	Pet pets[CONSTANTS::MAX_PETS]{};
	size_t size = 0;
};

Pet initPet(const char* name, AnimalType animal, unsigned age)
{
	if (!name)
	{
		return {};
	}

	Pet pet;
	strcpy(pet.name, name);
	pet.type = animal;
	pet.age = age;

	return pet;
}

void savePet(std::ofstream& ofs, const Pet& pet)
{
	ofs << pet.name << ',' << (int)pet.type << ',' << pet.age;
}

void savePetstore(std::ofstream& ofs, const Petstore& petstore)
{
	ofs << petstore.size << '\n';

	for (size_t i = 0; i < petstore.size; i++)
	{
		savePet(ofs, petstore.pets[i]);

		if (i != petstore.size - 1)
		{
			ofs << '\n';
		}
	}
}

void savePetstore(const char* filepath, const Petstore& petstore)
{
	if (!filepath)
	{
		return;
	}

	std::ofstream ofs(filepath);

	if (!ofs.is_open())
	{
		return;
	}

	savePetstore(ofs, petstore);

	ofs.close();
}

Pet readPet(std::ifstream& ifs)
{
	Pet pet;
	int type = 0;

	ifs.getline(pet.name, CONSTANTS::MAX_NAME, ',');

	ifs >> type;
	pet.type = (AnimalType)type;

	ifs.ignore();
	ifs >> pet.age;

	return pet;
}

Petstore readPetstore(std::ifstream& ifs)
{
	Petstore store;

	ifs >> store.size;
	ifs.ignore();

	for(size_t i = 0; i < store.size; i++)
	{
		store.pets[i] = readPet(ifs);
		ifs.ignore();
	}

	ifs.clear();

	return store;
}

Petstore readPetstore(const char* filepath)
{
	if (!filepath)
	{
		return {};
	}

	std::ifstream ifs(filepath);

	if (!ifs.is_open())
	{
		return {};
	}

	Petstore store = readPetstore(ifs);

	ifs.close();

	return store;
}

int main()
{
	Petstore store;
	store.size = 3;
	store.pets[0] = initPet("Rocky", AnimalType::DOG, 6);
	store.pets[1] = initPet("Betty", AnimalType::CAT, 4);
	store.pets[2] = initPet("Chichi", AnimalType::PARROT, 2);

	savePetstore("pets.txt", store);

	Petstore store2 = readPetstore("pets.txt");

	return 0;
}
