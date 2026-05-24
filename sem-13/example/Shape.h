#pragma once
#include <vector>

class Shape
{
protected:
	struct Point
	{
        int x;
		int y;
		
        Point();
		Point(int x, int y);

		double distanceTo(const Point& other) const;
	};

	const Point& getPointAtIndex(size_t index) const;

private:
	std::vector<Point> points;

public:
	Shape(size_t pointsCount);
	virtual ~Shape() = default;

	void setPoint(size_t pointIndex, int x, int y);

	virtual double getArea() const = 0;             
	virtual double getPerimeter()  const = 0;              
	virtual bool containsPoint(int x, int y) const = 0;

};