#include "GradeReport.h"
#include <cstring>
#pragma warning (disable:4996)

void GradeReport::free()
{
	delete[] grades;
	delete[] reportName;

	grades = nullptr;
	reportName = nullptr;
	gradesCount = 0;
}

void GradeReport::copyFrom(const GradeReport& other)
{
	gradesCount = other.gradesCount;

	grades = new double[gradesCount]{};
	for (size_t i = 0; i < gradesCount; i++)
		grades[i] = other.grades[i];

	reportName = new char[strlen(other.reportName) + 1]{};
	strcpy(reportName, other.reportName);
}

GradeReport::GradeReport()
{
	grades = nullptr;
	strcpy(reportName, "");
	gradesCount = 0;
}

GradeReport::GradeReport(const double* grades, size_t gradeCount, 
	const char* reportName)
{
	if (!grades || !reportName)
		return;

	setGrades(grades, gradeCount);
	setReportName(reportName);
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

GradeReport::~GradeReport()
{
	free();
}

size_t GradeReport::getGradeCount() const
{
	return gradesCount;
}

char* GradeReport::getReportName() const
{
	return reportName;
}

double GradeReport::calculateAverage() const
{
	double average = 0;
	for (size_t current = 0; current < gradesCount; current++)
	{
		average += grades[current];
	}

	return average / gradesCount;
}

void GradeReport::setReportName(const char* reportName)
{
	if (!reportName || this->reportName == reportName)
		return;

	delete[] this->reportName;
	this->reportName = new char[strlen(reportName) + 1];

	strcpy(this->reportName, reportName);
}

void GradeReport::setGrades(const double* grades, size_t gradesCount)
{
	if (!grades || this->grades == grades)
		return;

	delete[] this->grades;
	this->grades = new double[gradesCount];

	for (size_t i = 0; i < gradesCount; i++)
		this->grades[i] = grades[i];

	this->gradesCount = gradesCount;
}
