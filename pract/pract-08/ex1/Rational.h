#pragma once
class Rational
{
public:

    int p;
    int q;

    int NOD(int a, int b) const;
    void rationalize();
    void addSubHelper(const Rational& other, int (op)(int lhs, int rhs));

public:

    Rational();
    Rational(int n);
    Rational(int num, int den);

    int getP() const;
    int getQ() const;

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator/=(const Rational& other);
    Rational& operator*=(const Rational& other);

    Rational operator-() const;

    operator double() const;

    operator bool() const;

    bool operator==(const Rational& other) const;
    std::strong_ordering operator<=>(const Rational& other) const;

    Rational& operator++();
    Rational operator++(int);

    Rational& operator--();
    Rational operator--(int);

};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& os, const Rational& num);
std::istream& operator>>(std::istream& is, Rational& num);

