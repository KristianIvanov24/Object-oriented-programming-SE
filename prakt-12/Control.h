#pragma once
#include <iostream>

struct Pos
{
	int x, y;
	Pos() : x(0), y(0) {};
	Pos(int x, int y) : x(x), y(y) {};
};

class Control
{
protected:
	size_t size;
	Pos location;
public:
	Control();
	Control(size_t size, const Pos& location);
	void resize(size_t size);
	void changeLocation(const Pos& loc);
	virtual void setDataDialog() = 0;
	virtual Control* clone() const = 0;
};

