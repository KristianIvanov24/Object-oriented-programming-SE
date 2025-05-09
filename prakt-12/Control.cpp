#include "Control.h"

Control::Control()
{
	size = 0;
	location = { 0,0 };
}

Control::Control(size_t size, const Pos& location)
{
	this->size = size;
	this->location = location;
}

void Control::resize(size_t size)
{
	this->size = size;
}

void Control::changeLocation(const Pos& loc)
{
	location = loc;
}
