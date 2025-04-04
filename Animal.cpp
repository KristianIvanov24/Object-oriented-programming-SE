#include "Animal.h"
#include <iostream>

void Animal::copyFrom(const Animal& other)
{
	this->type = other.type;
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	this->age = other.age;
}

void Animal::free()
{
	delete[] name;
}

Animal::Animal() {

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

char* Animal::getName() const
{
	return name;
}

void Animal::setName(char* name)
{
	if (!name || this->name==name)
	{
		return;
	}

	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

int Animal::getAge() const {

	return age;
}

void Animal::setAge(int age)
{
	if (age < constants::MIN_AGE)
	{
		this->age = 0;
		return;
	}
	this->age = age;
}

Type Animal::getType() const
{
	return type;
}

