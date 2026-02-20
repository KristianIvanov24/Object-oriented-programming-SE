#include <iostream>

const int MAX_TITLE_SIZE = 64;
const int MAX_AUTHOR_SIZE = 32;
const int MAX_LIBRARY_NAME_SIZE = 32;
const int MAX_BOOKS = 10;

namespace str
{
    size_t strlen(const char *str)
    {
        if (!str)
            return 0;

        size_t result = 0;
        while (*str)
        {
            result++;
            str++;
        }

        return result;
    }

    void strcpy(char *dest, const char *source)
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

    int strcmp(const char *str1, const char *str2)
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
}

struct Book
{
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    int publicationYear;
    enum class Status
    {
        Available,
        Borrowed,
        Reserved
    } status;
};

struct Library
{
    char name[MAX_LIBRARY_NAME_SIZE];
    Book books[MAX_BOOKS];
    int bookCount = 0;

    Library(const char *libraryName) : bookCount(0)
    {
        str::strcpy(name, libraryName);
    }
};

void swap(Book &book1, Book &book2)
{
    Book temp = book1;
    book1 = book2;
    book2 = temp;
}

const char *statusToString(const Book &book)
{
    switch (book.status)
    {
        case Book::Status::Available:
            return "Available";
        case Book::Status::Borrowed:
            return "Borrowed";
        case Book::Status::Reserved:
            return "Reserved";
        default:
            return "Unknown status";
    }
}

void addBook(Library &library, const char *title, const char *author, int publicationYear)
{
    if (library.bookCount >= MAX_BOOKS)
    {
        std::cout << "Maximum books exceeded!" << std::endl;
        return;
    }

    Book &newBook = library.books[library.bookCount];

    if (str::strlen(title) >= MAX_TITLE_SIZE || str::strlen(author) >= MAX_AUTHOR_SIZE)
    {
        std::cout << "Name length exceeded!" << std::endl;
        return;
    }
    str::strcpy(newBook.title, title);
    str::strcpy(newBook.author, author);

    newBook.publicationYear = publicationYear;
    newBook.status = Book::Status::Available;
    library.bookCount++;
}

void borrowBook(Book &book)
{
    if (book.status != Book::Status::Available)
    {
        std::cout << "Book isn't available" << std::endl;
        return;
    }
    book.status = Book::Status::Borrowed;
}

void reserveBook(Book &book)
{
    if (book.status != Book::Status::Available)
    {
        std::cout << "Book isn't available" << std::endl;
        return;
    }
    book.status = Book::Status::Reserved;
}

void printBook(const Book &book)
{
    std::cout << book.title << " " << book.author << " "
              << book.publicationYear << " " << statusToString(book) << std::endl;
}

void printLibrary(const Library &library)
{
    for (int i = 0; i < library.bookCount; i++)
    {
        printBook(library.books[i]);
    }
}

void printLibraryAlphabetically(const Library &library)
{
    Book sortedBooks[MAX_BOOKS];
    for (int i = 0; i < library.bookCount; i++)
        sortedBooks[i] = library.books[i];

    for (int i = 0; i < library.bookCount - 1; i++)
    {
        for (int j = 0; j < library.bookCount - i - 1; j++)
        {
            if (str::strcmp(sortedBooks[j].title, sortedBooks[j + 1].title) > 0)
            {
                swap(sortedBooks[j], sortedBooks[j + 1]);
            }
        }
    }

    for (int i = 0; i < library.bookCount; i++)
    {
        printBook(sortedBooks[i]);
    }
}

int main()
{
    Library library("My library");

    addBook(library, "1984", "George Orwell", 1949);
    addBook(library, "Test", "John Doe", 2019);
    addBook(library, "ABC", "Jane Smith", 2010);

    borrowBook(library.books[0]);
    reserveBook(library.books[1]);

    printLibrary(library);
    std::cout << std::endl;

    printLibraryAlphabetically(library);
    return 0;
}