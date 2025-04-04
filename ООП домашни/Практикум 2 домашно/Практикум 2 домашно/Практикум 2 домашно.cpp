#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable : 4996)

namespace constants
{
    //задача 2
    const size_t MAX_NUMBER_COUNT = 20;
    const char EVEN_FILE[] = "even.txt";
    const char ODD_FILE[] = "odd.txt";

    //задача 3
    const size_t MAX_VECTOR_COUNT = 50;
    const size_t BUFF_SIZE = 1024;
    const size_t TOTAL_COORDINATES_POSITIONS_COUNT = 6;

    //задача 4
    const size_t MAX_DEVICE_NAME_SIZE = 32;
    const size_t MAX_SUPPLIER_NAME_SIZE = 32;
    const size_t MAX_OWNER_NAME_SIZE = 32;
    const size_t MAX_DEVICES_IN_WAREHOUSE = 100;
}

//задача 1
void transferNumbersFromFiles(const char* inputFile, const char* outputFile)
{
    if (!inputFile || !outputFile)
    {
        std::cout << "Error";
        return;
    }
    int firstNum, secondNum;

    std::ifstream ifs(inputFile);
    if (!ifs.is_open())
    {
        std::cout << "Error";
        return;
    }

    ifs >> firstNum >> secondNum;
    ifs.close();


    std::ofstream ofs(outputFile);
    if (!ofs.is_open())
    {
        std::cout << "Error";
        return;
    }

    ofs << firstNum + secondNum << " " << firstNum * secondNum;
    ofs.close();
}

//задача 2
bool isEven(const int num)
{
    return (num % 2 == 0);
}

void splitEvenAndOddNumbers(const char* fileName)
{
    if (!fileName)
    {
        std::cout << "Error";
        return;
    }

    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        std::cout << "Error";
        return;
    }

    std::ofstream even(constants::EVEN_FILE);
    std::ofstream odd(constants::ODD_FILE);

    if (!even.is_open() || !odd.is_open())
    {
        std::cout << "Error";
        return;
    }

    size_t numberCounter = 0;
    int currentNum;

    while (!inputFile.eof())
    {
        inputFile >> currentNum;
        numberCounter++;

        if(isEven(currentNum))
        { 
            even << currentNum << " ";
        }
        else 
        {
            odd << currentNum << " ";
        }

        if (numberCounter >= constants::MAX_NUMBER_COUNT)
        {
            break;
        }
    }

    inputFile.close();
    even.close();
    odd.close();
}

//задача 3
namespace VectorOperations
{
    struct Vector
    {
        int x;
        int y;
        int z;
    };

    struct VectorSpace
    {
        Vector vectors[constants::MAX_VECTOR_COUNT];
        size_t currentVectorCount;
    };

    Vector makeVector(int x, int y, int z)
    {
        return { x, y, z };
    }

    void addToVectorSpace(VectorSpace& vectorSpace, const Vector& vector)
    {
        if (vectorSpace.currentVectorCount >= constants::MAX_VECTOR_COUNT)
        {
            std::cout << "Cannot add a new vector";
            return;
        }

        vectorSpace.vectors[vectorSpace.currentVectorCount] = vector;
        vectorSpace.currentVectorCount++;
    }

    void serializeVector(std::ofstream& ofs, const Vector& vector)
    {
        ofs << "<" << vector.x << ", " << vector.y << ", " << vector.z << ">";
    }

    void findNumberPositionsInLine(const char buff[], size_t numberPositions[])
    {
        size_t end = strlen(buff);
        numberPositions[0] = 1;
        numberPositions[constants::TOTAL_COORDINATES_POSITIONS_COUNT - 1] = end - 1;
        size_t ptr = 1;

        size_t checkedNumbers = 1;


        for (size_t current = 1; current < end; current++)
        {
            if (buff[current] == ',')
            {
                numberPositions[ptr++] = current;
                current += 2;
                numberPositions[ptr++] = current;

                checkedNumbers++;
            }

            if (checkedNumbers >= constants::TOTAL_COORDINATES_POSITIONS_COUNT / 2)
            {
                break;
            }
        }
    }

    unsigned charToDigit(const char symbol)
    {
        return symbol - '0';
    }

    int takeNumberFromStringByPositions(const char* buff, const size_t firstPos, const size_t secondPos)
    {
        if (!buff)
        {
            return 0;
        }

        bool isNegative = (buff[firstPos] == '-');
        int result = 0;

        for (size_t current = firstPos + isNegative; current < secondPos; current++)
        {
            result *= 10;
            result += charToDigit(buff[current]);
        }

        return (isNegative ? -result : result);
    }

    Vector deserializeVector(std::ifstream& ifs, const bool returnPosition)
    {
        size_t currentPos = ifs.tellg();

        int x, y, z;
        char buff[constants::BUFF_SIZE];
        ifs.getline(buff, constants::BUFF_SIZE);

        size_t numberPositions[constants::TOTAL_COORDINATES_POSITIONS_COUNT];
        findNumberPositionsInLine(buff, numberPositions);

        x = takeNumberFromStringByPositions(buff, numberPositions[0], numberPositions[1]);
        y = takeNumberFromStringByPositions(buff, numberPositions[2], numberPositions[3]);
        z = takeNumberFromStringByPositions(buff, numberPositions[4], numberPositions[5]);

        if(returnPosition)
            ifs.seekg(currentPos);

        return makeVector(x, y, z);
    }

    void serializeVectorSpace(const char* fileName, const VectorSpace& vectorSpace)
    {
        if (!fileName)
        {
            return;
        }

        std::ofstream ofs(fileName);
        if (!ofs.is_open())
        {
            return;
        }

        size_t end = vectorSpace.currentVectorCount;
        for (size_t current = 0; current < end; current++)
        {
            serializeVector(ofs, vectorSpace.vectors[current]);
        }

        ofs.close();
    }

    VectorSpace deserializeVectorSpace(const char* fileName)
    {
        if (!fileName)
        {
            Vector v = { 0, 0, 0 };
            return { v, 1 };
        }

        std::ifstream ifs(fileName);
        if (ifs.is_open())
        {
            Vector v = { 0, 0, 0 };
            return { v, 1 };
        }

        VectorSpace vectorSpace;
        size_t vectorCount = 0;

        while (!ifs.eof())
        {
            vectorSpace.vectors[vectorCount++] = deserializeVector(ifs, false);
        }

        vectorSpace.currentVectorCount = vectorCount;

        ifs.close();
        return vectorSpace;
    }
}

//задача 4
namespace DeviceOperations
{
    enum class DeviceType
    {
        TV,
        SMARTPHONE,
        LAPTOP,
        PC,
        CAMERA
    };

    struct Device
    {
        double price;
        unsigned available;
        char name[constants::MAX_DEVICE_NAME_SIZE + 1];
        char supplier[constants::MAX_SUPPLIER_NAME_SIZE + 1];
        DeviceType deviceType;
    };

    Device createDevice(const char name[], const unsigned available, const double price,
        const char supplier[], DeviceType deviceType)
    {
        Device device;
        strcpy(device.name, name);
        strcpy(device.supplier, supplier);
        device.available = available;
        device.price = price;
        device.deviceType = deviceType;

        return device;
    }
}

namespace WarehouseOperations
{
    using namespace DeviceOperations;

    struct Warehouse 
    {
        Device devices[constants::MAX_DEVICES_IN_WAREHOUSE];
        size_t currentDeviceCount;
        char owner[constants::MAX_OWNER_NAME_SIZE + 1];
    };

    Warehouse createWarehouse(const char owner[])
    {
        Warehouse warehouse;
        strcpy(warehouse.owner, owner);
        warehouse.currentDeviceCount = 0;


    }

    void addDeviceToWarehouse(Warehouse warehouse, const Device device)
    {
        if (warehouse.currentDeviceCount >= constants::MAX_DEVICES_IN_WAREHOUSE)
        {
            std::cout << "Warehouse capacity reached";
            return;
        }

        warehouse.devices[warehouse.currentDeviceCount] = device;
        warehouse.currentDeviceCount++;
    }
}

int main()
{
    std::ifstream ifs("input.txt");
    VectorOperations::Vector v = VectorOperations::deserializeVector(ifs, true);
    std::cout << v.x << " " << v.y << " " << v.z;

    return 0;
}
