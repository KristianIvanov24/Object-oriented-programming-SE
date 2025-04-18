#include <iostream>

void throwException() 
{
    int choice;
  
    std::cout
            << "What do you want to throw?\n"
            << " [1] char\n"
            << " [2] int\n"
            << " [3] double\n"
            << " [4] std::exception object\n"
            << " [5] std::out_of_range object\n"
            << "Your choice: ";
  
    std::cin >> choice;
  
    switch (choice) 
    {
        case 1: throw '!';
        case 2: throw 5;
        case 3: throw 5.5;
        case 4: throw std::runtime_error("Something happened!");
        case 5: throw std::out_of_range("Something is out of range!");
        default:
            throw std::logic_error("A number between 1 and 5 was expected!");
    }

    std::cout << "Will this line ever be executed? Never!\n";
}

// външна функция, която обработва само два вида изключения
void caller()
{
    try 
    {
        // дори и функцията да хвърли изключение от тип char,
        // няма да бъде направено преобразуване до int
        // не се осъществява неявно преобразуване за примитивните типове данни
        // единствено, ако имаме йерархия от изключения,
        // изключение от производен тип може да бъде прихванато от catch блок,
        // в който е указан базовият тип
        // ако в catch блока трябва да бъдат изброени и производните типове, и базовия,
        // то базовият тип трябва да бъде накрая
        throwException();
    } 
    catch (int ex) 
    { 
        std::cout << "Caught an int: " << ex << std::endl; 
    } 
    catch (double ex) 
    {
        std::cout << "Caught a double: " << ex << std::endl;
    }
}

int main() 
{
    try 
    {
        caller();
    }
    // ако изключението е обект, то трябва да бъде прихванато по псевдоним,
    // за да се избегне излишното му копиране
    catch (const std::out_of_range &ex) 
    {
        std::cout << "Caught a std::out_of_range: " << ex.what() << std::endl;
    }
    // std::out_of_range преди std::exception, защото е производен клас
    // в противен случай изключение от тип std::out_of_range ще бъде прихването
    // в catch блока на std::exception
    catch (const std::exception &ex) 
    {
        std::cout << "Caught a std::exception: " << ex.what() << std::endl;
    }
    // специален тип catch блок, който се използва за прихващане на всякакъв вид изключения,
    // ако се използва трябва да стои най-отдолу, като последен блок
    catch (...) 
    {
        std::cout << "Caught something the rest have failed to catch... but what is it?\n";
    }
}
