#include <iostream>
#include <cstring>

namespace constants {
    const size_t TITLE_SIZE = 64;
    const size_t AUTHOR_SIZE = 32;
    const size_t NAME_SIZE = 32;
    const size_t BOOK_SIZE = 10;
}

enum Status {
    Available,
    Borrowed,
    Reserved
};

struct Book {
    char title[constants::TITLE_SIZE + 1];
    char author[constants::AUTHOR_SIZE + 1];
    int publicationYear;
    Status status;
};

class Library {
public:
    char name[constants::NAME_SIZE + 1];
    Book books[constants::BOOK_SIZE];
    int bookCount;
};

void addBook(Library& l, const char* title, const char* author, int year) {
    if (l.bookCount >= constants::BOOK_SIZE) {
        std::cout << "The library is full" << '\n';
        return;
    }

    Book& newBook = l.books[l.bookCount];
    strncpy(newBook.title, title, constants::TITLE_SIZE);
    newBook.title[constants::TITLE_SIZE] = '\0';

    strncpy(newBook.author, author, constants::AUTHOR_SIZE);
    newBook.author[constants::AUTHOR_SIZE] = '\0';

    newBook.publicationYear = year;
    newBook.status = Available;

    l.bookCount++;
}

void borrowBook(Book& book) {
    if (book.status = Available) {
        book.status = Borrowed;
    }
    else {
        std::cout << "The book is not avilable for borrowing" << '\n';
    }
}

void reserveBook(Book& book) {
    if (book.status == Available) {
        book.status = Reserved;
    }
    else {
        std::cout << "The book can not be reserved" << '\n';
    }
}

const char* statusToString(Status status) {
    switch (status) {
    case Available: 
        return "Available";
    case Borrowed: 
        return "Borrowed";
    case Reserved: 
        return "Reserved";
    default: 
        return "Unknown";
    }
}

void printLibrary(const Library& l) {
    std::cout << "Library: " << l.name << '\n';
    std::cout << "Books:\n";

    for (int i = 0; i < l.bookCount; i++) {
        const Book& b = l.books[i];
        std::cout << "TItle: " << b.title << ", Author: " << b.author 
            << ", Year of publication: " << b.publicationYear << ", Status: " << statusToString(b.status) << '\n';
    }
}

void printLibraryAlphabetically(const Library& l) {
    if (l.bookCount == 0) {
        return;
    }

    Book sorted[constants::BOOK_SIZE];

    for (int i = 0; i < l.bookCount; i++) {
        sorted[i] = l.books[i];
    }

    for (int i = 0; i < l.bookCount - 1; i++) {
        for (int j = 0; j < l.bookCount - i - 1; j++) {
            if (strcmp(sorted[j].title, sorted[j + 1].title) > 0) {
                Book temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    std::cout << "Library (Alphabetically): " << l.name << "\n";

    for (int i = 0; i < l.bookCount; i++) {
        std::cout << "Title: " << sorted[i].title << ", Author: " << sorted[i].author
            << ", Year of publication: " << sorted[i].publicationYear << ", Status: " << statusToString(sorted[i].status)<< "\n";
    }
}

int main()
{
  
}

