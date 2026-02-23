#include <iostream>

/*
2. Създайте структура, която представлява точка в двумерното пространство. Реализирайте следните функции:

Четене от стандартния вход.
Принтиране на стандартния изход.
Разстояние между две точки.
*/

struct Point
{
    double x;
    double y;
};

void readPoint(Point &p)
{
    std::cin >> p.x >> p.y;
}

void printPoint(const Point &p)
{
    std::cout << "(" << p.x << ", " << p.y << ")";
}

double dist(const Point &p1, const Point &p2)
{
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;

    return sqrt(x * x + y * y);
}

int main()
{
    Point a, b;
    readPoint(a);
    readPoint(b);

    std::cout << dist(a, b) << std::endl;
    printPoint(a);

    return 0;
}