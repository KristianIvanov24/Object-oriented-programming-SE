#include "Configuration.h"

double Configuration::price() const
{
    double sum;
    for (size_t i = 0; i < size; i++)
        sum += components[i]->price();

    return sum;
}

const Component& Configuration::operator[](size_t index) const
{
    return *components[index];
}

void Configuration::moveFrom(Configuration&& other) noexcept
{
    components = other.components;
    size = other.size;
    capacity = other.capacity;
    other.components = nullptr;
}

void Configuration::copyFrom(const Configuration& other)
{
    capacity = other.capacity;
    size = other.size;
    components = new Component * [capacity] {nullptr};
    for (size_t i = 0; i < size; i++)
    {
        components[i] = other.components[i]->clone();
    }
}

void Configuration::free()
{
    delete[] components;
}

void Configuration::resize()
{
    Component** temp = new Component * [capacity * 2];
    for (size_t i = 0; i < size; i++)
        temp[i] = components[i];

    delete[] components;
    components = temp;
    temp = nullptr;
}

Configuration::Configuration()
{
    capacity = 16;
    components = new Component * [capacity] {nullptr};
    size = 0;
}

Configuration::Configuration(const Configuration& other)
{
    copyFrom(other);
}

Configuration::Configuration(Configuration&& other)
{
    moveFrom(std::move(other));
}

Configuration& Configuration::operator=(const Configuration& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Configuration& Configuration::operator=(Configuration&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

Configuration::~Configuration()
{
    free();
}

void Configuration::insert(Component* component)
{
    if (size == capacity)
        resize();

    components[size++] = component;
}

size_t Configuration::getSize() const
{
    return size;
}

std::ostream& operator<<(std::ostream& os, const Configuration& conf)
{
    for (size_t i = 0; i < conf.size; i++)
    {
        conf.components[i]->output(os);
    }
}
