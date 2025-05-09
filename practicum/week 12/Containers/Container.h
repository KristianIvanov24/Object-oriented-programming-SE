#pragma once

class Container
{
public:
	virtual bool member(double num) const = 0;
	virtual double operator[](size_t i) const = 0;
	virtual size_t count() const = 0;
	virtual void write() const = 0;
	virtual Container* clone() const = 0;
	virtual ~Container() = default;
};

