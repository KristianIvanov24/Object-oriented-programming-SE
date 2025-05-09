#pragma once
#include <fstream>
#include "Book.h"

class Bookstore
{
private:
	char* name;
	Book* catalogue;
	size_t booksCnt, capacity;

	void free();
	void copyFrom(const Bookstore& other);
	void moveFrom(Bookstore&& other) noexcept;
	void resize();
	void swap(size_t i1, size_t i2);
public:
	Bookstore();
	Bookstore(const Bookstore& other);
	Bookstore(Bookstore&& other) noexcept;
	Bookstore& operator=(const Bookstore& other);
	Bookstore& operator=(Bookstore&& other) noexcept;
	~Bookstore();

	Bookstore& operator+=(const Book& toAdd);
	Bookstore& operator-=(int id);

	void write(std::ofstream& ofs) const;
	void read(std::ifstream& ifs);

	void write(const char* filePath) const;
	void read(const char* filePath);

	size_t getBooksCount() const;
};

bool operator<(const Bookstore& lhs, const Bookstore& rhs);
