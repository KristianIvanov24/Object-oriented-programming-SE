#include "Bookstore.h"
//#include<fstream>

void Bookstore::free()
{
    delete[] catalogue;
    delete[] name;
}

void Bookstore::copyFrom(const Bookstore& other)
{
    booksCnt = other.booksCnt;
    catalogue = new Book[booksCnt];
    for (size_t i = 0; i < booksCnt; i++)
    {
        catalogue[i] = other.catalogue[i];
    }
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

void Bookstore::moveFrom(Bookstore&& other) noexcept
{
    booksCnt = other.booksCnt;
    catalogue = other.catalogue;
    other.catalogue = nullptr;
    name = other.name;
    other.name = nullptr;
}

void Bookstore::resize()
{
    Book* temp = new Book[capacity * 2];
    capacity *= 2;
    for (size_t i = 0; i < booksCnt; i++)
    {
        temp[i] = catalogue[i];
    }

    delete[] catalogue;
    catalogue = temp;
}

void Bookstore::swap(size_t i1, size_t i2)
{
    Book temp = Book(catalogue[i1]);
    catalogue[i1] = catalogue[i2];
    catalogue[i2] = temp;
}

Bookstore::Bookstore()
{
    booksCnt = 0;
    catalogue = nullptr;
    name = nullptr;
}

Bookstore::Bookstore(const Bookstore& other)
{
    copyFrom(other);
}

Bookstore::Bookstore(Bookstore&& other) noexcept
{
    moveFrom(std::move(other));
}

Bookstore& Bookstore::operator=(const Bookstore& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Bookstore& Bookstore::operator=(Bookstore&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

Bookstore::~Bookstore()
{
    free();
}

Bookstore& Bookstore::operator+=(const Book& toAdd)
{
    if (booksCnt == capacity)
        resize();

    catalogue[booksCnt++] = toAdd;
}

Bookstore& Bookstore::operator-=(int id)
{
    for (size_t i = 0; i < booksCnt; i++)
    {
        if (catalogue[i].getId() == id)
        {
            swap(i, booksCnt - 1);
            break;
        }
    }

    booksCnt--;
}

void Bookstore::write(std::ofstream& ofs) const
{
    ofs.write((const char*)this, sizeof(this));
}

void Bookstore::read(std::ifstream& ifs)
{
    ifs.read((char*)this, sizeof(this));
}

void Bookstore::write(const char* filePath) const
{
    std::ofstream ofs(filePath, std::ios::binary);
    write(ofs);
}

void Bookstore::read(const char* filePath)
{
    std::ifstream ifs(filePath, std::ios::binary);
    read(ifs);
}

size_t Bookstore::getBooksCount() const
{
    return booksCnt;
}

bool operator<(const Bookstore& lhs, const Bookstore& rhs)
{
    return lhs.getBooksCount() < rhs.getBooksCount();
}
