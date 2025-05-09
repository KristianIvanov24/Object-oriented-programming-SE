#include "ShoppingCart.h"

void ShoppingCart::free()
{
    delete[] items;
    items = nullptr;
}

void ShoppingCart::copyFrom(const ShoppingCart& other)
{
    count = other.count;
    capacity = other.capacity;
    items = new Item[capacity];
    for (size_t i = 0; i < count; i++)
    {
        items[i] = other.items[i];
    }
}

void ShoppingCart::moveFrom(ShoppingCart&& other) noexcept
{
    count = other.count;
    capacity = other.capacity;
    items = other.items;
    other.items = nullptr;
}

ShoppingCart::ShoppingCart()
{
    count = capacity = 0;
    items = nullptr;
}

ShoppingCart::ShoppingCart(const ShoppingCart& other)
{
    copyFrom(other);
}

ShoppingCart::ShoppingCart(ShoppingCart&& other) noexcept
{
    moveFrom(std::move(other));
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other)
{
    // TODO: insert return statement here
}

ShoppingCart& ShoppingCart::operator=(ShoppingCart&& other) noexcept
{
    // TODO: insert return statement here
}

ShoppingCart::~ShoppingCart()
{
    free();
}

void ShoppingCart::addItem(const Item& toAdd)
{
    for (size_t i = 0; i < count; i++)
    {
        if (items[i].getName() == toAdd.getName())
            return;
    }

    if (count == capacity)
        resize();

    items[count++] = toAdd;
}

void ShoppingCart::removeItem(const MyString& name)
{
    for (size_t i = 0; i < count; i++)
    {
        if (items[i].getName() == name)
        {
            swap(i, count - 1);
            count--;
            return;
        }
    }
}

int ShoppingCart::itemsCount() const
{
    return count;
}

bool ShoppingCart::exists(const MyString& name) const
{
    for (size_t i = 0; i < count; i++)
    {
        if (items[i].getName() == name)
        {
            return true;
        }
    }
    return false;
}

bool ShoppingCart::isEmpty() const
{
    return count;
}

double ShoppingCart::getPriceOf(const MyString& name) const
{
    for (size_t i = 0; i < count; i++)
    {
        if (items[i].getName() == name)
        {
            return items[i].getPrice();
        }
    }
}

double ShoppingCart::totalPrice() const
{
    double total = 0;
    for (size_t i = 0; i < count; i++)
    {
        total += items[i].getPrice();
    }

    return total;
}

void ShoppingCart::sortByName()
{
    for (size_t i = 0; i < count - 1; i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < count; j++)
        {
            if (items[min_index].getName() > items[j].getName())
                min_index = j;
        }

        if (min_index != i)
            swap(i, min_index);
    }
}

void ShoppingCart::saveToBinary(std::ofstream& ofs) const
{
    if (!ofs.is_open())
    {
        return;
    }

    ofs.write((const char*)capacity, sizeof(size_t));
    ofs.write((const char*)count, sizeof(size_t));

    for (size_t i = 0; i < count; i++)
    {
        items[i].write(ofs);
    }
}

void ShoppingCart::readFromBinary(std::ifstream& ifs)
{
    if (!ifs.is_open())
    {
        return;
    }

    ifs.read((char*)&capacity, sizeof(capacity));
    items = new Item[capacity];
    ifs.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; i++)
    {
        items[i].read(ifs);
    }
}
