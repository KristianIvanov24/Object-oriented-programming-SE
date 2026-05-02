#include "Person.h"

Person::Person(const char* name, int age)
{
	setName(name);
	setAge(age);
}

const std::string& Person::getName() const
{
	return name;
}

unsigned Person::getAge() const
{
	return age;
}

void Person::setName(const std::string& name)
{
	// can be added aditional check for name correctness 
	
	this->name = name;
}

void Person::setAge(int age)
{
	if (age > 120)
		return;

	this->age = age;
}
