#pragma once

struct A
{
    int x = 2;
    int y = 3;
};

class B
{
    A** data;
    size_t capacity;
    size_t size;

    void free();
    void copyFrom(const B& other);
    void moveFrom(B&& other);
    void resize(size_t newCap);

public:
    B();
    B(const B& other);
    B& operator=(const B& other);
    ~B();

    B(B&& other) noexcept;
    B& operator=(B&& other) noexcept;

    void add(const A& obj);
};
