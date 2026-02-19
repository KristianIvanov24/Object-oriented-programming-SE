#include <iostream>

namespace constants {
    const size_t TITLE_LENGTH = 64;
	const size_t AUTHOR_LENGTH = 32;
	const size_t NAME_LENGTH = 32;	
	const size_t BOOK_SIZE = 10;
}

enum class Status{
	Available,
	Borrowed,
	Reserved
};

const char* getStatusIntoString(Status s) {
	switch (s) {
		case Status::Available: 
			return "Available";
		case Status::Borrowed:  
			return "Borrowed";
		case Status::Reserved:  
			return "Reserved";
		default:        
			return "Error";
	}
}

struct Book {
	char title[constants::TITLE_LENGTH];
	char author[constants::AUTHOR_LENGTH];
	int publicationYear;
	Status status;
};

struct Library {
	char name[constants::NAME_LENGTH];
	Book books[constants::BOOK_SIZE];
	int bookCount;
};

void myStrCpy(char* dest, const char* src, int maxLen) {
	if (!dest || !src || maxLen <= 0) {
		return;
	}

	while (*src != '\0' && maxLen > 1) {
		*dest = *src;
		dest++;
		src++;
		maxLen--;
	}

	*dest = '\0';
}

int myStrLen(const char* src) {
	if (!src) {
		return -1;
	}

	int count = 0;

	while (*src) {
		src++;
		count++;
	}

	return count;
}

int myStrCmp(const char* str1, const char* str2) {
	if (!str1 || !str2) {
		return -1;
	}

	while (*str1 && *str2) {
		if (*str1 != *str2) {
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

void addBook(Library& library, const char* title, const char* author, int publicationYear) {
	int titleLen = myStrLen(title);
	int authorLen = myStrLen(author);

	if (titleLen < 0 || authorLen < 0 || publicationYear < 0) {
		std::cout << "Incorrect input" << std::endl;
		return;
	}

	if (library.bookCount >= constants::BOOK_SIZE) {
		std::cout << "Library is full" << std::endl;
		return;
	}

	Book& newBook = library.books[library.bookCount];

	myStrCpy(newBook.title, title, constants::TITLE_LENGTH);

	myStrCpy(newBook.author, author, constants::AUTHOR_LENGTH);

	newBook.publicationYear = publicationYear;
	newBook.status = Status::Available;

	library.bookCount++;
	std::cout << "Book is added" << std::endl;
}

void borrowBook(Book& book) {
	if (book.status == Status::Available) {
		book.status = Status::Borrowed;
		std::cout << "Book is borrowed" << std::endl;
	}
	else {
		std::cout << "Book cannot be borrowed" << std::endl;
	}
}

void reserveBook(Book& book) {
	if (book.status == Status::Available) {
		book.status = Status::Reserved;
		std::cout << "Book is reserved" << std::endl;
	}
	else {
		std::cout << "Book cannot be reserved" << std::endl;
	}
}

void printBook(const Book& book) {
	std::cout << book.title <<
		" -> " << book.author <<
		" -> " << book.publicationYear <<
		" -> " << getStatusIntoString(book.status) << std::endl;
}

void printLibrary(const Library& library) {
	for (int i = 0; i < library.bookCount; i++) {
		printBook(library.books[i]);
	}
	std::cout << std::endl;
}

void swapBooks(Book& book1, Book& book2) {
	Book temp = book1;
	book1 = book2;
	book2 = temp;
}

void sortBooksByTitle(Book* books, int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (myStrCmp(books[j].title, books[j + 1].title) > 0) {
				swapBooks(books[j], books[j + 1]);
			}
		}
	}
}

void printLibraryAlphabetically(const Library& library) {
	if (library.bookCount == 0) {
		return;
	}

	Book* sortedBooks = new Book[library.bookCount];
	for (int i = 0; i < library.bookCount; i++) {
		sortedBooks[i] = library.books[i];
	}

	sortBooksByTitle(sortedBooks, library.bookCount);

	for (int i = 0; i < library.bookCount; i++) {
		printBook(sortedBooks[i]);
	}
	std::cout << std::endl;

	delete[] sortedBooks;
}

int main()
{
	Library library{"Library", {}, 0};

	addBook(library, "Something", "Someone", 725);
	addBook(library, "1384", "Author", 1249);
	addBook(library, "Harry Potter", "Myself", 1432);

	borrowBook(library.books[1]);

	printLibrary(library);
	printLibraryAlphabetically(library);

    return 0;
}