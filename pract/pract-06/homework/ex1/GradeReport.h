#pragma once

#include <iostream>

class GradeReport
{
    unsigned *grades;
    size_t gradesCount;
    char *name;

    void free();
    void copyFrom(const GradeReport &);
    bool isValidGrade(size_t) const;

public:
    GradeReport();
    GradeReport(const unsigned *, size_t, const char *);
    GradeReport(const GradeReport &);
    GradeReport &operator=(const GradeReport &);
    ~GradeReport();

    void setName(const char *);
    void setGrades(const unsigned *);

    unsigned getGradesCount() const;
    const char *getName() const;
    double getAverageGrade() const;

    static GradeReport merge(const GradeReport &, const GradeReport &);
};