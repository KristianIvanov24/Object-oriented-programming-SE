#pragma once
#include <fstream>
#include "Mystring.h"

class Item
{
private:
	MyString name;
	unsigned quantity;
	double price;
public:
	void write(std::ofstream& ofs) const; 
	void read(std::ifstream& ifs);

	const MyString& getName() const;
	double getPrice() const;
};

