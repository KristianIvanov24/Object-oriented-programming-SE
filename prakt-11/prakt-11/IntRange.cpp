#include "IntRange.h"

IntRange::IntRange(int beg, int end) 
{
    if (beg < end)
    {
        this->beg = beg;
        this->end = end;
    }
}

bool IntRange::member(int x) const
{
    return (beg <= x && x <= end);
}

int IntRange::get(int i) const
{
    return beg + i;
}

bool IntRange::isSubstetOf(const IntSet& s) const
{
    for (int i = beg; i <= end; i++)
        if (!s.member(i))
            return false;

    return true;
}

bool IntRange::intersects(const IntSet& s) const
{
    for (int i = beg; i <= end; i++)
        if (s.member(i))
            return true;

    return false;
}

IntSet* IntRange::clone() const
{
    return new IntRange(*this);
}
