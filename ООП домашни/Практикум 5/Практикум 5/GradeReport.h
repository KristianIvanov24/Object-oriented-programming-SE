#pragma once

class GradeReport
{
private:
	double* grades = nullptr;
	size_t gradesCount = 0;
	char* reportName = nullptr;

	void free();

	void copyFrom(const GradeReport& gr);
public:
	GradeReport();
	GradeReport(const double* grades, size_t gradeCount, const char* reportName);
	GradeReport(const GradeReport&);
	GradeReport& operator=(const GradeReport&);
	~GradeReport();

	size_t getGradeCount() const;
	char* getReportName() const;
	void setReportName(const char* reportName);
	void setGrades(const double* grades, size_t gradesCount);
	double calculateAverage() const;

};

