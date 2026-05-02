#pragma once
#include <iostream>

class Person
{
	std::string name;
	unsigned age;

	void setName(const std::string& name);
	void setAge(unsigned age);
public:
	Person(const std::string&  name, unsigned age);

	const std::string& getName() const;
	unsigned getAge() const;
};
