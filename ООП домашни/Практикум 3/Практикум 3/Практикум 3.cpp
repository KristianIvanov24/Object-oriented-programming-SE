#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable:4996)

namespace constants
{
    //задача 2
    const size_t MAX_CAR_OWNER_NAME_SIZE = 24;
    const size_t MAX_FINE_COUNT = 20;

    //задача 3
    const char CIPHER_FILE_NAME[] = "cyhper.bin";
    const char KEY_FILE_NAME[] = "key.bin";

    //задача 4
    const size_t NODE_USER_DATA = 504;
}

enum class CarBrand
{
    MERCEDES,
    AUDI,
    BMW,
    TOYOTA,
    HONDA
};

struct Car
{
    CarBrand brand;
    char ownerName[constants::MAX_CAR_OWNER_NAME_SIZE];
    double maxSpeed;
    unsigned fines[constants::MAX_FINE_COUNT];
    size_t fineCount;
};

unsigned calculateTotalFineSum(const Car& car)
{
    unsigned sum = 0;
    for (size_t i = 0; i < car.fineCount; i++)
    {
        sum += car.fines[i];
    }

    return sum;
}

void addFine(Car& car, const int newFine)
{
    if (car.fineCount >= constants::MAX_FINE_COUNT)
        return;

    car.fines[car.fineCount++] = newFine;
}

void printCarBrand(const CarBrand brand)
{
    switch (brand)
    {
        case CarBrand::AUDI:
            std::cout << "Audi";
            break;
        case CarBrand::BMW:
            std::cout << "BMW";
            break;
        case CarBrand::MERCEDES:
            std::cout << "Mercedes";
            break;
        case CarBrand::TOYOTA:
            std::cout << "Toyota";
            break;
        case CarBrand::HONDA:
            std::cout << "Honda";
            break;
    }
}

void printFines(const unsigned fines[], const size_t count)
{
    for (size_t current = 0; current < count; current++)
    {
        std::cout << fines[current] << " ";
    }
}

void printCarInfo(const Car& car)
{
    std::cout << "Car brand: ";
    printCarBrand(car.brand);
    std::cout << "\nOnwer: " << car.ownerName << '\n';
    std::cout << "Max speed: " << car.maxSpeed << '\n';
    std::cout << "Fines: ";
    printFines(car.fines, car.fineCount);
}

void serialiseCar(std::ofstream& ofs, const Car& car)
{
    if (!ofs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    ofs.write((const char*)&car, sizeof(Car));
}

Car deserialiseCar(std::ifstream& ifs)
{
    if (!ifs.is_open())
    {
        std::cout << "Error when opening file\n";
        return {};
    }

    Car car;
    ifs.read((char*)&car, sizeof(Car));

    return car;
}

void serialiseCarArray(std::ofstream& ofs, const Car cars[], const size_t size)
{
    if (!ofs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    ofs.write((const char*)&size, sizeof(size));
    ofs.write((const char*)cars, sizeof(Car) * size);
}

Car* deserialiseCarArray(std::ifstream& ifs, size_t& size)
{
    if (!ifs.is_open())
    {
        std::cout << "Error when opening file\n";
        return nullptr;
    }

    ifs.read((char*)&size, sizeof(size));
    std::cout << size << '\n';

    Car* cars = new Car[size];
    for (size_t current = 0; current < size; current++)
    {
        cars[current] = deserialiseCar(ifs);
    }

    return cars;
}

//задача 3
size_t getFileSize(std::ifstream& ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    ifs.seekg(currentPos);

    return fileSize;
}

unsigned* readCypher(std::ifstream& ifs, size_t& numberCount)
{
    if (!ifs.is_open())
    {
        std::cout << "Error when opening file\n";
        return nullptr;
    }

    numberCount = getFileSize(ifs) / sizeof(unsigned);

    unsigned* cypher = new unsigned[numberCount];
    ifs.read((char*)cypher, numberCount * sizeof(unsigned));

    return cypher;
}

void saveCypher(std::ofstream& ofs, const unsigned* cypher, const size_t numberCount)
{
    if (!cypher)
        return;

    if (!ofs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    ofs.write((const char*)cypher, numberCount * sizeof(unsigned));
}

uint8_t readKey(std::ifstream& ifs)
{
    if (!ifs.is_open())
    {
        std::cout << "Error when opening file\n";
        return 0;
    }

    uint8_t key;
    ifs.read((char*)&key, sizeof(uint8_t));

    return key;
}

void saveKey(std::ofstream& ofs, const uint8_t key)
{
    if (!ofs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    ofs.write((const char*)&key, sizeof(uint8_t));
}

void printDecyphered(const unsigned* numbers, const size_t numberCount, const uint8_t key)
{
    if (!numbers)
        return;

    for (size_t current = 0; current < numberCount; current++)
    {
        std::cout << numbers[current] + key << " ";
    }
}

void decypher()
{
    std::ifstream cypherIfs(constants::CIPHER_FILE_NAME, std::ios::binary);

    if (!cypherIfs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    size_t numberCount;
    unsigned* cypher = readCypher(cypherIfs, numberCount);
    
    cypherIfs.close();

    std::ifstream keyIfs(constants::KEY_FILE_NAME, std::ios::binary);
    uint8_t key = readKey(keyIfs);

    if (!keyIfs.is_open())
    {
        std::cout << "Error when opening file\n";
        return;
    }

    keyIfs.close();

    printDecyphered(cypher, numberCount, key);

    delete[] cypher;
    cypher = nullptr;
}

//задача 4
struct Node
{
    uint64_t next;
    char userData[constants::NODE_USER_DATA];
};

void tagCensored(const Node* nodes, bool* used, const size_t nodeCount)
{
    Node currentNode = nodes[0];
    used[0] = true;

    while (currentNode.next != 0)
    {
        if (currentNode.next >= nodeCount)
            break;

        used[currentNode.next] = true;
        currentNode = nodes[currentNode.next];
    }
}

void saveCensoredNodeList(std::ofstream& ofs, const Node* nodes,
    const bool* used, const size_t nodeCount)
{
    Node censoredNode = { 0, "censored" };

    for (size_t current = 0; current < nodeCount; current++)
    {
        if (used[current])
            ofs.write((const char*)&nodes[current], sizeof(Node));
        else
            ofs.write((const char*)&censoredNode, sizeof(Node));
    }
}

void censorUnused(const char* fileName)
{
    if (!fileName)
        return;

    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs.is_open())
    {
        std::cout << "Error when opening file";
        return;
    }

    size_t nodeCount = getFileSize(ifs) / sizeof(Node);
    Node* nodes = new Node[nodeCount];
    bool* used = new bool[nodeCount]{0};

    ifs.read((char*)nodes, nodeCount * sizeof(Node));
    ifs.close();

    tagCensored(nodes, used, nodeCount);

    std::ofstream ofs(fileName);
    if (!ofs.is_open())
    {
        std::cout << "Error when opening file";
        delete[] used;
        delete[] nodes;
        used = nullptr;
        nodes = nullptr;
        return;
    }

    saveCensoredNodeList(ofs, nodes, used, nodeCount);

    delete[] used;
    delete[] nodes;
    used = nullptr;
    nodes = nullptr;
    ofs.close();
}

int main()
{

    return 0;
}