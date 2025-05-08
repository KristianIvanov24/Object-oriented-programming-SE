#pragma once
#include <iostream>

class IntSet
{
public:
	virtual  bool member(int x) const = 0;
	virtual int get(int i) const = 0;
	virtual bool isSubstetOf(const IntSet& s) const = 0;
	virtual bool intersects(const IntSet& s) const = 0;
	virtual IntSet* clone() const = 0;
};

