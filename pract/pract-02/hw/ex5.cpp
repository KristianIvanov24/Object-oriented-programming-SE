#include <iostream>
#include <cmath>
#include <algorithm>

/*
6. Реализирайте система за изчисления на полиноми със структурата Polynomial със следните член-данни:

коефициентите (най-много 20)
степента на полинома (Коефициентът на x^i се пази на позиция i в масива.)
Реализирайте следните функции:

Създава полином по подадени коефициенти и степен.
Пресмята стойността на полином в точка x.
Събира два полинома.
Изважда два полинома.
Умножава два полинома.
Извежда полином на стандартния изход (например 3.00x^2 + 2.00x^1 + 1.00x^0).
*/

const int MAX_DEG = 20;

struct Polynomial
{
    double coef[MAX_DEG]{};
    int n;
};

bool validDegree(int n)
{
    if (n >= MAX_DEG)
    {
        std::cout << "Max degree exceeded!" << std::endl;
        return false;
    }
    return true;
}

void readPolynomial(Polynomial &pl)
{
    int n;
    std::cin >> n;
    if (!validDegree(n))
    {
        return;
    }

    pl.n = n;
    for (int i = 0; i <= pl.n; i++)
    {
        std::cin >> pl.coef[i];
    }
}

double calc(const Polynomial &pl, double x)
{
    double res = 0;
    for (int i = 0; i <= pl.n; i++)
    {
        res += pl.coef[i] * pow(x, i);
    }
    return res;
}

void printPolynomial(const Polynomial &pl)
{
    for (int i = pl.n; i >= 0; i--)
    {
        std::cout << pl.coef[i] << "x^" << i;
        if (i != 0)
            std::cout << " + ";
    }
    std::cout << std::endl;
}

Polynomial operation(const Polynomial &pl1, const Polynomial &pl2, double (*op)(const double a, const double b))
{
    Polynomial pl;
    pl.n = std::max(pl1.n, pl2.n);

    for (int i = 0; i <= pl.n; i++)
    {
        double a = 0, b = 0;
        if (pl1.n >= i)
            a = pl1.coef[i];
        if (pl2.n >= i)
        {
            b = pl2.coef[i];
        }
        pl.coef[i] = op(a, b);
    }
    return pl;
}

Polynomial mult(const Polynomial &pl1, const Polynomial &pl2)
{
    Polynomial pl;
    pl.n = pl1.n + pl2.n;
    if (!validDegree(pl.n))
    {
        pl.n = 0;
        pl.coef[0] = 0;
        return pl;
    }

    for (int i = 0; i <= pl1.n; i++)
    {
        for (int j = 0; j <= pl2.n; j++)
        {
            pl.coef[i + j] += pl1.coef[i] * pl2.coef[j];
        }
    }
    return pl;
}

int main()
{
    Polynomial pl1, pl2;
    readPolynomial(pl1);
    readPolynomial(pl2);

    std::cout << calc(pl1, 1) << std::endl;

    Polynomial p = operation(pl1, pl2, [](const double a, const double b)
                             { return a + b; });
    Polynomial q = operation(pl1, pl2, [](const double a, const double b)
                             { return a - b; });
    Polynomial r = mult(pl1, pl2);

    printPolynomial(p);
    printPolynomial(q);
    printPolynomial(r);

    return 0;
}