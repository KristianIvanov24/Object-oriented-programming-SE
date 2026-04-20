#include <iostream>
#include <utility>

template <typename T>
class Stack {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void free();
    void copyFrom(const Stack& other);
    void moveFrom(Stack&& other);

    void resize(size_t newCap);
public:
    Stack() = default;

    Stack(const Stack& other);
    Stack& operator=(const Stack& other);

    Stack(Stack&& other);
    Stack& operator=(Stack&& other);

    ~Stack();

    void pop();
    void push(const T& el);

    const T& top() const;

    bool isEmpty() const;

    void clear();

    size_t count() const;
};

template <typename T>
Stack<T>::Stack(const Stack& other) {
    copyFrom(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
Stack<T>::Stack(Stack&& other) {
    moveFrom(std::move(other));
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    free();
}

template <typename T>
void Stack<T>::pop() {
    if(isEmpty()) {
        // hvurlqme izkluchenie
        return;
    }
    
    size--;
}

template <typename T>
void Stack<T>::push(const T &el) {
    if(size == capacity) {
        resize(capacity == 0 ? 8 : capacity * 2);
    }

    data[size++] = el;
}

template <typename T>
const T &Stack<T>::top() const
{
    if(isEmpty()) {
        // fjiakoda
    }
    return data[size - 1];
}

template <typename T>
bool Stack<T>::isEmpty() const
{
    return size==0;
}

template <typename T>
void Stack<T>::clear()
{
    size = 0;
}

template <typename T>
size_t Stack<T>::count() const
{
    return size;
}

template <typename T>
void Stack<T>::free() {
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template <typename T>
void Stack<T>::copyFrom(const Stack& other) {
    size = other.size;
    capacity = other.capacity;

    data = new T[capacity];

    for(int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
void Stack<T>::moveFrom(Stack&& other) {
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = other.capacity = 0;
}

template <typename T>
void Stack<T>::resize(size_t newCap) {
    capacity = newCap;
    T* newData = new T[capacity];

    for(int i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}

