#pragma once
#include <utility>        

template<typename T>
class MyVector {
private:
    T* data;
    size_t sz;
    size_t cap;

    void grow() {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];
        for (size_t i = 0; i < sz; i++)
            newData[i] = std::move(data[i]);
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    MyVector() : data(nullptr), sz(0), cap(0) {}

    ~MyVector() { delete[] data; }


    MyVector(const MyVector& other) : data(nullptr), sz(0), cap(0) {
        data = new T[other.cap];
        cap = other.cap;
        sz = other.sz;
        for (size_t i = 0; i < sz; i++)
            data[i] = other.data[i];
    }


    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            cap = other.cap;
            sz = other.sz;
            data = new T[cap];
            for (size_t i = 0; i < sz; i++)
                data[i] = other.data[i];
        }
        return *this;
    }


    MyVector(MyVector&& other) noexcept
        : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }


    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

   
    void push_back(const T& value) {
        if (sz == cap) grow();
        data[sz++] = value;
    }

    void push_back(T&& value) {         
        if (sz == cap) grow();
        data[sz++] = std::move(value);
    }

    void pop_back() {
        if (sz > 0) sz--;
    }

    void clear() { sz = 0; }

   
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T& front() { return data[0]; }
    const T& front() const { return data[0]; }

    T& back() { return data[sz - 1]; }
    const T& back()  const { return data[sz - 1]; }

    
    size_t size()     const { return sz; }
    size_t capacity() const { return cap; }
    bool   empty()    const { return sz == 0; }
};