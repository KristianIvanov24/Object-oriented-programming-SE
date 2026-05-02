#pragma once

#include "../Person/Person.h"

class Student : public Person
{
	std::string fn;
public:
	Student(const std::string& name, unsigned age, const std::string& fn);

	const std::string& getFn() const;
	void setFn(const std::string& fn);
};
