#include <iostream>
#include <fstream>

namespace constants
{
    const size_t MAX_SIZE_VECTORS = 50;
}

struct Vector
{
    double x;
    double y;
    double z;
};

struct VectorSpace 
{
	Vector vectors[constants::MAX_SIZE_VECTORS];
	size_t size;
};

Vector makeVector(double x, double y, double z)
{
    return { x, y, z };
}

void addToVectorSpace(VectorSpace& vectorSpace, const Vector& vector)
{
    if (vectorSpace.size < constants::MAX_SIZE_VECTORS)
    {
        vectorSpace.vectors[vectorSpace.size] = vector;
        vectorSpace.size++;
    }
    else 
    {
        std::cout << "VectorSpace is full" << std::endl;
    }
}

void serializeVector(std::ofstream& file, const Vector& vector)
{
    file << " < " << vector.x << ", " << vector.y << ", " << vector.z << " > ";
}

Vector deserializeVector(std::ifstream& file)
{
    double x, y, z;
    char ch;
    file >> ch;
    file >> x;
    file >> ch;
    file >> y;
    file >> ch;
    file >> z;
    file >> ch;

    return { x, y, z };
}

void serializeVectorSpace(const char* fileName, const VectorSpace& vectorSpace)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "File cannot be opened" << std::endl;
        return;
    }


    file << vectorSpace.size;
    for (int i = 0; i < vectorSpace.size; i++)
    {
        serializeVector(file, vectorSpace.vectors[i]);
    }
    file.close();
}

VectorSpace deserializeVectorSpace(const char* fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "File cannot be opened" << std::endl;
        return { {}, 0 };
    }

    VectorSpace vectorSpace;
    file >> vectorSpace.size;
    if(vectorSpace.size > constants::MAX_SIZE_VECTORS) 
    {
		vectorSpace.size = constants::MAX_SIZE_VECTORS;
	}

    for (int i = 0; i < vectorSpace.size; i++)
    {
        vectorSpace.vectors[i] = deserializeVector(file);
    }

    file.close();
	return vectorSpace;
}

int main()
{
    VectorSpace vs = { {}, 0 };

    addToVectorSpace(vs, makeVector(1, 2, 3));
    addToVectorSpace(vs, makeVector(4, 5, 6));
    addToVectorSpace(vs, makeVector(7, 8, 9));

    serializeVectorSpace("vectors.txt", vs);

    VectorSpace vs2 = deserializeVectorSpace("vectors.txt");

    for (int i = 0; i < vs2.size; i++)
    {
        std::cout << vs2.vectors[i].x << " "
            << vs2.vectors[i].y << " "
            << vs2.vectors[i].z << std::endl;
    }
    return 0;
}