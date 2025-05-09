#pragma once
#include "Webpage.h"
static int constexpr MAX_WEBPAGES_CNT = 30;

class Browser
{
private:
	Webpage web[30];
	size_t pagesCnt = 0;
public:
	void addPage(const Webpage& toAdd);
	void removePage(const Webpage& toRemove);

	void operator+= (const Webpage& toAdd);
	void operator-= (size_t index);

	void printOpenPages() const;
};

