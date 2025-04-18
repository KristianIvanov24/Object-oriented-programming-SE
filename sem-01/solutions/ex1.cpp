#include <iostream>
#include <string>
#pragma warning (disable: 4996) // we use this to disable error for using strcpy

namespace constants
{
    const size_t TITLE_LEGTH = 20;
    const size_t AUTHOR_NAME_LEGTH = 30;
    const size_t LIBRARY_NAME_LENGTH = 25;
    const size_t BOOKS_CAPACITY = 10;
};

namespace LibraryManagement
{

    enum class BookStatus
    {
        Available,
        Borrowed,
        Reserved
    };

    struct Book
    {
        char title[constants::TITLE_LEGTH];
        char author[constants::AUTHOR_NAME_LEGTH];
        int publicationYear;
        BookStatus status;
    };

    struct Library
    {
        char name[constants::LIBRARY_NAME_LENGTH];
        Book books[constants::BOOKS_CAPACITY];
        int bookCount = 0;
    };


    Book createBook(const char* title, const char* author, int publicationYear)
    {
        if (!title || !author)
        {
            return {};
        }

        Book book;

        strcpy(book.title, title);
        strcpy(book.author, author);
        book.publicationYear = publicationYear;
        book.status = BookStatus::Available;

        return book;
    }

    void addBook(Library& library, const char* title, const char* author, int publicationYear)
    {
        if (library.bookCount >= constants::BOOKS_CAPACITY)
        {
            return;
        }

        library.books[library.bookCount++] = createBook(title, author, publicationYear);
    }

    void borrowBook(Book& book)
    {
        if (book.status == BookStatus::Available)
        {
            book.status = BookStatus::Borrowed;
        }
    }

    void reserveBook(Book& book)
    {
        if (book.status == BookStatus::Available)
        {
            book.status = BookStatus::Reserved;
        }
    }


    void printBookStatus(BookStatus status)
    {
        switch (status)
        {
        case BookStatus::Available:
            std::cout << "Available";
            break;
        case BookStatus::Borrowed:
            std::cout << "Borrowed";
            break;
        case BookStatus::Reserved:
            std::cout << "Reserved";
            break;
        default:
            std::cout << "Unknown";
        }
    }

    void printBook(const Book& book)
    {
        std::cout << book.title << " by " << book.author
            << " (" << book.publicationYear << ") - ";
        printBookStatus(book.status);
        std::cout << std::endl;
    }

    void printLibrary(const Library& library)
    {
        std::cout << "Library: " << library.name << std::endl;
        for (int i = 0; i < library.bookCount; i++)
        {
            std::cout << "Book " << i + 1 << ": ";
            printBook(library.books[i]);
        }
    }
}

int main()
{
    using namespace LibraryManagement;

    Library lib = { "FMI Library" };

    addBook(lib, "Under the Yoke", "Ivan Vazov", 1893);
    addBook(lib, "Tobacoo", "Dimitar Dimov", 1951);
    addBook(lib, "To Chicago and Back", "Aleko Konstantinov", 1894);

    borrowBook(lib.books[1]);
    reserveBook(lib.books[2]);

    printLibrary(lib);

    return 0;
}
