#include "Browser.h"

//void Browser::free()
//{
//
//}

void Browser::copyFrom(const Browser& other)
{
	opened = other.opened;

	for (size_t current = 0; current < other.opened; current++)
	{
		pages[current] = other.pages[current];
	}
}

Browser::Browser(const Webpage* pages, size_t opened)
{
	if (!pages || opened > Constants::MAX_OPENED_PAGES)
	{
		this->opened = 0;
		return;
	}

	this->opened = opened;
	for (size_t current = 0; current < opened; current++)
	{
		this->pages[current] = pages[current];
	}
}

Browser::Browser(const Browser& other)
{
	copyFrom(other);
}

Browser& Browser::operator=(const Browser& other)
{
	copyFrom(other);
	return *this;
}


void Browser::addPage(const Webpage& page)
{
	*this += page;
}

void Browser::removePage(const Webpage& page)
{
	if (opened <= 0)
		return;

	for (size_t current = 0; current < opened; current++)
	{
		if (pages[current] == page)
		{
			std::swap(pages[current], pages[--opened]);
			return;
		}
	}
}

void Browser::removePage(size_t index)
{
	*this -= index;
}

Browser& Browser::operator+=(const Webpage& page)
{
	if (opened < Constants::MAX_OPENED_PAGES)
	{
		pages[opened++] = page;
	}

	return *this;
}

Browser& Browser::operator-=(size_t index)
{
	if (index < 0 || index >= Constants::MAX_OPENED_PAGES || opened <= 0)
	{
		return *this;
	}

	std::swap(pages[index], pages[--opened]);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Browser& browser)
{
	for (size_t current = 0; current < browser.opened; current++) 
	{
		os << browser.pages[current];
	}

	return os;
}

