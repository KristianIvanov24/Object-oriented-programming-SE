#include "SmartHome.h"

void SmartHome::copyFrom(const SmartHome& other)
{
    size = other.size;
    capacity = other.capacity;

    data = new Device * [capacity] {nullptr};
    for (size_t i = 0; i < size; i++)
        data[i] = other.data[i]->clone();
}

void SmartHome::free()
{
    for (size_t i = 0; i < capacity; i++)
    {
        delete data[i];
    }

    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

void SmartHome::moveFrom(SmartHome&& other)
{
    size = other.size;
    capacity = other.capacity;
    data = other.data;
    other.data = nullptr;
}

void SmartHome::resize(size_t newCapacity)
{
    Device** temp = new Device*[newCapacity]{nullptr};

    for (size_t i = 0; i < size; i++)
    {
        temp[i] = data[i];
    }

    delete[] data;
    capacity = newCapacity;
    data = temp;
}

SmartHome::SmartHome()
{
    capacity = INITIAL_CAPACITY;
    size = 0;
    data = new Device * [capacity] { nullptr };
}

SmartHome::SmartHome(const SmartHome& other)
{
    copyFrom(other);
}

SmartHome::SmartHome(SmartHome&& other)
{
    moveFrom(std::move(other));
}

SmartHome* SmartHome::operator=(const SmartHome& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return this;
}

SmartHome* SmartHome::operator=(SmartHome&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return this;
}

SmartHome::~SmartHome()
{
    free();
}

void SmartHome::addDevice(Device* toAdd)
{
    if (!toAdd)
        return;

    if (size == capacity)
        resize(capacity * 2);

    data[size++] = toAdd;
}

void SmartHome::addDevice(const Device& toAdd)
{
    addDevice(toAdd.clone());
}

void SmartHome::removeDevice(size_t index)
{
    if (index >= size)
    {
        return;
    }
     
    std::swap(data[index], data[size - 1]);
    delete data[size - 1];
    data[size - 1] = nullptr;
    --size;
}

void SmartHome::printAllDevices() const
{
    for (size_t i = 0; i < size; i++)
    {
        data[i]->printDetails();

        if (i != size - 1)
        {
            std::cout << "-------------------------" << std::endl;
        }
    }
}

void SmartHome::turnOffAt(size_t index)
{
    if (index >= size)
    {
        return;
    }

    data[index]->turnOff();
}

void SmartHome::turnOnAt(size_t index)
{
    if (index >= size)
    {
        return;
    }

    data[index]->turnOn();
}

double SmartHome::findAveragePriceByManufacturer(const MyString& manufacturer) const
{
    int counter = 0;
    double total = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (data[i]->getManufactuter() == manufacturer)
        {
            counter++;
            total += data[i]->getPrice();
        }
    }

    if (counter == 0)
    {
        return 0;
    }

    return total / counter;
}
