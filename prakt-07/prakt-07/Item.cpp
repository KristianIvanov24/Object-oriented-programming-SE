#include "Item.h"

void Item::write(std::ofstream& ofs) const
{
	name.write(ofs);
	ofs.write((const char*)&quantity, sizeof(quantity));
	ofs.write((const char*)&price, sizeof(price));
}

void Item::read(std::ifstream& ifs)
{
	name.read(ifs);
	ifs.read((char*)&quantity, sizeof(quantity));
	ifs.read((char*)&price, sizeof(price));
}

const MyString& Item::getName() const
{
	return name;
}

double Item::getPrice() const
{
	return price;
}
