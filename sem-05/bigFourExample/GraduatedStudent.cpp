#include "GraduatedStudent.h"
#include <cstring>

#pragma warning (disable : 4996)

void GraduatedStudent::copyFrom(const GraduatedStudent& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	grades = new int[other.gradesCount];
	gradesCount = other.gradesCount;

	for (int i = 0; i < other.gradesCount; i++)
	{
		grades[i] = other.grades[i];
	}

	strcpy(quote, other.quote);
}

void GraduatedStudent::free()
{
	delete[] name;
	delete[] grades;
	name = nullptr;
	grades = nullptr;
	gradesCount = 0;
	strcpy(quote, "");
}

GraduatedStudent::GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote)
{
	setName(name);
	setGrades(grades, gradesCount);
	setQuote(quote);
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
{
	copyFrom(other);
}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void GraduatedStudent::setName(const char* name)
{
	if (!name || this->name == name)
	{
		return;
	}

	delete[] this->name;

	this->name = new char[strlen(name) + 1]{};

	strcpy(this->name, name);
}

void GraduatedStudent::setGrades(const int* grades, size_t gradesCount)
{
	if (!grades || this->grades == grades)
	{
		return;
	}

	delete[] this->grades;

	this->grades = new int[gradesCount];
	this->gradesCount = gradesCount;

	for (int i = 0; i < gradesCount; i++)
	{
		this->grades[i] = grades[i];
	}
}

void GraduatedStudent::setQuote(const char* newQuote)
{
	if (!newQuote || strlen(newQuote) > MAX_QUOTE_LEN)
	{
		return;
	}

	strcpy(quote, newQuote);
}

const char* GraduatedStudent::getName() const
{
	return name;
}

const int* GraduatedStudent::getGrades() const
{
	return grades;
}

size_t GraduatedStudent::getGradesCount() const
{
	return gradesCount;
}

const char* GraduatedStudent::getQuote() const
{
	return quote;
}

GraduatedStudent::~GraduatedStudent()
{
	free();
}
