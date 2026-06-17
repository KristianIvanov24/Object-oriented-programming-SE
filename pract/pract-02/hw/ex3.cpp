#include <iostream>

/*
3. Създайте структура, която представлява фигурата триъгълник. Реализирайте следните функции:

Четене от стандартния вход.
Принтиране на стандартния изход.
Пресмятане на обиколка.
Пресмятане на лице.
Връщне на типа на триъгълника спрямо страните му (равнобедрен, равностранен, разностранен).

*/

struct Triangle
{
    double a;
    double b;
    double c;
};

void readTriangle(Triangle &tr)
{
    std::cin >> tr.a >> tr.b >> tr.c;
}

void printTriangle(const Triangle &tr)
{
    std::cout << "a = " << tr.a << ", b = " << tr.b << " c = " << tr.c << std::endl;
}

double perimeter(const Triangle &tr)
{
    return tr.a + tr.b + tr.c;
}

double area(const Triangle &tr)
{
    double p = perimeter(tr) / 2;
    return sqrt(p * (p - tr.a) * (p - tr.b) * (p - tr.c));
}

std::string type(const Triangle &tr)
{
    if (tr.a == tr.b && tr.a == tr.c)
    {
        return "equilateral";
    }
    else if (tr.a == tr.b || tr.a == tr.c || tr.b == tr.c)
    {
        return "isosceles";
    }
    else
    {
        return "scalene";
    }
}

int main()
{
    Triangle tr;
    readTriangle(tr);
    printTriangle(tr);

    std::cout << "Perimeter: " << perimeter(tr) << "\nArea: " << area(tr) << "\nType: " << type(tr) << std::endl;

    return 0;
}