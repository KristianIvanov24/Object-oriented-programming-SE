#include <iostream>

namespace constants
{
	const int TITLE_MAX_LENGTH = 64;
	const int AUTHOR_MAX_LENGTH = 32;
	const int NAME_MAX_LENGTH = 32;
	const int MAX_BOOKS = 10;
}

enum class Status
{
    Available,
    Borrowed,
	Reserved
};

class Book
{
public:
	char title[constants::TITLE_MAX_LENGTH];
	char author[constants::AUTHOR_MAX_LENGTH];
	int publicationYear;
	Status status;
};

class Library
{
public:
	char name[constants::NAME_MAX_LENGTH];
	Book books[constants::MAX_BOOKS];
	int bookCount;
};

void addBook(Library& library, const char* title, const char* author, int year)
{
	if (library.bookCount < constants::MAX_BOOKS)
	{
		Book& newBook = library.books[library.bookCount++];
		strcpy_s(newBook.title, title);
		strcpy_s(newBook.author, author);
		newBook.publicationYear = year;
		newBook.status = Status::Available;
	}
	else
	{
		std::cout << "Library is full. Cannot add more books.\n";
	}
}

void borrowBook(Book& book)
{
	if (book.status == Status::Available)
	{
		book.status = Status::Borrowed;
		std::cout << "You have borrowed: " << book.title << "\n";
	}
	else
	{
		std::cout << "Sorry, this book is not available.\n";
	}
}

void reserveBook(Book& book)
{
	if (book.status == Status::Available)
	{
		book.status = Status::Reserved;
		std::cout << "You have reserved: " << book.title << "\n";
	}
	else
	{
		std::cout << "Sorry, this book is not available for reservation.\n";
	}
}

void printLibrary(const Library& library)
{
	std::cout << "Library: " << library.name << "\n";
	std::cout << "Books:\n";
	for (int i = 0; i < library.bookCount; i++)
	{
		const Book& book = library.books[i];
		std::cout << "Title: " << book.title;
		std::cout << ", Author: " << book.author;
		std::cout << ", Year: " << book.publicationYear;
		std::cout << ", Status: ";
		switch (book.status)
		{
		case Status::Available:
			std::cout << "Available";
			break;
		case Status::Borrowed:
			std::cout << "Borrowed";
			break;
		case Status::Reserved:
			std::cout << "Reserved";
			break;
		}
		std::cout << "\n";
	}
}

void printLibraryAlphabetically(const Library& library)
{
	const Book* sortedBooks[constants::MAX_BOOKS];
	for (int i = 0; i < library.bookCount; i++)
	{
		sortedBooks[i] = &library.books[i];
	}

	for (int i = 0; i < library.bookCount - 1; i++)
	{
		for (int j = 0; j < library.bookCount - i - 1; j++)
		{
			if (strcmp(sortedBooks[j]->title, sortedBooks[j + 1]->title) > 0)
			{
				const Book* temp = sortedBooks[j];
				sortedBooks[j] = sortedBooks[j + 1];
				sortedBooks[j + 1] = temp;
			}
		}
	}
	
	printLibrary(library);
}

int main()
{
    
}