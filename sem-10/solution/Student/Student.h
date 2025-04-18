#pragma once

#include "../Person/Person.h"
#include "../Resources.h"

class Student : public Person
{
	char fn[resources::constants::MAX_FN_LEN];
public:
	Student(const char* name, int age, const char* fn);

	const char* getFn() const;
	void setFn(const char* fn);
};
