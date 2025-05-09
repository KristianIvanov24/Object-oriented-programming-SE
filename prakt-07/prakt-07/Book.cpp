#include "Book.h"
int Book::cnt = 0;

void Book::free()
{
	delete[] title;
	title = nullptr;
	delete[] author;
	author = nullptr;
}

void Book::moveFrom(Book&& other) noexcept
{
	year = other.year;
	price = other.price;

	author = other.author;
	other.author = nullptr;

	title = other.title;
	other.title = nullptr;
}

void Book::copyFrom(const Book& other)
{
	year = other.year;
	price = other.price;

	author = new char[strlen(other.author) + 1];
	strcpy(author, other.author);

	title = new char[strlen(other.title) + 1];
	strcpy(title, other.title);
}

Book::Book()
{
	id = cnt++;
	year = price = 0;
	author = title = nullptr;
}

Book::Book(const Book& other)
{
	id = cnt++;
	copyFrom(other);
}

Book::Book(Book&& other)
{
	id = cnt++;
	moveFrom(std::move(other));
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Book& Book::operator=(Book&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Book::~Book()
{
	free();
}

int Book::getId() const
{
	return id;
}
