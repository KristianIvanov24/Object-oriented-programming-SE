#include <iostream>
const unsigned short SIDES = 3;
enum class TriangleType
{
	equilateral, //равностранен
	isosceles, //равнобедрен
	scalene //разностранен
};
class Triangle
{
public:
	double sideA, sideB, sideC;
};
bool areSidesValid(const Triangle tr)
{
	if (tr.sideA <= 0 || tr.sideB <= 0 || tr.sideC <= 0)
		return false;

	double sides[SIDES] = { tr.sideA, tr.sideB,tr.sideC };

	for (int i = 0; i < SIDES; ++i)
		if (sides[i % SIDES] + sides[(i + 1) % SIDES] <= sides[(i + 2) % SIDES])
			return false;

	return true;
}
void inputTriangle(Triangle& tr)
{
	std::cin >> tr.sideA >> tr.sideB >> tr.sideC;

	while (!areSidesValid(tr))
	{
		std::cout << "Invalid sides. Enter new sides: ";
		std::cin >> tr.sideA >> tr.sideB >> tr.sideC;
	}
}
void printTriangle(const Triangle tr)
{
	std::cout << "Side A = " << tr.sideA << "\nSideB = " << tr.sideB << "\nSideC = " << tr.sideC << std::endl;
}
double perimeter(const Triangle tr)
{
	return tr.sideA + tr.sideB + tr.sideC;
}
double area(const Triangle tr)
{
	double halfPerimeter = perimeter(tr) / 2;
	double area = halfPerimeter;

	double sides[SIDES] = { tr.sideA, tr.sideB,tr.sideC };
	for (int i = 0; i < SIDES; ++i)
		area *= halfPerimeter - sides[i];

	return sqrt(area);
}
TriangleType typeOfTriang(const Triangle tr)
{
	unsigned short howManySidesAreEqual = 0;
	double sides[SIDES] = { tr.sideA, tr.sideB,tr.sideC };

	for (int i = 0; i < SIDES; ++i)
		if (sides[i] == sides[(i+1) % SIDES])
			howManySidesAreEqual++;

	switch (howManySidesAreEqual)
	{
	case 0:return TriangleType::scalene;
	case 3:return TriangleType::equilateral;
	default:return TriangleType::isosceles;
	}
}
int main()
{
	Triangle tr;

	inputTriangle(tr);
	printTriangle(tr);

	std::cout << "Perimeter: " << perimeter(tr) << std::endl;
	std::cout << "Area: " << area(tr) << std::endl;
	std::cout << "Type of triangle: " << (int)typeOfTriang(tr) << std::endl;
}
