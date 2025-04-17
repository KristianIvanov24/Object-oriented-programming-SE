#pragma once
#include "Webpage.h"

class Browser
{
private:
	Webpage pages[Constants::MAX_OPENED_PAGES];
	size_t opened = 0;

	void copyFrom(const Browser&);

public:
	Browser() = default;
	Browser(const Webpage*, size_t);
	Browser(const Browser&);
	Browser& operator=(const Browser&);

	void addPage(const Webpage&);
	void removePage(const Webpage&);
	void removePage(size_t);
	
	Browser& operator+=(const Webpage&);
	Browser& operator-=(size_t);

	friend std::ostream& operator<<(std::ostream&, const Browser&);
};

