#pragma once

constexpr size_t MAX_QUOTE_LEN = 30;

class GraduatedStudent
{
	char* name = nullptr;
	int* grades = nullptr;
	size_t gradesCount = 0;
	char quote[MAX_QUOTE_LEN + 1]{};

	void copyFrom(const GraduatedStudent& other);
	void free();

public:

	GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote);
	GraduatedStudent(const GraduatedStudent& other);
	GraduatedStudent& operator=(const GraduatedStudent& other);
	~GraduatedStudent();

	void setName(const char* name);
	void setGrades(const int* grades, size_t gradesCount);
	void setQuote(const char* quote);

	const char* getName() const;
	const int* getGrades() const;
	size_t getGradesCount() const;
	const char* getQuote() const;
};
