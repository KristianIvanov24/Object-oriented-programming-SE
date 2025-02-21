#pragma warning (disable:4996)

#include <cstring>
#include <iostream>

namespace stringHelpers
{
	bool isDigitChar(char ch)
	{
		return ch >= '0' && ch <= '9';
	}

	unsigned charToDigit(char ch)
	{
		if (!isDigitChar(ch))
		{
			return 0;
		}

		return ch - '0';
	}

	unsigned strToUnsigned(const char* str)
	{
		if (!str)
		{
			return 0;
		}

		unsigned int result = 0;

		while (*str)
		{
			if (!isDigitChar(*str))
			{
				return 0;
			}

			result = result * 10 + charToDigit(*str);
			str++;
		}

		return result;
	}

	int strToNum(const char* const str)
	{
		if (!str)
		{
			return 0;
		}

		if (*str == '-')
		{
			return -1 * strToUnsigned(str + 1);
		}

		return strToUnsigned(str);
	}
}

namespace io
{
	const unsigned MAX_CIN_BUFFER_SIZE = 512;

	void input(char* result)
	{
		if (!result)
		{
			return;
		}

		std::cin.getline(result, MAX_CIN_BUFFER_SIZE, '\n');
	}

	void input(int& result)
	{
		char resultStr[MAX_CIN_BUFFER_SIZE]{};

		std::cin.getline(resultStr, MAX_CIN_BUFFER_SIZE, '\n');

		result = stringHelpers::strToNum(resultStr);
	}

	void printNewLine()
	{
		std::cout << std::endl;
	}

	void printNewLines(unsigned count)
	{
		while (count)
		{
			printNewLine();
			count--;
		}
	}

	void print(const char* const toPrint, unsigned newLinesCount = 1)
	{
		std::cout << toPrint;
		printNewLines(newLinesCount);
	}

	void print(int toPrint, unsigned newLinesCount = 1)
	{
		std::cout << toPrint;
		printNewLines(newLinesCount);
	}

	void clearConsole()
	{
		// idk if legal? :)
		system("cls");
	}

	void pauseConsole()
	{
		printNewLine();
		print("Press any key to continue...");
		std::cin.get();
	}
}

namespace enums
{
	enum Status
	{
		Available,
		Borrowed,
		Reserved,
	};

	const char* getStatus(Status status)
	{
		switch (status)
		{
			case Status::Available:
				return "Available";

			case Status::Reserved:
				return "Reserved";

			case Status::Borrowed:
				return "Borrowed";

			default:
				return "No status";
		}
	}

	enum AddBookState
	{
		LibraryIsFull,
		AlreadyExists,
		InvalidData,
		Success
	};

	const char* getAddBookState(AddBookState state)
	{
		switch (state)
		{
			case AddBookState::LibraryIsFull:
				return "The book could not be added because the library is full!";

			case AddBookState::AlreadyExists:
				return "The book could not be added because such book already exists!";

			case AddBookState::InvalidData:
				return "Invalid input given! Please try again";

			case AddBookState::Success:
				return "Book added successfully!";

			default:
				return "Oops! Something must have gone wrong! Please try again!";
		}
	}
}

namespace utils
{
	bool isInRange(unsigned len, unsigned min, unsigned max)
	{
		return len >= min && len <= max;
	}

	bool isInRange(const char* str, unsigned min, unsigned max)
	{
		if (!str)
		{
			return false;
		}

		unsigned len = strlen(str);

		return isInRange(len, min, max);
	}

	void setStrProp(char* prop, const char* value)
	{
		if (!prop || !value)
		{
			return;
		}

		strcpy(prop, value);
	}

	void setNumProp(int* prop, int* value)
	{
		if (!prop || !value)
		{
			return;
		}

		*prop = *value;
	}
}

namespace bookConstants
{
	const unsigned MIN_TITLE_LENGTH = 2;
	const unsigned MAX_TITLE_LENGTH = 100;

	const unsigned MIN_AUTHOR_LENGTH = 2;
	const unsigned MAX_AUTHOR_LENGTH = 50;

	const unsigned MIN_PUBLICATION_YEAR = 0;
	const unsigned MAX_PUBLICATION_YEAR = 2025;

	const unsigned DEFAULT_PUBLICATION = 2025;
	const enums::Status DEFAULT_STATUS = enums::Status::Available;
}

namespace libraryConstants
{
	const unsigned MIN_NAME_LENGTH = 1;
	const unsigned MAX_NAME_LENGTH = 100;

	const unsigned MAX_BOOK_COUNT = 10;
	const unsigned DEFAULT_BOOK_COUNT = 0;
}

namespace bookLogic
{
	using namespace bookConstants;

	struct Book
	{
		char title[MAX_TITLE_LENGTH + 1] = {};
		char author[MAX_AUTHOR_LENGTH + 1] = {};
		int publicationYear = DEFAULT_PUBLICATION;
		enums::Status status = DEFAULT_STATUS;
	};

	bool setBookTitle(Book& book, const char* title)
	{
		if (!title)
		{
			return false;
		}

		if (!utils::isInRange(title, MIN_TITLE_LENGTH, MAX_TITLE_LENGTH))
		{
			return false;
		}

		utils::setStrProp(book.title, title);
		return true;
	}

	bool setBookAuthor(Book& book, const char* author)
	{
		if (!author)
		{
			return false;
		}

		if (!utils::isInRange(author, MIN_AUTHOR_LENGTH, MAX_AUTHOR_LENGTH))
		{
			return false;
		}

		utils::setStrProp(book.author, author);
		return true;
	}

	bool setBookPublication(Book& book, int publicationYear)
	{
		if (!utils::isInRange(publicationYear, MIN_PUBLICATION_YEAR, MAX_PUBLICATION_YEAR))
		{
			return false;
		}

		utils::setNumProp(&book.publicationYear, &publicationYear);
		return true;
	}

	Book initBook(const char* title, const char* author, int publicationYear, bool& isValid)
	{
		Book book;

		bool titleIsSet = setBookTitle(book, title);
		bool authorIsSet = setBookAuthor(book, author);
		bool publicationIsSet = setBookPublication(book, publicationYear);

		isValid = titleIsSet && authorIsSet && publicationIsSet;

		return book;
	}

	void borrowBook(Book& book)
	{
		book.status = enums::Status::Borrowed;
	}

	void reserveBook(Book& book)
	{
		book.status = enums::Status::Reserved;
	}

	void printBook(const Book& book)
	{
		io::print("Title: ", 0);
		io::print(book.title);

		io::print("  By: ", 0);
		io::print(book.author);

		io::print("  Published in: ", 0);
		io::print(book.publicationYear);

		io::print("  Current status: ", 0);
		io::print(getStatus(book.status));
	}
}

namespace libraryLogic
{
	using namespace libraryConstants;

	struct Library
	{
		char name[MAX_NAME_LENGTH + 1] = {};
		bookLogic::Book books[MAX_BOOK_COUNT] = {};
		unsigned bookCount = DEFAULT_BOOK_COUNT;
	};

	bool setLibraryName(Library& lib, const char* const name)
	{
		if (!name)
		{
			return false;
		}

		if (!utils::isInRange(name, MIN_NAME_LENGTH, MAX_NAME_LENGTH))
		{
			return false;
		}

		utils::setStrProp(lib.name, name);
		return true;
	}

	Library initLibrary(const char* const name, bool& isValid)
	{
		Library lib;

		bool nameIsSet = setLibraryName(lib, name);
		isValid = nameIsSet;

		return lib;
	}

	bool isLibraryFull(Library& lib)
	{
		return lib.bookCount == MAX_BOOK_COUNT;
	}

	bookLogic::Book* findBook(Library& lib, const char* const title, const char* const author)
	{
		if (!title || !author)
		{
			return nullptr;
		}

		for (size_t i = 0; i < lib.bookCount; i++)
		{
			bookLogic::Book* book = &lib.books[i];

			if (!strcmp(title, (*book).title) && !strcmp(author, (*book).author))
			{
				return book;
			}
		}

		return nullptr;
	}

	bool bookExists(Library& lib, const char* const title, const char* const author)
	{
		if (!title || !author)
		{
			return false;
		}

		return findBook(lib, title, author);
	}

	enums::AddBookState addBook(Library& lib, const char* title, const char* author, int publicationYear)
	{
		if (!title || !author)
		{
			return enums::AddBookState::InvalidData;
		}

		if (isLibraryFull(lib))
		{
			return enums::AddBookState::LibraryIsFull;
		}

		if (bookExists(lib, title, author))
		{
			return enums::AddBookState::AlreadyExists;
		}

		bool isValid = false;
		bookLogic::Book book = bookLogic::initBook(title, author, publicationYear, isValid);
		if (!isValid)
		{
			return enums::AddBookState::InvalidData;
		}

		lib.books[lib.bookCount] = book;
		lib.bookCount++;

		return enums::AddBookState::Success;
	}

	void printLibrary(const Library& lib)
	{
		for (size_t i = 0; i < lib.bookCount; i++)
		{
			bookLogic::printBook(lib.books[i]);

			io::printNewLine();
		}
	}
}

namespace panel
{
	using namespace io;

	void printOptions()
	{
		print("1. Display books");
		print("2. Add book");
		print("3. Borrow a book");
		print("4. Reserve a book");
	}

	void runDisplayBooks(const libraryLogic::Library& lib)
	{
		if (lib.bookCount == 0)
		{
			print("No books available right now!");
			return;
		}

		libraryLogic::printLibrary(lib);
	}

	void runAddBook(libraryLogic::Library& lib)
	{
		clearConsole();
		print("-- Add book --", 2);

		char title[bookConstants::MAX_TITLE_LENGTH + 1] = {};
		char author[bookConstants::MAX_AUTHOR_LENGTH + 1] = {};
		int publicationYear = -1;

		print("Title: ", 0);
		input(title);

		print("Author: ", 0);
		input(author);

		print("Publication year: ", 0);
		input(publicationYear);

		enums::AddBookState state = libraryLogic::addBook(lib, title, author, publicationYear);

		printNewLine();
		print(enums::getAddBookState(state));
	}

	void borrowReserveBookHelper(
		libraryLogic::Library& lib,
		void (*mutator)(bookLogic::Book&))
	{
		if (lib.bookCount == 0)
		{
			print("No books available right now!");
			return;
		}

		print("-- Available books --");
		libraryLogic::printLibrary(lib);

		char title[bookConstants::MAX_TITLE_LENGTH + 1] = {};
		char author[bookConstants::MAX_AUTHOR_LENGTH + 1] = {};

		print("Please choose a book from the list above: ");
		print("Title: ", 0);
		input(title);

		print("Author: ", 0);
		input(author);

		bookLogic::Book* book = libraryLogic::findBook(lib, title, author);
		if (!book)
		{
			printNewLine();
			print("No book with such name and author was found!");
			return;
		}

		mutator(*book);
		printNewLine();
		print("Book status changed successfully!");
	}

	void runBorrowBook(libraryLogic::Library& lib)
	{
		clearConsole();
		print("-- Borrow a book --", 2);

		borrowReserveBookHelper(lib, bookLogic::borrowBook);
	}

	void runReserveBook(libraryLogic::Library& lib)
	{
		clearConsole();
		print("-- Reserve a book --", 2);

		borrowReserveBookHelper(lib, bookLogic::reserveBook);
	}

	void routeToOption(int option, libraryLogic::Library& lib)
	{
		switch (option)
		{
			case 1: panel::runDisplayBooks(lib); break;
			case 2: panel::runAddBook(lib);  break;
			case 3: panel::runBorrowBook(lib); break;
			case 4:	panel::runReserveBook(lib); break;
			default:
			{
				clearConsole();
				print("Invalid option! Please choose an option from the provided list!");
				break;
			}
		}
	}
}

int main()
{
	using namespace io;

	libraryLogic::Library lib;

	while (true)
	{
		char libName[libraryConstants::MAX_NAME_LENGTH + 1] = {};
		print("Choose a name for your library: ", 0);
		input(libName);

		bool isValid = false;
		lib = libraryLogic::initLibrary(libName, isValid);

		if (isValid)
		{
			break;
		}

		print("Invalid library name! Please try again!", 2);
	}

	clearConsole();

	while (true)
	{
		print(lib.name, 0);
		print(" Library Managment System", 2);

		panel::printOptions();
		printNewLine();

		print("Input an option: ", 0);
		int option = -1;
		input(option);

		clearConsole();

		panel::routeToOption(option, lib);

		pauseConsole();
		clearConsole();
	}

}
