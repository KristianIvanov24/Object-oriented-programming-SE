#include "Teacher.h"

Teacher::Teacher(const std::string& name, unsigned age) : Person(name, age)
{

}
	
Teacher::Teacher(const std::string& name, unsigned age, const std::vector<std::string>& subjects) : Person(name, age), subjects(subjects)
{

}

void Teacher::addSubject(const std::string& subjectName)
{
	subjects.push_back(subjectName);
}
	
bool Teacher::isTeaching(const std::string& subjectName) const
{
    return std::find(subjects.begin(), subjects.end(), subjectName) != subjects.end();
}
	
const std::vector<std::string>& Teacher::getAllSubjects() const
{
	return subjects;
}
