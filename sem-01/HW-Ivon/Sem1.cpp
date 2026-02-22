// Sem1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

namespace constants
{
    const int maxTitleLength = 64;
    const int maxAuthorName = 32;
    const int maxLibraryName = 32;
    const int maxBooksLength = 10;
}

namespace myString
{
	int myStrcmp(const char* str1, const char* str2)
	{
		if (!str1 || !str2)
			return 0;

		while (*str1 && *str2 && *str1 == *str2)
		{
			str1++;
			str2++;
		}

		return *str1 - *str2;
	}

	void myStrcpy(char* dest, const char* source)
	{
		if (!source)
			return;

		while (*source)
		{
			*dest = *source;
			dest++;
			source++;
		}

		*dest = '\0';
	}

	size_t myStrlen(const char* str)
	{
		if (!str)
			return 0;

		unsigned result = 0;

		while (*str)
		{
			result++;
			str++;
		}

		return result;
	}

	void myStrcat(char* dest, const char* source)
	{
		if (!dest || !source)
			return;

		size_t firstLen = myStrlen(dest);
		dest += firstLen;
		myStrcpy(dest, source);
	}

	unsigned charToDigit(char ch)
	{
		return ch - '0';
	}

	unsigned stringToNumber(const char* str)
	{
		if (!str)
			return 0;

		unsigned result = 0;

		while (*str)
		{
			int digit = charToDigit(*str);
			(result *= 10) += digit;

			str++;
		}

		return result;
	}

	int myAtoi(const char* str)
	{
		if (!str)
			return 0;

		if (*str == '-')
			return -1 * stringToNumber(str + 1);

		return stringToNumber(str);
	}

	bool isPrefix(const char* str, const char* suffix)
	{
		if (!str || !suffix)
		{
			return false;
		}

		while (*str && *suffix && *str == *suffix)
		{
			str++;
			suffix++;
		}

		return *suffix == '\0';
	}

	bool contains(const char* str, const char* toFind)
	{
		if (!str || !toFind)
		{
			return false;
		}

		while (*str)
		{
			if (isPrefix(str, toFind))
			{
				return true;
			}

			str++;
		}

		return false;
	}
}

enum Status
{
    Available, 
    Borrowed,
    Reserved
};

const char* getStatusText(Status s) {
	switch (s) {
	case Status::Available: return "Available";
	case Status::Borrowed:  return "Borrowed";
	case Status::Reserved:  return "Reserved";
	default:                return "Unknown";
	}
}

struct Book
{
    char title[constants::maxTitleLength];
    char author[constants::maxAuthorName];
    int publicationYear;
    Status status;

	void printBook() const
	{
		std::cout << "Title: " << title << " Author: " << author << " Status: " << getStatusText(status) << std::endl;
	}
};

struct Library
{
    int bookCount;
    char name[constants::maxLibraryName];
    Book books[constants::maxBooksLength];
};



void addBook(Library& library, const char* title, const char* author, int year)
{
	if (library.bookCount >= constants::maxBooksLength)
	{
		std::cout << "Not enough space in the library.";
		return;

	}

	if (myString::myStrlen(title) > constants::maxTitleLength || myString::myStrlen(author) > constants::maxAuthorName)
	{
		std::cout << "Cannot add book.";
		return;
	}

	Book book;
	myString::myStrcpy(book.title, title);
	myString::myStrcpy(book.author, author);
	book.publicationYear = year;
	book.status = Status::Available;

	library.books[library.bookCount] = book;
	library.bookCount++;
}

void borrowBook(Book& book)
{
	book.status = Status::Borrowed;
}

void reserveBook(Book& book)
{
	book.status = Status::Reserved;
}



void printLibrary(const Library& lib)
{
	for (int i = 0; i < lib.bookCount; i++) {
		lib.books[i].printBook();
	}
}

void swapBooks(Book& b1, Book& b2)
{
	Book temp = b1; 
	b1 = b2;        
	b2 = temp;
}

void sortBooks(Book* books, int bookCount)
{
	for (int i = 0; i < bookCount; i++)
	{
		for (int j = 0; j < bookCount-i-1; j++)
		{
			if (myString::myStrcmp(books[j].title, books[j + 1].title) > 0)
			{
				swapBooks(books[j], books[j + 1]);
			}
		}
	}
}

void printLibraryAlphabetically(const Library& lib)
{
	Book books[constants::maxBooksLength];

	for (int i = 0; i < lib.bookCount; i++) {
		books[i] = lib.books[i];
	}

	sortBooks(books, lib.bookCount);

	for (int i = 0; i < lib.bookCount; i++) {
		books[i].printBook();
	}
}



int main()
{
	Library myLibrary;
	myLibrary.bookCount = 0; 
	myString::myStrcpy(myLibrary.name, "City Central Library");

	addBook(myLibrary, "The Great Gatsby", "F. Scott Fitzgerald", 1925);
	addBook(myLibrary, "1984", "George Orwell", 1949);
	addBook(myLibrary, "Z-First Book", "Unknown Author", 2024);
	addBook(myLibrary, "Alice in Wonderland", "Lewis Carroll", 1865);

	printLibrary(myLibrary);

	std::cout << std::endl;
	
	borrowBook(myLibrary.books[1]);
	myLibrary.books[1].printBook();

	std::cout << std::endl;
	
	reserveBook(myLibrary.books[2]);

	

	printLibraryAlphabetically(myLibrary);
}

