#pragma warning(disable : 4996)
#include "GradeReport.h"
#include "Validation.h"
#include "Constants.h"
#include <cstring>

GradeReport::GradeReport(const int* grades_arr, int n, const char* report_name)
    : count(0)
    , grades(nullptr)
    , name(nullptr)
{
    if (!Validations::isValidName(report_name) || !Validations::isValidGradeArray(grades_arr, n))
        return;

    grades = new int[n];
    name = new char[strlen(report_name) + 1];
    count = n;

    for (int i = 0; i < n; i++)
        grades[i] = grades_arr[i];

    strcpy(name, report_name);
}

GradeReport::~GradeReport() {
    delete[] grades;
    delete[] name;
}

GradeReport::GradeReport(const GradeReport& other)
    : count(other.count)
    , grades(other.count > 0 ? new int[other.count] : nullptr)
    , name(other.name ? new char[strlen(other.name) + 1] : nullptr)
{
    if (grades) memcpy(grades, other.grades, count * sizeof(int));
    if (name)   strcpy(name, other.name);
}

GradeReport& GradeReport::operator=(const GradeReport& other) {
    if (this == &other) return *this;

    int* new_grades = other.count > 0 ? new int[other.count] : nullptr;
    char* new_name = other.name ? new char[strlen(other.name) + 1] : nullptr;

    if (new_grades) memcpy(new_grades, other.grades, other.count * sizeof(int));
    if (new_name)   strcpy(new_name, other.name);

    delete[] grades;
    delete[] name;

    grades = new_grades;
    name = new_name;
    count = other.count;

    return *this;
}

GradeReport::GradeReport(GradeReport&& other) noexcept
    : grades(other.grades)
    , count(other.count)
    , name(other.name)
{
    other.grades = nullptr;
    other.name = nullptr;
    other.count = 0;
}

GradeReport& GradeReport::operator=(GradeReport&& other) noexcept {
    if (this == &other) return *this;

    delete[] grades;
    delete[] name;

    grades = other.grades;
    name = other.name;
    count = other.count;

    other.grades = nullptr;
    other.name = nullptr;
    other.count = 0;

    return *this;
}

bool GradeReport::isValid() const {
    return grades != nullptr && name != nullptr && count > 0;
}

int GradeReport::getCount() const {
    return count;
}

const char* GradeReport::getName() const {
    return name;
}

double GradeReport::getAverage() const {
    if (count == 0) return 0.0;

    int sum = 0;
    for (int i = 0; i < count; i++)
        sum += grades[i];

    return static_cast<double>(sum) / count;
}

GradeReport GradeReport::merge(const GradeReport& a, const GradeReport& b) {
    if (!a.isValid() || !b.isValid()) {
        int dummy[1] = { 0 };
        return GradeReport(dummy, 0, "invalid");
    }

    int total = a.count + b.count;
    int* merged_grades = new int[total];

    memcpy(merged_grades, a.grades, a.count * sizeof(int));
    memcpy(merged_grades + a.count, b.grades, b.count * sizeof(int));

    int   name_len = strlen(a.name) + strlen(Constants::MERGE_SEPARATOR) + strlen(b.name) + 1;
    char* merged_name = new char[name_len];
    strcpy(merged_name, a.name);
    strcat(merged_name, Constants::MERGE_SEPARATOR);
    strcat(merged_name, b.name);

    GradeReport result(merged_grades, total, merged_name);

    delete[] merged_grades;
    delete[] merged_name;

    return result;
}