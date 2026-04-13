#pragma once

class GradeReport {
    int* grades;
    int   count;
    char* name;

public:

    GradeReport(const int* grades_arr, int n, const char* report_name);

    ~GradeReport();
    GradeReport(const GradeReport& other);
    GradeReport& operator=(const GradeReport& other);
    GradeReport(GradeReport&& other) noexcept;
    GradeReport& operator=(GradeReport&& other) noexcept;

    int         getCount()   const;
    const char* getName()    const;
    double      getAverage() const;
    bool        isValid()    const;

    static GradeReport merge(const GradeReport& a, const GradeReport& b);
};