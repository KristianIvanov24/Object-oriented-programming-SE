#pragma once

class Person
{
	char* name;
	int age;

	void copyFrom(const Person& other);
	void free();
	void moveFrom(Person&& other);

public:
	Person(const char* name, int age);

	Person(const Person& other);
	Person& operator=(const Person& other);

	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;

	~Person();

	const char* getName() const;
	int getAge() const;

	void setName(const char* name);
	void setAge(int age);
};
