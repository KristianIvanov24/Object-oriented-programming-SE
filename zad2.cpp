#include <iostream>

struct Point
{
	double x;
	double y;
};

void enterPoint(Point& point)
{
	std::cin >> point.x >> point.y;
}

void printPointCoordinates(const Point& point)
{
	std::cout << "(" << point.x << ";" << point.y << ")";
}

double distance(const Point& p1, const Point& p2)
{
	double res1 = (p1.x - p2.x) * (p1.x - p2.x);
	double res2 = (p1.y - p2.y) * (p1.y - p2.y);
	return sqrt(res1 + res2);
}

int main()
{
	std::cout << "Hello World!\n";
}