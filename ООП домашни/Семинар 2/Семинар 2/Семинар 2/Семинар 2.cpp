#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

namespace constants
{
	const size_t MAX_STUDENT_NAME_SIZE = 50;
	const size_t FACULTY_NUMBER_SIZE = 10;
	const size_t MAX_STUDENTS_IN_TABLE = 50;

	const size_t BUFFER_SIZE = 1024;

	//pipe -> |
	const size_t PIPE_COUNT_IN_LINE = 4;
	const char PIPE_SYMBOL = '|';
}

namespace MarkdownOperations
{
	struct Student
	{
		char name[constants::MAX_STUDENT_NAME_SIZE + 1];
		char facultyNumber[constants::FACULTY_NUMBER_SIZE];
		double gpa;
	};

	struct Markdown
	{
		Student students[constants::MAX_STUDENTS_IN_TABLE];
		size_t currentStudentCount = 0;
	};

	void addStudent(Markdown& table, const char* studentName, const char* facultyNumber,
		const double gpa)
	{
		if (!studentName || !facultyNumber)
		{
			return;
		}

		if (table.currentStudentCount >= constants::MAX_STUDENTS_IN_TABLE)
		{
			std::cout << "Max student count reached, cannot add a new one\n";
			return;
		}

		Student student;
		strcpy(student.name, studentName);
		strcpy(student.facultyNumber, facultyNumber);
		student.gpa = gpa;

		table.students[table.currentStudentCount] = student;
		table.currentStudentCount++;
	}

	void printStudent(const Markdown& table, const char* facultyNumber)
	{
		if (!facultyNumber)
		{
			std::cout << "Invalid faculty number\n";
			return;
		}

		for (size_t current = 0; current < table.currentStudentCount; current++)
		{
			if (strcmp(table.students[current].facultyNumber, facultyNumber) == 0)
			{
				Student currStudent = table.students[current];
				std::cout << "Name: " << currStudent.name << ", Faculty Number: "
					<< currStudent.facultyNumber << ", Grades: " << currStudent.gpa << '\n';

				return;
			}
		}

		std::cout << "There isn't a student with this faculty number\n";
	}

	void updateGrade(Markdown& table, const char* facultyNumber, const double newGpa)
	{
		if (!facultyNumber)
		{
			std::cout << "Invalid faculty number\n";
			return;
		}

		for (size_t current = 0; current < table.currentStudentCount; current++)
		{
			if (strcmp(table.students[current].facultyNumber, facultyNumber) == 0)
			{
				table.students[current].gpa = newGpa;
				std::cout << "Grade updated successfully.";

				return;
			}
		}

		std::cout << "There isn't a student with this faculty number\n";
	}
}

namespace FileOperations
{
	void saveTableHeader(std::ofstream& ofs)
	{
		if (!ofs.is_open())
		{
			std::cout << "Error\n";
			return;
		}

		ofs << "| Name | Faculty Number | Grade |" << std::endl;
		ofs << "|------|----------------|-------|" << std::endl;
	}

	void saveCurrentStudent(std::ofstream& ofs, const MarkdownOperations::Student& student)
	{
		if (!ofs.is_open())
		{
			std::cout << "Error\n";
			return;
		}

		ofs << "| " << student.name << " | " << student.facultyNumber << " | " << student.gpa << " |" << std::endl;
	}
	
	void saveMarkdown(const MarkdownOperations::Markdown& table, const char* fileName)
	{
		std::ofstream ofs(fileName);

		if (!ofs.is_open())
		{
			std::cout << "Error\n";
			return;
		}

		saveTableHeader(ofs);
		for (size_t current = 0; current < table.currentStudentCount; current++)
		{
			saveCurrentStudent(ofs, table.students[current]);
		}

		ofs.close();
		std::cout << "File " << fileName << " was saved successfully!\n";
	}

	//pipe -> |
	void findPipesInStr(const char* str, size_t pipesPositions[])
	{
		if (!str)
		{
			return;
		}

		size_t end = strlen(str) - 1;
		size_t currentPipePos = 1;

		pipesPositions[0] = 0;
		pipesPositions[constants::PIPE_COUNT_IN_LINE - 1] = end;

		for (size_t position = 1; position < end; position++)
		{
			if (str[position] == constants::PIPE_SYMBOL)
			{
				pipesPositions[currentPipePos++] = position;

				if (currentPipePos >= constants::PIPE_COUNT_IN_LINE - 1)
				{
					return;
				}
			}
		}

		return;
	}

	void myStrcpy(char* dest, const char src[],
		const size_t startingPosition, const size_t endingPosition)
	{
		for (size_t current = startingPosition; current <= endingPosition; current++)
		{
			*dest = src[current];
			dest++;
		}

		*dest = '\0';
	}

	unsigned charToDigit(const char symbol)
	{
		return symbol - '0';
	}

	int toPower(const int number, size_t power)
	{
		int res = 1;

		while (power)
		{
			res *= number;
			power--;
		}

		return res;
	}

	double myStringToDoubleGPA(const char* str, const size_t startingPosition, 
		const size_t endingPosition)
	{
		if (!str)
		{
			return 0;
		}

		double result = 0;
		size_t digitCount = 1;

		if (startingPosition == endingPosition)
		{
			return charToDigit(str[startingPosition]);
		}

		for (size_t current = startingPosition; current <= endingPosition; current++)
		{
			if (str[current] == '.')
			{
				continue;
			}

			result *= 10;
			result += charToDigit(str[current]);
			digitCount++;
		}
		
		result /= toPower(10, digitCount - 1);

		return result;
	}
	
	void readMarkdown(MarkdownOperations::Markdown& table, const char* fileName)
	{
		std::ifstream ifs(fileName);

		if (!ifs.is_open())
		{
			std::cout << "Error\n";
			return;
		}

		size_t pipePositions[constants::PIPE_COUNT_IN_LINE];

		size_t studentCount = 0;
		size_t counter = 0;

		while (!ifs.eof())
		{
			size_t startingPosition = 0;
			size_t endingPosition = 1;

			char line[constants::BUFFER_SIZE];
			ifs.getline(line, constants::BUFFER_SIZE);

			if (counter < 2)
			{
				counter++;
				continue;
			}

			findPipesInStr(line, pipePositions);

			myStrcpy(table.students[studentCount].name, line, 
				pipePositions[startingPosition++] + 2, pipePositions[endingPosition++] - 2);

			myStrcpy(table.students[studentCount].facultyNumber, line,
				pipePositions[startingPosition++] + 2, pipePositions[endingPosition++] - 2);

			table.students[studentCount].gpa = myStringToDoubleGPA(line,
				pipePositions[startingPosition++] + 2, pipePositions[endingPosition++] - 2);

			studentCount++;
		}

		table.currentStudentCount = studentCount;

		ifs.close();
		std::cout << "File successfully opened!\n";
	}
}


int main()
{
	MarkdownOperations::Markdown table;
	FileOperations::readMarkdown(table, "students.md");

	MarkdownOperations::printStudent(table, "0MI0600000");
	MarkdownOperations::updateGrade(table, "0MI0600000", 6.00);

	MarkdownOperations::addStudent(table, "Valentin Vulkov", "9MI0600483", 5.69);

	FileOperations::saveMarkdown(table, "students.md");

	return 0;
}