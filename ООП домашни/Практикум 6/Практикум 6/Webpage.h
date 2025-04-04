#pragma once
#include "Constants.h"
#include <iostream>

class Webpage
{
private:
	char* address = nullptr;
	char IPAdress[Constants::MAX_IP_ADDRESS_SIZE];

	void free();
	void copyFrom(const Webpage&);
public:
	Webpage();
	Webpage(const char*, const char*);
	Webpage(const Webpage&);
	Webpage& operator=(const Webpage&);
	~Webpage();

	friend std::ostream& operator<<(std::ostream&, const Webpage&);
	friend std::istream& operator>>(std::istream&, Webpage&);

	bool operator==(const Webpage&);
	bool operator!=(const Webpage&);
};

