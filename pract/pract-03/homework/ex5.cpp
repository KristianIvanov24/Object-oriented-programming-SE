#include <iostream>
#include <fstream>

const size_t MAX_VECTORS = 50;

struct Vector
{
    int x;
    int y;
    int z;
};

struct VectorSpace
{
    size_t vectorCount;
    Vector vectors[MAX_VECTORS];
};

Vector makeVector(int x, int y, int z)
{
    return {x, y, z};
}

void addToVectorSpace(VectorSpace &vectorSpace, const Vector &vector)
{
    if (vectorSpace.vectorCount == MAX_VECTORS)
    {
        std::cout << "Vector limit exceeded!" << std::endl;
        return;
    }

    vectorSpace.vectors[vectorSpace.vectorCount++] = vector;
}

void serializeVector(std::ofstream &ofs, const Vector &vector)
{
    ofs << "<" << vector.x << ", " << vector.y << ", " << vector.z << "> ";
}

Vector deserializeVector(std::ifstream &ifs)
{
    Vector vector;
    char c;
    std::cin >> c >> vector.x >> c >> vector.y >> c >> vector.z;

    return vector;
}

void serializeVectorSpace(const char *fileName, const VectorSpace &vectorSpace)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    file << vectorSpace.vectorCount << " ";
    for (size_t i = 0; i < vectorSpace.vectorCount; i++)
    {
        serializeVector(file, vectorSpace.vectors[i]);
    }
}

VectorSpace deserializeVectorSpace(const char *fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opeing file!" << std::endl;
        return {0};
    }

    VectorSpace vs;
    file >> vs.vectorCount;
    for (size_t i = 0; i < vs.vectorCount; i++)
    {
        vs.vectors[i] = deserializeVector(file);
    }
}