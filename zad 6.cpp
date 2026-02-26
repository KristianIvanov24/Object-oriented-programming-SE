#include <iostream>

namespace constants
{
	const int MAX_NAME_LEN = 32 + 1;
	const double MIN_GRADE = 2.00;
	const double MAX_GRADE = 6.00;
	const int MAX_STUDENTS_NUMBER = 50;
	const int MIN_FAC_NUM = 100000;
	const int MAX_FAC_NUM = 999999;
}

enum class Specialties
{
	Informatics,
	ComputerScience,
	SoftwareEngineering,
	Mathematics,
	Unknown
};

struct Student
{
	char name[constants::MAX_NAME_LEN];
	int facNum;
	double averageGrade;
	Specialties speciality;
};

struct Course
{
	Student students[constants::MAX_STUDENTS_NUMBER];
	int studentsnum = 0;
};

Student createStudent(const char* name, int facNum, double averageGrade, Specialties speciality)
{
	Student student = { " ", 0 , 0.0, Specialties::Unknown };
	if (strlen(name) > constants::MAX_NAME_LEN)
	{
		std::cout << "Invalid name";
		return student;
	}
	strcpy_s(student.name, name);
	if (facNum<constants::MIN_FAC_NUM || facNum>constants::MAX_FAC_NUM)
	{
		std::cout << "Invalid facNum";
		return student;
	}
	student.facNum = facNum;
	student.speciality = speciality;
	if (averageGrade > constants::MAX_GRADE || averageGrade < constants::MIN_GRADE)
	{
		std::cout << "Invalid grade";
		return student;
	}
	student.averageGrade = averageGrade;
	return student;
}

void printSpeciality(const Specialties& speciality)
{
	switch (speciality)
	{
	case Specialties::Informatics:std::cout << "Informatics"; break;
	case Specialties::ComputerScience:std::cout << "Computer Science"; break;
	case Specialties::SoftwareEngineering:std::cout << "Sodtware Engineering"; break;
	case Specialties::Mathematics:std::cout << "Mathematics"; break;
	default:std::cout << "Unknown";
	}
}

void printStudent(const Student& student)
{
	std::cout << "Name: ";
	std::cout << student.name << "  ";
	std::cout << "FN: ";
	std::cout << student.facNum << "  ";
	std::cout << "Average grade: ";
	std::cout << student.averageGrade << "  ";
	printSpeciality(student.speciality);
}

void printCourseInformation(const Course& course)
{
	for (int i = 0; i < course.studentsnum; i++)
	{
		printStudent(course.students[i]);
	}
}

void addStudent(Course& course, const Student& student)
{
	if (course.studentsnum < constants::MAX_STUDENTS_NUMBER)
	{
		course.students[course.studentsnum++] = student;
	}
}

void deleteStudent(Course& course, int FacNum)
{
	int indx = -1;
	for (int i = 0; i < course.studentsnum; i++)
	{
		if (course.students[i].facNum == FacNum)
		{
			indx = i;
			break;
		}
	}
	if (indx == -1)
	{
		std::cout << "The student does not exist";
		return;
	}

	for (int i = indx; i < course.studentsnum - 1; i++)
	{
		course.students[i] = course.students[i + 1];
	}
	course.studentsnum--;
}

void filterStudents(const Course& course, bool(*filter)(const Student&))
{
	for (int i = 0; i < course.studentsnum; i++)
	{
		if (filter(course.students[i]))
		{
			printStudent(course.students[i]);
		}
	}
}

void sortStudents(Course& course, bool(*sort)(const Student&, const Student&))
{
	for (int i = 0; i < course.studentsnum - 1; i++)
	{
		for (int j = i; j < course.studentsnum - i - 1; j++)
		{
			if (sort(course.students[j], course.students[j + 1]))
			{
				Student temp = course.students[j];
				course.students[j] = course.students[j + 1];
				course.students[j + 1] = temp;
			}
		}
	}
}

bool isExcellent(const Student& student)
{
	return student.averageGrade > 5.50;
}

bool sortByGradeDescending(const Student& s1, const Student& s2)
{
	return s1.averageGrade < s2.averageGrade;
}

int main()
{
	Course myCourse;
	Student s1 = createStudent("Ivan Ivanov", 123456, 4.50,Specialties::Informatics);
	Student s2 = createStudent("Maria Popova", 654321, 6.00, Specialties::SoftwareEngineering);
	addStudent(myCourse, s1);
	addStudent(myCourse, s2);
	filterStudents(myCourse, isExcellent);
	std::cout<<std::endl;
	sortStudents(myCourse, sortByGradeDescending);
	std::cout << std::endl;
	std::cout << "Vsichki studenti sa:" << std::endl;
	printCourseInformation(myCourse);
	std::cout << std::endl;
	deleteStudent(myCourse, 123456);
	std::cout << "Studentite bez iztritiq sa:" << std::endl;
	printCourseInformation(myCourse);

}