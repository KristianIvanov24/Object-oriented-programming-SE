#include "GradeReport.h"
#include "constants.h"
#include <iostream>
#include <cstring>

using namespace constants;

void GradeReport::free()
{
    delete[] grades;
    grades = nullptr;
    delete[] name;
    name = nullptr;
    gradesCount = 0;
}

void GradeReport::copyFrom(const GradeReport &other)
{
    setName(other.name);
    this->gradesCount = other.gradesCount;
    setGrades(other.grades);
}

GradeReport::GradeReport() : grades(nullptr), name(nullptr), gradesCount(0) { }

GradeReport::GradeReport(const unsigned *grades, size_t gradesCount, const char *name)
{
    setName(name);
    this->gradesCount = gradesCount;
    setGrades(grades);
}

GradeReport::GradeReport(const GradeReport &other)
{
    copyFrom(other);
}

GradeReport &GradeReport::operator=(const GradeReport &other)
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

void GradeReport::setName(const char *name)
{
    if (this->name)
        delete[] this->name;
    if (!name)
    {
        this->name = new char[strlen(DEFAULT_NAME) + 1];
        strcpy(this->name, DEFAULT_NAME);
        return;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void GradeReport::setGrades(const unsigned *grades)
{
    if (!grades) {
        this->grades = nullptr;
        gradesCount = 0;
        return;
    }

    delete[] this->grades;
    this->grades = new unsigned[gradesCount];
    for (size_t i = 0; i < gradesCount; i++)
    {
        if (grades[i] < MIN_GRADE || grades[i] > MAX_GRADE) {
            std::cout << "Invalid grade" << std::endl;
            delete[] this->grades;
            this->grades = nullptr;
            gradesCount = 0;
            return;
        }
        this->grades[i] = grades[i];
    }
}

unsigned GradeReport::getGradesCount() const
{
    return gradesCount;
}

const char *GradeReport::getName() const
{
    return name;
}

double GradeReport::getAverageGrade() const
{
    if (gradesCount == 0) 
        return 0;
    double sum = 0;
    for (size_t i = 0; i < gradesCount; i++)
    {
        sum += grades[i];
    }
    return sum / gradesCount;
}

bool GradeReport::isValidGrade(size_t index) const {
    if (!grades || index >= gradesCount)
        return false;
    return grades[index] >= MIN_GRADE && grades[index] <= MAX_GRADE;
}

GradeReport GradeReport::merge(const GradeReport &a, const GradeReport &b)
{
    GradeReport res;
    if (!a.name || !b.name) 
        return res;
    size_t aLen = strlen(a.name), bLen = strlen(b.name);

    res.name = new char[aLen + bLen + 1];
    strcpy(res.name, a.name);
    strcat(res.name, b.name);

    res.gradesCount = a.gradesCount + b.gradesCount;
    res.grades = new unsigned[res.gradesCount]{};

    size_t i;
    for (i = 0; i < a.gradesCount; i++)
    {
        if (!a.isValidGrade(i)) {
            std::cout << "Invalid grade" << std::endl;
            delete[] res.grades;
            res.grades = nullptr;
            res.gradesCount = 0;
            return res;
        }
        res.grades[i] = a.grades[i];
    }
    for (i = a.gradesCount; i < res.gradesCount; i++)
    {
        if (!b.isValidGrade(i - a.gradesCount)) {
            std::cout << "Invalid grade" << std::endl;
            delete[] res.grades;
            res.grades = nullptr;
            res.gradesCount = 0;
            return res;
        }
        res.grades[i] = b.grades[i - a.gradesCount];
    }

    return res;
}
