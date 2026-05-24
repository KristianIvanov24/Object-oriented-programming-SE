#include "Triangle.h"

#include <limits>
#include <cmath>

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setPoint(2, x3, y3);
}
double Triangle::getArea() const
{
	const Shape::Point& p1 = getPointAtIndex(0);
	const Shape::Point& p2 = getPointAtIndex(1);
	const Shape::Point& p3 = getPointAtIndex(2);

    double semiPerimeter = getPerimeter() / 2.0;
	return sqrt(semiPerimeter * (semiPerimeter - p1.distanceTo(p2)) * 
                (semiPerimeter - p1.distanceTo(p3)) * (semiPerimeter - p2.distanceTo(p3)));
}

double Triangle::getPerimeter() const
{
    const Shape::Point& p1 = getPointAtIndex(0);
	const Shape::Point& p2 = getPointAtIndex(1);
	const Shape::Point& p3 = getPointAtIndex(2);

    return p1.distanceTo(p2) + p1.distanceTo(p3) + p2.distanceTo(p3);
}              

bool Triangle::containsPoint(int x, int y) const
{
	Shape::Point p(x, y);
	Triangle t1(getPointAtIndex(0).x, getPointAtIndex(0).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
	Triangle t2(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
	Triangle t3(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(0).x, getPointAtIndex(0).y, p.x, p.y);

	return std::abs(t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}