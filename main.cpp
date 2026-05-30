#include <iostream>
#include "MyVector.hpp"

template<typename T>
void printVector(const MyVector<T>& v) {
    std::cout << "Vector: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\nSize: " << v.size()
        << ", Capacity: " << v.capacity() << "\n\n";
}

int main() {
    MyVector<int> v;

    std::cout << "=== push_back (copy) ===\n";
    v.push_back(1); v.push_back(2); v.push_back(3);
    printVector(v);

    std::cout << "=== push_back (move) ===\n";
    int x = 10;
    v.push_back(std::move(x));
    printVector(v); 

    std::cout << "=== operator[] ===\n";
    v[0] = 100;
    printVector(v);                   

    std::cout << "=== front / back ===\n";
    std::cout << "Front: " << v.front() << "\n";
    std::cout << "Back:  " << v.back() << "\n\n";

    std::cout << "=== pop_back ===\n";
    v.pop_back();
    printVector(v);               

    std::cout << "=== copy constructor ===\n";
    MyVector<int> v2 = v;
    printVector(v2);

    std::cout << "=== copy assignment ===\n";
    MyVector<int> v3;
    v3 = v;
    printVector(v3);

    std::cout << "=== move constructor ===\n";
    MyVector<int> v4 = std::move(v2);
    printVector(v4);

    std::cout << "=== move assignment ===\n";
    MyVector<int> v5;
    v5 = std::move(v3);
    printVector(v5);

    std::cout << "=== clear ===\n";
    v5.clear();
    printVector(v5);                   

    std::cout << "=== empty ===\n";
    std::cout << (v5.empty() ? "Vector is empty\n" : "Vector is not empty\n");

    return 0;
}