#include "Student.h"

Student::Student(const std::string& name, int age, const std::string& fn) : Person(name, age)
{
	setFn(fn);
}

const std::string& Student::getFn() const
{
	return fn;
}

void Student::setFn(const std::string& fn)
{

	if (std::strlen(fn) >= 10)
		return;

	this->fn = fn;
}
