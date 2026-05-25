#define _CRT_SECURE_NO_WARNINGS
#include "GradeReport.h"
#include <iostream>
#include <cstring>

void GradeReport::free()
{
	delete[] name;
	name = nullptr;
	delete[] grades;
	grades = nullptr;
	size = 0;
}

void GradeReport::copyFrom(const GradeReport& other)
{
	size = other.size;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	grades = new unsigned[other.size];
	for (int i = 0; i < other.size; ++i)
	{
		grades[i] = other.grades[i];
	}
}

GradeReport::GradeReport() :name(nullptr), grades(nullptr),size(0)
{
}

GradeReport::GradeReport(const GradeReport& other)
{
	copyFrom(other);
}

GradeReport& GradeReport::operator=(const GradeReport& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

GradeReport::GradeReport(const char* name,unsigned* grades,size_t size) : name(nullptr), grades(nullptr), size(0)
{
	setName(name);
	setGradesAndSize(grades, size);
}

void GradeReport::setName(const char* name)
{
	if (name == nullptr)
		return;
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}


void GradeReport::setGradesAndSize(unsigned* grades, size_t size)
{
	delete[] this->grades;
	if (size > 100)
		return;
	this->grades = new unsigned[size];
	this->size = size;
	for (int i = 0; i < size; ++i)
	{
		this->grades[i] = grades[i];
	}
}

size_t GradeReport::returnAmountOfGrades() const
{
	return size;
}

const char* GradeReport::getName() const
{
	return this->name;
}

double GradeReport::calculateAverageResult() const
{
	double sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += (double)grades[i];
	}
	return sum /= size;
}

GradeReport GradeReport::merge(const GradeReport& a, const GradeReport& b)
{
	GradeReport merged;
	size_t mergedNamaLen = strlen(a.name) + strlen(b.name);
	merged.name = new char[mergedNamaLen + 1];
	strcpy(merged.name, a.name);
	strcat(merged.name, b.name);
	merged.size = a.size + b.size;
	merged.grades = new unsigned[merged.size];
	size_t index = 0;
	for (int i = 0; i < a.size; ++i)
	{
		merged.grades[index++] = a.grades[i];
	}
	for (int i = 0; i < b.size; ++i)
	{
		merged.grades[index++] = b.grades[i];
	}
	return merged;
}

GradeReport::~GradeReport()
{
	free();
}

