#include "Zoo.h"
#include <iostream>

void Zoo::copyFrom(const Zoo& other)
{
	this->animals = new Animal[strlen(animals) + 1];

	this->count = other.count;
}

void Zoo::free()
{
	for (int i = 0; i < count; i++)
	{
		delete[i] animals;
	}
	delete[] animals;
}

Zoo::Zoo()
{
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
}

Zoo::~Zoo()
{
	free();
}

void Zoo::addAnimal(const Animal& animal)
{
	if (count > constants::MAX_SIZE)
	{
		return;
	}

	this->animals[count] = animal;
	count++;
}

int Zoo::findInd(char* name)
{
	if (!name)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		if (!strcmp(animals[i].getName(), name))
		{
			return i;
		}
	}

	return -1;

}

void Zoo::removeAnimal(char* name)
{
	if (!name)
	{
		return;
	}

	int ind = findInd(name);

	if (ind == -1)
	{
		return;
	}

	std::swap(animals[ind], animals[count - 1]);
	count--;
}

int Zoo::getCountOfAnimal() const
{
	return this->count;
}