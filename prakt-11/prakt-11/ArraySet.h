#pragma once
#include "IntSet.h"
 
class ArraySet : IntSet
{
private:
	int* arr;
	size_t size;
	int n;
public:
	ArraySet(int n);
	bool insert(int x);
	bool remove(int x);

	bool member(int x) const override;
	int get(int i) const override;
	bool isSubstetOf(const IntSet& s) const override;
	bool intersects(const IntSet& s) const override;
	IntSet* clone() const override;
};