#include "Webpage.h"
#include <cstring>
#pragma warning (disable:4996)

void Webpage::free()
{
	delete[] address;

	address = nullptr;
	strcpy(IPAdress, "");
}

void Webpage::copyFrom(const Webpage& other)
{
	address = new char[strlen(other.address) + 1];

	strcpy(address, other.address);
	strcpy(IPAdress, other.IPAdress);
}

Webpage::Webpage()
{
	address = nullptr;
	strcpy(IPAdress, "");
}

Webpage::Webpage(const char* address, const char* IPAddress)
{
	if (!address || !IPAddress)
	{
		this->address = nullptr;
		strcpy(this->IPAdress, "");
		return;
	}

	this->address = new char[strlen(address) + 1];

	strcpy(this->address, address);
	strcpy(this->IPAdress, IPAddress);
}

Webpage::Webpage(const Webpage& other)
{
	copyFrom(other);
}

Webpage& Webpage::operator=(const Webpage& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Webpage::~Webpage()
{
	free();
}

std::ostream& operator<<(std::ostream& os, const Webpage& webpage)
{
	os << strlen(webpage.address) << std::endl 
		<< webpage.address << std::endl 
		<< webpage.IPAdress;

	return os;
}

std::istream& operator>>(std::istream& is, Webpage& webpage)
{
	webpage.free();

	size_t addressSize;
	is >> addressSize;

	webpage.address = new char[addressSize + 1];
	is >> webpage.address >> webpage.IPAdress;

	return is;
}

bool Webpage::operator==(const Webpage& other)
{
	return strcmp(address, other.address) == 0 && strcmp(IPAdress, other.IPAdress) == 0;
}

bool Webpage::operator!=(const Webpage& other)
{
	return !(*this == other);
}