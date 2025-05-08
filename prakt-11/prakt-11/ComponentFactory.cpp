#include "ComponentFactory.h"

Component* ComponentFactory::create_Component()
{
    std::cout << "a - cpu, b - memory";
    char choice;
    std::cin >> choice;

    switch (choice)
    {
    case 'a':
        return createCPU();
    case 'b':
        return createMemory();
    default:
        return nullptr;
    }
}

CPU* ComponentFactory::createCPU()
{
    char* lable;
    unsigned short cores, clockSpeed;
    std::cin >> lable >> cores >> clockSpeed;

    return new CPU(lable, cores, clockSpeed);
}

Memory* ComponentFactory::createMemory()
{
    char* lable;
    unsigned short capacity;
    std::cin >> lable >> capacity;

    return new Memory(lable, capacity);
}
