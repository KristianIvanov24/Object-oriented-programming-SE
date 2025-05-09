#include "ArraySet.h"

ArraySet::ArraySet(int n)
{
    this->n = n;
    size = 0;
    arr = new int[n] {0};
}

bool ArraySet::insert(int x)
{
    if(member(x) || size == n)
         return false;
    arr[size++] = x;
    return true;
}

bool ArraySet::remove(int x)
{
    for(size_t i = 0; i < size; i++)
    {
        if (arr[i] == x)
        {
            for (size_t j = i; j < size - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            size--;
            return true;
        }
    }
    
    return false;
}

bool ArraySet::member(int x) const
{
    for (size_t i = 0; i < size; i++)
        if (member(arr[i]))
            return true;

    return false;
}

int ArraySet::get(int i) const
{
    if (i < n)
        return arr[i];

    else throw std::exception("invalid index");
}

bool ArraySet::isSubstetOf(const IntSet& s) const
{
    for (size_t i = 0; i < size; i++)
        if (!s.member(arr[i]))
            return false;

    return true;
}

bool ArraySet::intersects(const IntSet& s) const
{
    for (size_t i = 0; i < size; i++)
        if (s.member(arr[i]))
            return true;

    return false;
}

IntSet* ArraySet::clone() const
{
    return new ArraySet(*this);
}
