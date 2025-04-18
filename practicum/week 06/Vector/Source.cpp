#include <iostream>
#include "Vector.h"

int main()
{
    int arr[] = { 1,2,3,4,5 };
    Vector vec1(arr, 5);
    vec1 *= 2;

    std::cout << vec1 <<std::endl;

    Vector vec2(5);
    std::cin >> vec2;
    std::cout << vec2<<std::endl;

    std::cout << vec2 - vec1 << std::endl;
    std::cout << ~vec2<<std::endl;

    vec2.saveToFile("vector_file.dat");

    Vector vec3;
    std::cout << !vec3 << std::endl;

    vec3.readFromFile("vector_file.dat");
    std::cout << vec3 << std::endl;

    return 0;
}
