#include <iostream>

namespace constants
{
	const size_t BOOK_TITLE_LEN = 64;
	const size_t AUTHOR_NAME_LEN = 32;
	const size_t LIBRARY_NAME_LEN = 32;
	const size_t MAX_AMOUNT_OF_BOOKS = 10;
}

int myStrLen(const char* str)
{
	if (!str)
		return 0;
	int len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return len;
}

int myStrCompare(const char* str1, const char* str2)
{
	if (!str1 || !str2)
		return -1;
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
			break;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

void myStrCopy(const char* str, char* toCopy)
{
	if (!str || !toCopy)
		return;
	while (*str)
	{
		*toCopy = *str;
		str++;
		toCopy++;
	}
	*toCopy = '\0';
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
	char title[constants::BOOK_TITLE_LEN];
	char author[constants::AUTHOR_NAME_LEN];
	size_t publicationYear;
	Status status;
};

class Library
{
public:
	char name[constants::LIBRARY_NAME_LEN];
	Book books[constants::MAX_AMOUNT_OF_BOOKS];
	size_t booksCount = 0;
};

Book crateBook(const char* title, const char* author, size_t publicationYear)
{
	if (myStrLen(title) > constants::BOOK_TITLE_LEN || myStrLen(author) > constants::BOOK_TITLE_LEN)
		return {};
	Book book;
	myStrCopy(title, book.title);
	myStrCopy(author, book.author);
	book.publicationYear = publicationYear;
	book.status = Status::Available;
	return book;
}

void addBook(Library& library, const char* title, const char* author, size_t publicationYear)
{
	if (library.booksCount >= constants::MAX_AMOUNT_OF_BOOKS)
	{
		std::cout << "Your library can not store more book";
		return;
	}
	library.books[library.booksCount++] = crateBook(title, author, publicationYear);
}

void printStatus(const Book& book)
{
	std::cout << "; status:";
	switch (book.status)
	{
	case Status::Available: std::cout << "Available"; break;
	case Status::Borrowed: std::cout << " Borowed"; break;
	case Status::Reserved: std::cout << " Reserved"; break;
	default: return;
	}
}

void swapBoks(Book& b1, Book& b2)
{
	Book b = b1;
	b1 = b2;
	b2 = b;
}

void printBook(const Book& book)
{
	std::cout << "Name:" << book.title << " written by " << book.author << " published in:" << book.publicationYear;
	printStatus(book);
}

void printLibrary(const Library& library)
{
	std::cout << library.name << ":" << std::endl;
	for (size_t i = 0; i < library.booksCount; ++i)
	{
		std::cout << "Book" << i + 1 << ": ";
		printBook(library.books[i]);
		std::cout << std::endl;
	}
}

void printLibraryAlphabetically(Library library)
{
	std::cout << "Alphabetically order:" << std::endl;
	for (size_t i = 0; i < library.booksCount - 1; ++i)
	{
		for (size_t j = i + 1; j < library.booksCount; ++j)
		{
			if (myStrCompare(library.books[i].title, library.books[j].title) > 0)
			{
				swapBoks(library.books[i], library.books[j]);
			}
		}
		printBook(library.books[i]);
		std::cout << std::endl;
	}
	printBook(library.books[library.booksCount - 1]);
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

int main()
{
	Library myLibrary = { "Biblios" };
	addBook(myLibrary, "The Hobbit", "J.R.R. Tolkien", 1937);
	addBook(myLibrary, "The Metamorphosis", "Franz Kafka", 1915);
	addBook(myLibrary, "The Stranger", "Albert Camus", 1942);
	addBook(myLibrary, "Brave New World", "Aldous Huxley", 1932);
	reserveBook(myLibrary.books[2]);
	borrowBook(myLibrary.books[0]);
	printLibraryAlphabetically(myLibrary);
}