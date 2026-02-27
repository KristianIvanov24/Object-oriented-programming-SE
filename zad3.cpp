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

struct Triangle
{
	Point pointA;
	Point pointB;
	Point pointC;
};

void enterTriangle(Triangle& delta)
{
	enterPoint(delta.pointA);
	enterPoint(delta.pointB);
	enterPoint(delta.pointC);
}

void printTriangle(const Triangle& delta)
{
	printPointCoordinates(delta.pointA);
	std::cout << " , ";
	printPointCoordinates(delta.pointB);
	std::cout << " , ";
	printPointCoordinates(delta.pointC);
	std::cout << " , ";
}

double perimeter(const Triangle& delta)
{
	double side1 = distance(delta.pointA, delta.pointB);
	double side2 = distance(delta.pointA, delta.pointC);
	double side3 = distance(delta.pointB, delta.pointC);
	return side1 + side2 + side3;
}

double Area(const Triangle& delta)
{
	double side1 = distance(delta.pointA, delta.pointB);
	double side2 = distance(delta.pointA, delta.pointC);
	double side3 = distance(delta.pointB, delta.pointC);
	double P = perimeter(delta);
	double p = P / 2.0;
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

enum class TriangleType
{
	Ravnostranen,
	Ravnobedren,
	Raznostranen,
	Nevaliden
};

TriangleType getTriangleType(const Triangle& delta)
{
	double side1 = distance(delta.pointA, delta.pointB);
	double side2 = distance(delta.pointA, delta.pointC);
	double side3 = distance(delta.pointB, delta.pointC);
	if ((side3 >= side1 + side2) || (side2 >= side1 + side3) || (side1 >= side2 + side3))
		return TriangleType::Nevaliden;

	if ((side1 == side2) && (side2 == side3))
	{
		return TriangleType::Ravnostranen;
	}
	else if ((side1 == side2) || (side2 == side3) || (side1 == side3))
	{
		return TriangleType::Ravnobedren;
	}
	else
	{
		return TriangleType::Raznostranen;
	}
}
void printTriangleType(const TriangleType type)
{
	switch (type)
	{
	case TriangleType::Ravnostranen: std::cout << "Ravnostranen"; break;
	case TriangleType::Ravnobedren: std::cout << "Ravnobedren"; break;
	case TriangleType::Raznostranen: std::cout << "Raznostranen"; break;
	default: std::cout << "nevaliden";
	}
}
int main()
{
	Triangle delta;
	enterTriangle(delta);
	TriangleType type = getTriangleType(delta);
	printTriangleType(type);
}