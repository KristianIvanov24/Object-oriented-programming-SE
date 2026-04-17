#pragma once
#include <iostream>

class MyString
{
	char* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);
	void resize(unsigned newCapacity);

public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString(MyString&& other);

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);

	~MyString();

	size_t getSize() const;
	size_t getCapacity() const;
	const char* c_str() const;

	MyString substr(unsigned begin, unsigned howMany);

	MyString& operator+=(const MyString& other);

	char& operator[](unsigned index); // str[3] = '3'
	const char& operator[](unsigned index) const; // std::cout << str[3]; char c = str[2];[

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);

	friend bool operator==(const MyString& lhs, const MyString& rhs);
	friend bool operator!=(const MyString& lhs, const MyString& rhs);
	friend std::strong_ordering operator<=>(const MyString& lhs, const MyString& rhs);
};

MyString operator+(const MyString& lhs, const MyString& rhs);