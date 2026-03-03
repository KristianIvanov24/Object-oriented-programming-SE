#include <iostream>

namespace constants
{
    const size_t MAX_TITLE_SIZE = 64;
    const size_t MAX_NAME_SIZE = 32;
    const size_t MAX_BOOKS = 10;
}

enum class Status
{
    Available,
    Borrowed,
    Reserved
};

struct Book
{
    char title[constants::MAX_TITLE_SIZE];
    char author[constants::MAX_NAME_SIZE];
    int publicationYear;
    Status status;
};

class Library
{
    public:
        char name[constants::MAX_NAME_SIZE];
        Book books[constants::MAX_BOOKS];
        size_t bookCount;
};

void myStrCopy(char* dest,const char* source)
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

bool addBook(Library& library, const char* title, const char* author, int publicationYear)
{
    if (library.bookCount < constants::MAX_BOOKS)
    {
        int currIndex = library.bookCount;
        Book book;
        myStrCopy(book.title, title);
        myStrCopy(book.author, author);
        book.publicationYear = publicationYear;
        book.status = Status::Available;
        library.books[currIndex] = book;
        library.bookCount++;
        return true;
    }
    return false;
}

void borrowBook(Book& book)
{
    book.status = Status::Borrowed;
}

void reserveBook(Book& book)
{
    book.status = Status::Reserved;
}

void printLibrary(const Library& library)
{
    std::cout << library.name << ':' << std::endl;
    for (int i = 0;i < library.bookCount;i++)
    {
        std::cout << "Book " << i + 1 << ": " << library.books[i].title << " by " << library.books[i].author << ' ' << library.books[i].publicationYear << " - ";
        switch (library.books[i].status)
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
        std::cout << std::endl;
    }
}

int myStrCmp(const char* str1,const char* str2)
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

void insertionSort(int indexes[], const Library& library)
{
    for (int i = 1;i < library.bookCount;i++)
    {
        int currElement = indexes[i];
        int currIndex = i - 1;
        while (currIndex >= 0 && myStrCmp(library.books[indexes[currIndex]].title, library.books[currElement].title) > 0)
        {
            indexes[currIndex + 1] = indexes[currIndex];
            currIndex--;
        }
        indexes[currIndex + 1] = currElement;
    }
}

void printLibraryAlphabetically(const Library& library)
{
    int indexes[constants::MAX_BOOKS];
    for (int i = 0;i < library.bookCount;i++)
    {
        indexes[i] = i;
    }
    insertionSort(indexes, library);
    std::cout << library.name << ':' << std::endl;
    for (int i = 0;i < library.bookCount;i++)
    {
        std::cout << "Book " << i + 1 << ": " << library.books[indexes[i]].title << " by " << library.books[indexes[i]].author << ' ' << library.books[indexes[i]].publicationYear << " - ";
        switch (library.books[indexes[i]].status)
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
        std::cout << std::endl;
    }
}

int main()
{
    Library library;
    library.bookCount = 0;
    myStrCopy(library.name, "FMI Library");
    addBook(library, "zapiski po algebra", "umni hora", 2015);
    addBook(library, "fmi uchebnik", "chovek", 2004);
    addBook(library, "q", "test", 2004);
    addBook(library, "j", "test", 2004);
    addBook(library, "a", "test", 2004);
    addBook(library, "p", "test", 2004);
    addBook(library, "b", "test", 2004);
    printLibrary(library);
    std::cout << std::endl;
    printLibraryAlphabetically(library);
    std::cout << std::endl;
    borrowBook(library.books[0]);
    reserveBook(library.books[1]);
    printLibrary(library);
}

