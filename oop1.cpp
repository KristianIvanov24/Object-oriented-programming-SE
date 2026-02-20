#include <iostream>

void myStrCopy(char* dest, const char* source)
{
	if (!dest || !source)
		return;

	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
}
namespace constants
{
	const int TITLE_MAX_SIZE = 64;
	const int AUTHOR_MAX_SIZE = 32;
	const int NAME_MAX_SIZE = 32;
	const int BOOKS_MAX_SIZE = 10;
}

enum class Status
{
	Available,
	Borrowed,
	Reserved
};

struct Book
{
	char title[constants::TITLE_MAX_SIZE];
	char author[constants::AUTHOR_MAX_SIZE];
	int publicationYear;
	Status status;
};

struct Library
{
	char name[constants::NAME_MAX_SIZE];
	Book books[constants::BOOKS_MAX_SIZE];
	size_t bookCount = 0;
};

Book createBook(const char* name, const char* author, int year)
{
	Book book;
	myStrCopy(book.title, name);
	myStrCopy(book.author, author);
	book.publicationYear = year;
	book.status = Status::Available;

	return book;
}

void addBook(Library& library, const char* title, const char* author, int publicationYear)
{
	library.books[library.bookCount++] = createBook(title, author, publicationYear);

	if (library.bookCount > 10)
	{
		std::cout << "exceeded limit";
		return;
	}

}

void borrowBook(Book& book)
{
	if (book.status == Status::Available)
		book.status = Status::Borrowed;
}

void reserveBook(Book& book)
{
	if (book.status == Status::Available)
		book.status = Status::Reserved;
}

void printStatus(const Book& book)
{
	switch (book.status)
	{
	case Status::Available:std::cout << "Available"; break;
	case Status::Borrowed:std::cout << "Borrowed"; break;
	case Status::Reserved:std::cout << "Reserved"; break;
	}
}

void printBook(const Book& book)
{
	std::cout << book.title << "  ";
	printStatus(book);
}

void printLibrary(const Library& library)
{
	for (int i = 0; i < library.bookCount; i++)
	{
		printBook(library.books[i]);
	}
}

void swap(Book& b1, Book& b2)
{
	Book temp = b1;
	b1 = b2;
	b2 = temp;
}

int myStrCompare(const char* str1, const char* str2)
{
	if (!str1 || !str2)
		return;

	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

void printLibraryAlphabetically(const Library& library)
{
	Book tempBooks[constants::BOOKS_MAX_SIZE];

	for (size_t i = 0; i < library.bookCount; i++)
	{
		tempBooks[i] = library.books[i];
	}

	for (size_t i = 0; i < library.bookCount - 1; i++)
	{
		size_t minIdx = i;
		for (size_t j = i + 1; j < library.bookCount; j++)
		{
			if (myStrCompare(tempBooks[j].title, tempBooks[minIdx].title) < 0)
			{
				minIdx = j;
			}
		}
		if (minIdx != i)
		{
			swap(tempBooks[i], tempBooks[minIdx]);
		}

		for (size_t i = 0; i < library.bookCount; i++)
		{
			printBook(tempBooks[i]);
			std::cout << std::endl;
		}
	}
}
int main()
{

}
