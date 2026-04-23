#include <iostream>
#include "Rational.h"


Rational::Rational() : p(0), q(1)
{
}

Rational::Rational(int n) : p(n), q(1)
{
}

Rational::Rational(int num, int den)
{
    if (den == 0) {
        den = 1;
    }
    else if (den < 0) {
        num = -1;
        den = -1;
    }

    p = num;
    q = den;
    rationalize();
}

int Rational::getP() const
{
    return p;
}

int Rational::getQ() const
{
    return q;
}


int Rational::NOD(int a, int b) const
{
    if (a < 0) {
        a *= -1;
    }

    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }

    return a;
}

void Rational::rationalize()
{
    if (p == 0) {
        q = 1;
        return;
    }

    int nod = NOD(p, q);
    p /= nod;
    q /= nod;
}

void Rational::addSubHelper(const Rational& other, int(*op)(int lhs, int rhs))
{
    p = op(p * other.q, other.p * q);
    q *= other.q;

    rationalize();
}

Rational& Rational::operator+=(const Rational& other)
{
    addSubHelper(other, [](int lhs, int rhs)
        { return lhs + rhs; });

    return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
    addSubHelper(other, [](int lhs, int rhs)
        { return lhs - rhs; });

    return *this;
}
Rational& Rational::operator/=(const Rational& other)
{
    if (other.p == 0) {
        other.p == 1;
    }
    p *= other.q;
    q *= other.p;

    rationalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& other)
{
    p *= other.p;
    q *= other.q;

    rationalize();
    return *this;
}

Rational Rational::operator-() const
{
    return { -p, q };
}

Rational::operator double() const
{
    return (double)p / q;
}

Rational::operator bool() const
{
    return p != 0;
}

bool Rational::operator==(const Rational& other) const
{
    return (p == other.p && q == other.q) ? true : false;
}

std::strong_ordering Rational::operator<=>(const Rational& other) const
{
    int lhs = p *other.q;
    int rhs = other.p * q;

    if (lhs < rhs) return std::strong_ordering::less;
    if (lhs > rhs) return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

Rational& Rational::operator++()
{
    p += q;

    rationalize();
    return *this;
}
Rational Rational::operator++(int)
{
    Rational old = *this;
    ++(*this);
    return old;
}

Rational& Rational::operator--()
{
    p -= q;
    rationalize();
    return *this;
}
Rational Rational::operator--(int)
{
    Rational old = *this;
    --(*this);
    return old;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational res = lhs;
    return res += rhs;;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational res = lhs;
    return res -= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational res = lhs;
    return res /= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational res = lhs;
    return res *= rhs;
}

std::ostream& operator<<(std::ostream& os, const Rational& num)
{
    os << num.p;
    if (num.q != 1) {
        os << "/" << num.q;
    }

    return os;
}
std::istream& operator>>(std::istream& is, Rational& r)
{
    int num = 0, den = 1;
    char buff = '/';

    is >> num;
    if (is.peek() == '/') {
        is >> buff >> den;
    }

    r = Rational(num, den);

    return is;
}