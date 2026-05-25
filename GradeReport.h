#pragma once
class GradeReport
{
private:
	size_t size;
	unsigned* grades;
	char* name;

	void free();
	void copyFrom(const GradeReport& other);
public:
	GradeReport();
	GradeReport(const GradeReport& other);
	GradeReport& operator=(const GradeReport& other);
	GradeReport(const char* bame, unsigned* grades, size_t size);
	void setName(const char* name);
	void setGradesAndSize(unsigned* grades, size_t size);
	size_t returnAmountOfGrades()const;
	const char* getName()const;
	double calculateAverageResult()const;
	static GradeReport merge(const GradeReport& a, const GradeReport& b);
	~GradeReport();
};

