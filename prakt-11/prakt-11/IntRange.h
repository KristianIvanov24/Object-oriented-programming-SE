#pragma once
#include "IntSet.h"

class IntRange : IntSet
{
private:
	int beg, end;
public:
	IntRange(int beg, int end);

	bool member(int x) const override;
	int get(int i) const override;
	bool isSubstetOf(const IntSet& s) const override;
	bool intersects(const IntSet& s) const override;
	IntSet* clone() const override;
};

