#include <iostream>

namespace constants {
	const size_t TITLE_LEN = 64;
	const size_t AUTHOR_LEN = 32;
	const size_t NAME = 32;
	const size_t BOOK_MAX_COUNT = 10;
}

enum Status {
	Available,
	Borrowed,
	Reserved
};

struct Book {
	char title[constants::TITLE_LEN];
	char author[constants::AUTHOR_LEN];
	unsigned publicationYear;
	Status bookStatus;
};

struct Library {
	char name[constants::NAME];
	Book Book_Arr[constants::BOOK_MAX_COUNT];
	unsigned bookCount;
};

void copyString(char* destination, const char* source, int maxLen) {
	int i = 0;
	while (i < maxLen - 1 && source[i] != '\0') {
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
}

void StatusInWords(int n) {
	switch (n) {
	case 0: std::cout << "Available"; break;
	case 1: std::cout << "Borrowed"; break;
	case 2: std::cout << "Reserved"; break;
	}
}

int compareTitles(const char* t1, const char* t2) {
	int i = 0;
	while (t1[i] != '\0' && t2[i] != '\0') {
		if (t1[i] < t2[i]) return -1;
		if (t1[i] > t2[i]) return 1;
		i++;
	}
	return 0;
}
//char ignoreWhiteSpace(char* title) { 
//	for (int i = 0; i < constants::TITLE_LEN; i++) {
//		if (title[i] = ' ') {
//			title[i] = '_';
//		}
//	}
//	return *title;
// }

void addBook(Library& Library, const char* title, const char* author, int publicationYear) {
	if ((int)Library.bookCount >= constants::BOOK_MAX_COUNT) {
		std::cout << "Library is full!\n";
		return;
	}
	Book& newBook = Library.Book_Arr[(int)Library.bookCount];
	copyString(newBook.title, title, constants::TITLE_LEN);
	copyString(newBook.author, author, constants::AUTHOR_LEN);
	newBook.publicationYear = publicationYear;
	newBook.bookStatus = Status::Available;
	(int)Library.bookCount++;
}

void borrowBook(Book& Book) {
	if ((int)Book.bookStatus == 0) {
		Book.bookStatus = Status::Borrowed;
		std::cout << "Book borrowed!";
	}
	else std::cout << "Book not available or reserved!";
}

void reserveBook(Book& B) {
	if ((int)B.bookStatus == 0) {
		B.bookStatus = Status::Reserved;
		std::cout << "Book reserved!";
	}
	else std::cout << "Book not available or borrowed!";
}

void printLibrary(const Library& Library) {
	if ((int)Library.bookCount == 0) {
		std::cout << "Library is empty.\n";
		return;
	}
	for (int i = 0; i < (int)Library.bookCount; i++) {
		std::cout << "Title: " << Library.Book_Arr[i].title << std::endl;
		std::cout << "Status: ";
		int status = { (int)Library.Book_Arr[i].bookStatus };
		StatusInWords(status);
		std::cout << std::endl;
	}
}

void LibAlphabetical(Library Library) {
	for (int i = 0; i < (int)Library.bookCount - 1; i++) {
		for (int j = 0; j < (int)Library.bookCount - i - 1; j++) {

			if (compareTitles(Library.Book_Arr[j].title, Library.Book_Arr[j + 1].title) > 0) {
				Book temp = Library.Book_Arr[j];
				Library.Book_Arr[j] = Library.Book_Arr[j + 1];
				Library.Book_Arr[j + 1] = temp;
			}
		}
	}
	printLibrary(Library);
}

int main() {
	char title[constants::TITLE_LEN], author[constants::AUTHOR_LEN];
	int publicationYear;
	Library Library;
	Library.bookCount = 0;
	bool anotherBook = 0;
	while (Library.bookCount <= constants::BOOK_MAX_COUNT) {
		bool anotherBook = false;
		std::cout << "Add a book!\n";
		std::cout << "Title: ";
		std::cin >> title;
		std::cout << "Author: ";
		std::cin >> author;
		std::cout << "Publication year: ";
		std::cin >> publicationYear;
		std::cout << std::endl;
		addBook(Library, title, author, publicationYear);
		std::cout << "Do you want to add another book? Yes(1) or No(0)?\n";
		int answer;
		std::cin >> answer;
		if (answer == 1) { anotherBook = true; }
		else anotherBook = false;
		if (anotherBook == false) { break; }
	}
	std::cout << "Chose a comand: Borrow(1), Reserve(2), Print the library(3), Print the lybrary alphabetically(4) or Exit(5)?\n";
	int comand;
	std::cin >> comand;
	while (comand != 1 && comand != 2 && comand != 3 && comand != 4 && comand != 5) {
		std::cout << "Wrong comand, please choose from 1, 2, 3, 4 or 5!\n";
		std::cin >> comand;
	}
	while (comand != 5) {
		switch (comand) {
		case 1: {
			int indexB;
			std::cout << "Which book index? ";
			std::cin >> indexB;
			borrowBook(Library.Book_Arr[indexB]);
			break;
		}
		case 2: {
			int indexR;
			std::cout << "Which book index? ";
			std::cin >> indexR;
			reserveBook(Library.Book_Arr[indexR]);
			break;
		}
		case 3: printLibrary(Library); break;
		case 4: LibAlphabetical(Library); break;
		}
		std::cout << "Pick again!\n";
		std::cin >> comand;
		if (comand == 5) {
			std::cout << "You have exited the program! :)";
		}
	}

}