#include "Shape.h"

#include <stdexcept>
#include <cmath>

Shape::Point::Point()
    : x(0), y(0)
{

}

Shape::Point::Point(int x, int y)
    : x(x), y(y)
{

}

double Shape::Point::distanceTo(const Point& other) const
{
	int dx = x - other.x;
	int dy = y - other.y;

    return sqrt(dx*dx + dy*dy);
}

const Point& Shape::getPointAtIndex(size_t index) const
{
	if (index >= points.size())
		throw std::invalid_argument("Invalid point index!");

	return points[index];
}

Shape::Shape(size_t pointsCount) : points(pointsCount)
{
    
}

void Shape::setPoint(size_t pointIndex, int x, int y)
{
	if (pointIndex >= points.size())
		throw std::invalid_argument("Invalid point index!");

	points[pointIndex] = Point(x, y);
}

