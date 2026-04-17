#include <iostream>
#include <utility>

template<typename T>
class MyVector
{
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCap);

    void copyFrom(const MyVector& other);
    void moveFrom(MyVector&& other);
    void free();

public:
    MyVector();
    ~MyVector();

    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);

    MyVector(MyVector&& other);
    MyVector& operator=(MyVector&& other);

    void push_back(const T& value);
    void push_back(T&& value);

    void pop_back();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t getSize() const;
    size_t getCapacity() const;
    bool empty() const;

    void clear();

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;
};

template<typename T>
void MyVector<T>::resize(size_t newCap)
{
    T* newData = new T[newCap];

    for (size_t i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCap;
}

template<typename T>
void MyVector<T>::copyFrom(const MyVector& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];

    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template<typename T>
void MyVector<T>::moveFrom(MyVector&& other)
{
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
void MyVector<T>::free()
{
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template<typename T>
MyVector<T>::MyVector()
{
    data = nullptr;
    size = capacity = 0;
}

template<typename T>
MyVector<T>::~MyVector()
{
    free();
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
{
    copyFrom(other);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other)
{
    moveFrom(std::move(other));
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& value)
{
    if (size == capacity)
    {
        size_t newCap = (capacity == 0) ? 1 : capacity * 2;
        resize(newCap);
    }

    data[size++] = value;
}

template<typename T>
void MyVector<T>::push_back(T&& value)
{
    if (size == capacity)
    {
        size_t newCap = (capacity == 0) ? 1 : capacity * 2;
        resize(newCap);
    }

    data[size++] = std::move(value);
}

template<typename T>
void MyVector<T>::pop_back()
{
    if (size > 0)
    {
        size--;
    }
}

template<typename T>
T& MyVector<T>::operator[](size_t index)
{
    return data[index];
}

template<typename T>
const T& MyVector<T>::operator[](size_t index) const
{
    return data[index];
}

template<typename T>
size_t MyVector<T>::getSize() const
{
    return size;
}

template<typename T>
size_t MyVector<T>::getCapacity() const
{
    return capacity;
}

template<typename T>
bool MyVector<T>::empty() const
{
    return size == 0;
}

template<typename T>
void MyVector<T>::clear()
{
    size = 0;
}

template<typename T>
T& MyVector<T>::front()
{
    return data[0];
}

template<typename T>
const T& MyVector<T>::front() const
{
    return data[0];
}

template<typename T>
T& MyVector<T>::back()
{
    return data[size - 1];
}

template<typename T>
const T& MyVector<T>::back() const
{
    return data[size - 1];
}