#pragma once
#include "../Person/Person.h"

class Teacher : public Person
{
	std::vector<std::string> subjects;
public:
	Teacher(const std::string& name, unsigned age);
	Teacher(const std::string& name, unsigned age, const std::vector<std::string>& subjects);

	void addSubject(const std::string& subjectName);
	bool isTeaching(const std::string& subjectName) const;
	
	const std::vector<std::string>& getAllSubjects() const;
};
