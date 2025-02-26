//#include <iostream>
//#include <fstream>
//
//namespace CONSTANTS
//{
//	constexpr int VECTORS_MAX_SIZE = 50;
//}
//
//struct Vector
//{
//	int x = 0;
//	int y = 0;
//	int z = 0;
//};
//
//struct VectorSpace
//{
//	Vector vectors[CONSTANTS::VECTORS_MAX_SIZE]{};
//	size_t size = 0;
//};
//
//Vector makeVector(int x, int y, int z)
//{
//	return Vector{ x, y, z };
//}
//
//void addToVectorSpace(VectorSpace& vSpace, const Vector& v)
//{
//	if (vSpace.size >= CONSTANTS::VECTORS_MAX_SIZE)
//	{
//		return;
//	}
//
//	vSpace.vectors[vSpace.size++] = v;
//}
//
//void serializeVector(std::ofstream& ofs, const Vector& v)
//{
//	ofs << "<" << v.x << "," << v.y << "," << v.z << ">" << std::endl;
//}
//
//void serializeVector(const char* fileName, const Vector& v)
//{
//	if (!fileName)
//	{
//		return;
//	}
//
//	std::ofstream ofs(fileName);
//	if (!ofs.is_open())
//	{
//		return;
//	}
//
//	serializeVector(ofs, v);
//}
//
//void serializeVectorSpace(std::ofstream& ofs, const VectorSpace& vSpace)
//{
//	ofs << vSpace.size << std::endl;
//	for (int i = 0; i < vSpace.size; i++)
//	{
//		serializeVector(ofs, vSpace.vectors[i]);
//	}
//
//	ofs.close();
//}
//
//void serializeVectorSpace(const char* fileName, const VectorSpace& vSpace)
//{
//	if (!fileName)
//	{
//		return;
//	}
//
//	std::ofstream ofs(fileName);
//	if (!ofs.is_open())
//	{
//		return;
//	}
//
//	serializeVectorSpace(ofs, vSpace);
//}
//
//Vector deserializeVector(std::ifstream& ifs)
//{
//	int x, y, z;
//
//	ifs.ignore();
//	ifs >> x;
//
//	ifs.ignore();
//	ifs >> y;
//
//	ifs.ignore();
//	ifs >> z;
//
//	ifs.ignore();
//
//	return Vector{ x, y, z };
//}
//
//Vector deserializeVector(const char* fileName)
//{
//	if (!fileName)
//	{
//		return {};
//	}
//
//	std::ifstream ifs(fileName);
//	if (!ifs.is_open())
//	{
//		return {};
//	}
//
//	return deserializeVector(ifs);
//}
//
//VectorSpace deserializeVectorSpace(std::ifstream& ifs)
//{
//	VectorSpace vSpace;
//	ifs >> vSpace.size;
//	ifs.ignore();
//
//	for (int i = 0; i < vSpace.size; i++)
//	{
//		vSpace.vectors[i] = deserializeVector(ifs);
//		ifs.ignore();
//	}
//
//	ifs.close();
//	return vSpace;
//}
//
//VectorSpace deserializeVectorSpace(const char* fileName)
//{
//	if (!fileName)
//	{
//		return {};
//	}
//
//	std::ifstream ifs(fileName);
//	if (!ifs.is_open())
//	{
//		return {};
//	}
//
//	return deserializeVectorSpace(ifs);
//}
//
//void printVector(const Vector& v)
//{
//	std::cout << "<" << v.x << "," << v.y << "," << v.z << ">" << std::endl;
//}
//
//void printVectorSpace(const VectorSpace& vSpace)
//{
//	for (int i = 0; i < vSpace.size; i++)
//	{
//		printVector(vSpace.vectors[i]);
//	}
//}
//
//double lengthOf(const Vector& v)
//{
//	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
//}
//
//void sortVectorSpaceByCriteria(VectorSpace& space, bool (*criteria)(const Vector& lhs, const Vector& rhs))
//{
//	for (size_t i = 0; i < space.size - 1; i++)
//	{
//		size_t minIdx = i;
//		for (size_t j = i + 1; j < space.size; j++)
//		{
//			if (criteria(space.vectors[minIdx], space.vectors[j]))
//			{
//				minIdx = j;
//			}
//		}
//
//		if (minIdx != i)
//		{
//			std::swap(space.vectors[minIdx], space.vectors[i]);
//		}
//	}
//}
//
//bool ascLengthCriteria(const Vector& lhs, const Vector& rhs)
//{
//	return lengthOf(lhs) > lengthOf(rhs);
//}
//
//void sortVectorSpaceByLength(VectorSpace& space)
//{
//	sortVectorSpaceByCriteria(space, ascLengthCriteria);
//}
//
//bool ascLexographicCriteria(const Vector& lhs, const Vector& rhs)
//{
//	if (lhs.x != rhs.x)
//	{
//		return lhs.x > rhs.x;
//	}
//
//	if (lhs.y != rhs.y)
//	{
//		return lhs.y > rhs.y;
//	}
//
//	return lhs.z > rhs.z;
//}
//	
//void sortVectorSpaceLexographically(VectorSpace& space)
//{
//	sortVectorSpaceByCriteria(space, ascLexographicCriteria);
//}
//
//int dotProduct(const Vector& lhs, const Vector& rhs)
//{
//	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
//}
//
//Vector crossProduct(const Vector& lhs, const Vector& rhs)
//{
//
//	Vector cross;
//	cross.x = lhs.y * rhs.z - lhs.z * rhs.y;
//	cross.y = lhs.z * rhs.x - lhs.x * rhs.z;
//	cross.z = lhs.x * rhs.y - lhs.y * rhs.x;
//	
//	return cross;
//}
//
//bool areLinearDependent(const VectorSpace& space, size_t i, size_t j)
//{
//	if (i >= space.size || j >= space.size)
//	{
//		return false;
//	}
//
//	Vector cross = crossProduct(space.vectors[i], space.vectors[j]);
//
//	return (cross.x == 0 && cross.y == 0 && cross.z == 0);
//}
//
//void printBases(const VectorSpace& space)
//{
//	for (size_t i = 0; i < space.size; i++)
//	{
//		for (size_t j = i + 1; j < space.size; j++)
//		{
//			for (size_t k = j + 1; k < space.size; k++)
//			{
//				if (!areLinearDependent(space, i, j)
//					&& !areLinearDependent(space, i, k)
//					&& !areLinearDependent(space, j, k))
//				{
//					std::cout << "-------------" << std::endl;
//					printVector(space.vectors[i]);
//					printVector(space.vectors[j]);
//					printVector(space.vectors[k]);
//					std::cout << "-------------" << std::endl;
//				}
//			}
//		}
//	}
//}
//
//int main()
//{
//
//	const char* fileName = "vSpace.txt";
//	VectorSpace vSpace = {
//		{
//			{4, 2, 3},
//			{1, 2, 3},
//			{1, 2, 3},
//		},
//
//		3
//	};
//
//	serializeVectorSpace(fileName, vSpace);
//
//	VectorSpace vSpace2 = deserializeVectorSpace(fileName);
//	printVectorSpace(vSpace2);
//
//	sortVectorSpaceByLength(vSpace2);
//	printVectorSpace(vSpace2);
//
//	sortVectorSpaceLexographically(vSpace2);
//	printVectorSpace(vSpace2);
//
//	printBases(vSpace2);
//
//	return 0;
//}