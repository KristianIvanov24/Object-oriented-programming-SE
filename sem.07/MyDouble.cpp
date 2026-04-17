#include "MyDouble.h"

MyDouble::MyDouble(int integer, unsigned fractional) : integer(integer), fractional(fractional) {}

MyDouble::MyDouble() : integer(0), fractional(0) {}

size_t MyDouble::countDigits(unsigned number)
{
    if (number == 0)
        return 1;

    size_t count = 0;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

unsigned MyDouble::addDigits(size_t exponent)
{
    unsigned result = 1;
    for (size_t i = 0; i < exponent; i++)
    {
        result *= 10;
    }
    return result;
}

MyDouble& MyDouble::operator+=(const MyDouble& other)
{
    integer += other.integer;

    size_t thisDigits = countDigits(fractional);
    size_t otherDigits = countDigits(other.fractional);
    size_t maxDigits = (thisDigits > otherDigits) ? thisDigits : otherDigits;

    unsigned thisFrac = fractional * addDigits(maxDigits - thisDigits);
    unsigned otherFrac = other.fractional * addDigits(maxDigits - otherDigits);

    fractional = thisFrac + otherFrac;

    return *this;
}

MyDouble& MyDouble::operator-=(const MyDouble& other)
{
    integer -= other.integer;

    size_t thisDigits = countDigits(fractional);
    size_t otherDigits = countDigits(other.fractional);
    size_t maxDigits = (thisDigits > otherDigits) ? thisDigits : otherDigits;

    unsigned thisFrac = fractional * addDigits(maxDigits - thisDigits);
    unsigned otherFrac = other.fractional * addDigits(maxDigits - otherDigits);

    fractional = thisFrac - otherFrac;

    return *this;
}

MyDouble& MyDouble::operator/=(const MyDouble& other)
{
    integer /= other.integer;

    size_t thisDigits = countDigits(fractional);
    size_t otherDigits = countDigits(other.fractional);
    size_t maxDigits = (thisDigits > otherDigits) ? thisDigits : otherDigits;

    unsigned thisFrac = fractional * addDigits(maxDigits - thisDigits);
    unsigned otherFrac = other.fractional * addDigits(maxDigits - otherDigits);

    fractional = thisFrac / otherFrac;

    return *this;
}

MyDouble& MyDouble::operator*=(const MyDouble& other)
{
    integer *= other.integer;

    size_t thisDigits = countDigits(fractional);
    size_t otherDigits = countDigits(other.fractional);
    size_t maxDigits = (thisDigits > otherDigits) ? thisDigits : otherDigits;

    unsigned thisFrac = fractional * addDigits(maxDigits - thisDigits);
    unsigned otherFrac = other.fractional * addDigits(maxDigits - otherDigits);

    fractional = thisFrac * otherFrac;

    return *this;
}

MyDouble operator+(const MyDouble& lhs, const MyDouble& rhs)
{
    MyDouble result = lhs;
    result += rhs;
    return result;
}

MyDouble operator*(const MyDouble& lhs, const MyDouble& rhs)
{
    MyDouble result = lhs;
    result *= rhs;
    return result;
}

MyDouble operator-(const MyDouble& lhs, const MyDouble& rhs)
{
    MyDouble result = lhs;
    result -= rhs;
    return result;
}

MyDouble operator/(const MyDouble& lhs, const MyDouble& rhs)
{
    MyDouble result = lhs;
    result /= rhs;
    return result;
}

MyDouble& MyDouble::operator++()
{
    integer++;

    return *this;
}

MyDouble MyDouble::operator++(int)
{
    //MyDouble result = *this;

    integer++;

    //return result;

    return MyDouble(integer - 1, fractional);
}

std::istream& operator>>(std::istream& is, MyDouble& d)
{
    char dot;
    is >> d.integer >> dot >> d.fractional;

    return is;
}

std::ostream& operator<<(std::ostream& os, const MyDouble& d)
{
    os << d.integer << '.' << d.fractional;

    return os;
}

bool operator==(const MyDouble& lhs, const MyDouble& rhs)
{
    return lhs.integer == rhs.integer && lhs.fractional == rhs.fractional;
}

bool operator!=(const MyDouble& lhs, const MyDouble& rhs)
{
    return !(lhs == rhs);
}

std::strong_ordering operator<=>(const MyDouble& lhs, const MyDouble& rhs)
{
    if (auto cmp = lhs.integer <=> rhs.integer; cmp != 0)
        return cmp;

    size_t thisDigits = MyDouble::countDigits(lhs.fractional);
    size_t otherDigits = MyDouble::countDigits(rhs.fractional);
    size_t maxDigits = (thisDigits > otherDigits) ? thisDigits : otherDigits;

    unsigned thisFrac = lhs.fractional * MyDouble::addDigits(maxDigits - thisDigits);
    unsigned otherFrac = rhs.fractional * MyDouble::addDigits(maxDigits - otherDigits);

    return thisFrac <=> otherFrac;
}
