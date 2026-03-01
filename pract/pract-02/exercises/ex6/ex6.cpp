#include <iostream>

namespace constants{
	const size_t MAX_STUDENTS = 50;
	size_t FN_SIZE = 6;
	const size_t MAX_NAME_LENGTH = 32;
};

enum class Specialty {
	Software_Engineering,
	Computer_Science,
	Informatics,
	Mathematics,
	Statistics
};

const char* specialtyToString(Specialty s) {
	switch (s) {
		case Specialty::Software_Engineering: 
			return "Software Engineering";
		case Specialty::Computer_Science: 
			return "Computer Science";
		case Specialty::Informatics: 
			return "Informatics";
		case Specialty::Mathematics: 
			return "Mathematics";
		case Specialty::Statistics: 
			return "Statistics";
		default: return "Error";
	}
}

class Student {
public:
	char name[constants::MAX_NAME_LENGTH];
	int fn;
	double averageGrade;
	Specialty specialty;
};

class Course {
public:
	Student students[constants::MAX_STUDENTS];
	int studentsCount = 0;
};

bool validateStudent(const char* name, int fn, double averageGrade)
{
	if (strlen(name) == 0 || strlen(name) >= constants::MAX_NAME_LENGTH) {
		return false;
	} else if (fn < 100000 || fn > 999999) {
		return false;
	} else if (averageGrade < 2.0 || averageGrade > 6.0) {
		return false;
	}
	return true;
}

Student initStudent(const char* name, int fn, double averageGrade, Specialty specialty)
{
	if(validateStudent(name, fn, averageGrade) == false) {
		std::cout << "Failed to initialize student due to invalid input" << std::endl;
		return Student();
	}

	Student s;
	strncpy_s(s.name, name, strlen(name));
	s.fn = fn;
	s.averageGrade = averageGrade;
	s.specialty = specialty;

	return s;
}

void printStudent(const Student& s)
{
	std::cout << "Name: " << s.name 
		<< " -> " << "FN: " << s.fn 
		<< " -> " << "Average Grade: " << s.averageGrade 
		<< " -> " << "Specialty: " << specialtyToString(s.specialty) 
		<< std::endl;
}

void printCourseStudents(const Course& c)
{
	for (int i = 0; i < c.studentsCount; i++) {
		printStudent(c.students[i]);
	}
}

void addStudentToCourse(Course& c, const Student& s)
{
	if (c.studentsCount == constants::MAX_STUDENTS) {
		std::cout << "Maximum capacity of course reached" << std::endl;
		return;
	}

	c.students[c.studentsCount++] = s;
}

void removeStudentFromCourse(Course& c, int fn)
{
	for (int i = 0; i < c.studentsCount; i++) {
		if (c.students[i].fn == fn) {
			for (int j = i; j < c.studentsCount - 1; j++) {
				c.students[j] = c.students[j + 1];
			}
			c.studentsCount--;
			return;
		}
	}

	std::cout << "Student with this FN not found" << std::endl;
}

void filterCourseStudents(const Course& c, bool (*predicate)(const Student&))
{
	for (int i = 0; i < c.studentsCount; i++) {
		if (predicate(c.students[i])) {
			printStudent(c.students[i]);
		}
	}
}

void swap(Student& s1, Student& s2)
{
	Student temp = s1;
	s1 = s2;
	s2 = temp;
}

void sortStudentsInCourse(Course& c, bool (*predicate)(const Student&, const Student&))
{
	for (int i = 0; i < c.studentsCount - 1; i++) {
		for (int j = 0; j < c.studentsCount - i - 1; j++) {
			if (predicate(c.students[j], c.students[j + 1])) {
				swap(c.students[j], c.students[j + 1]);
			}
		}
	}
}


bool isSoftwareEngeneer(const Student& s) {
	return s.specialty == Specialty::Software_Engineering;
}

bool averageGradeDescending(const Student& a, const Student& b) {
	return a.averageGrade < b.averageGrade;
}

int main()
{
	Course myCourse;
	myCourse.studentsCount = 0;

	addStudentToCourse(myCourse, initStudent("Ivan", 123456, 5.75, Specialty::Software_Engineering));
	addStudentToCourse(myCourse, initStudent("Maria", 234567, 4.20, Specialty::Computer_Science));

	printCourseStudents(myCourse);

	filterCourseStudents(myCourse, isSoftwareEngeneer);

	sortStudentsInCourse(myCourse, averageGradeDescending);
	printCourseStudents(myCourse);


	removeStudentFromCourse(myCourse, 234567);
	printCourseStudents(myCourse);

	return 0;
}