#include <iostream>

const size_t MAX_TITLE = 64;
const size_t MAX_AUTHOR = 32;
const size_t MAX_LIBRARY_NAME = 32;
const size_t MAX_BOOKS = 10;

size_t myStrlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}
void myStrcopy(char* dest, const char* src) {
    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
int myStrcmp(const char* str1, const char* str2) {
    size_t i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

enum Status {
    Available,
    Borrowed,
    Reserved
};
struct Book {
    char title[MAX_TITLE + 1] = "";
    char author[MAX_AUTHOR + 1] = "";
    int publicationYear = 0;
    Status status = Available;
};
struct Library {
    char name[MAX_LIBRARY_NAME + 1] = "";
    Book books[MAX_BOOKS];
    int bookCount = 0;
};

void addBook(Library& lib, const char* title, const char* author, int year) {
    if (lib.bookCount >= MAX_BOOKS) {
        std::cout << "Library is full!\n";
        return;
    }

    if (myStrlen(title) > MAX_TITLE || myStrlen(author) > MAX_AUTHOR) {
        std::cout << "Title or author too long!\n";
        return;
    }

    Book& newBook = lib.books[lib.bookCount];

    myStrcopy(newBook.title, title);
    myStrcopy(newBook.author, author);
    newBook.publicationYear = year;
    newBook.status = Available;

    lib.bookCount++;
}
void borrowBook(Book& book) {
    if (book.status == Available) book.status = Borrowed;
    else std::cout << "Book cannot be borrowed!\n";
}
void reserveBook(Book& book) {
    if (book.status == Available) book.status = Reserved;
    else std::cout << "Book cannot be reserved!\n";
}
const char* statusToString(Status status) {
    switch (status) {
        case Available: return "Available";
        case Borrowed: return "Borrowed";
        case Reserved: return "Reserved";
        default: return "Unknown";
    }
}

void printBook(const Book& book, const int& num) {
    std::cout << num << ".    ";
    std::cout << book.title << " by ";
    std::cout << book.author << " (";
    std::cout << book.publicationYear << ") - ";
    std::cout << statusToString(book.status) << "\n";
}
void printLibrary(const Library& lib) {
    std::cout << "Library: " << lib.name << "\n";
    for (int i = 0; i < lib.bookCount; i++) {
        const Book& b = lib.books[i];
        printBook(b, i + 1);
    }
}
void printLibraryAlphabetically(const Library& lib) {
    if (!lib.bookCount) {
        return;
    }

    Book temp[MAX_BOOKS];
    for (int i = 0; i < lib.bookCount; i++) {
        temp[i] = lib.books[i];
    }

    for (int i = 0; i < lib.bookCount - 1; i++) {
        for (int j = 0; j < lib.bookCount - i - 1; j++) {
            if (myStrcmp(temp[j].title, temp[j + 1].title) > 0) {
                Book swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    std::cout << "Library (Alphabetically): " << lib.name << "\n";
    for (int i = 0; i < lib.bookCount; i++) printBook(temp[i], i + 1);
}

int main() {
    Library lib{};
    myStrcopy(lib.name, "404 Library");

    addBook(lib, "TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST", "random", 2026);
    addBook(lib, "random", "TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST", 2026);

    addBook(lib, "The Hobbit", "Tolkien", 1937);
    addBook(lib, "The Lord of the Rings", "Tolkien", 1954);
    addBook(lib, "1984", "Orwell", 1949);
    addBook(lib, "Brave New World", "Huxley", 1932);
    addBook(lib, "Fahrenheit 451", "Bradbury", 1953);
    addBook(lib, "The Catcher in the Rye", "Salinger", 1951);
    addBook(lib, "Moby Dick", "Melville", 1851);
    addBook(lib, "War and Peace", "Tolstoy", 1869);
    addBook(lib, "Crime and Punishment", "Dostoevsky", 1866);
    addBook(lib, "The Great Gatsby", "Fitzgerald", 1925);
    addBook(lib, "To Kill a Mockingbird", "Lee", 1960);

    borrowBook(lib.books[1]);
    reserveBook(lib.books[2]);

    printLibrary(lib);
    std::cout << "\n";
    printLibraryAlphabetically(lib);

    return 0;
}
