#pragma once
#include <iostream>

class Book
{
private:
	static int cnt;
	int id = 0;
	char* title;
	char* author;
	unsigned year;
	double price;

	void free();
	void moveFrom(Book&& other) noexcept;
	void copyFrom(const Book& other);
public:
	Book();
	Book(const Book& other);
	Book(Book&& other);
	Book& operator=(const Book& other);
	Book& operator=(Book&& other) noexcept;
	~Book();

	int getId() const;
};

