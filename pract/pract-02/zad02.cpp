#include <iostream>
class Point
{
public:
	double x, y;
};
double distBetwPoints(const Point point1, const Point point2)
{
	double xDist = point2.x - point1.x;
	double yDist = point2.y - point1.y;

	xDist *= xDist;
	yDist *= yDist;

	return sqrt(xDist + yDist);
}
void inputPoint(Point& point)
{
	std::cout << "Input x coord first then y coord: " << std::endl;

	std::cin >> point.x;
	std::cin >> point.y;
}
void printPoint(Point point)
{
	std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
}
int main()
{
	Point p1 = { 0,0 };
	Point p2;
	inputPoint(p2);

	printPoint(p2);

	std::cout << distBetwPoints(p1, p2);
}
