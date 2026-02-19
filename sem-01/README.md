#  **Структури/Класове и обединения. Пространство от имена и енумерации.**

##  **1. Структури и Класове**
- Последователност от полета, които се запазвазват в определен ред
- Използват се за групиране на елементи. 
- Елементите, наричани още членове, могат да бъдат от различен тип и с различна големина.

```c++
struct Box
{
    double height; 
    double width;
    double length;

    // double height, width, length; is also possible
    
    //Default values
    //double height = 1; 
    //double width = 1;
    //double length = 1;
    
}


class Box
{
public: // visibility for class attributes
    double height;
    double width;
    double length;
}

 ```

###  **Деклариране на обекти от новия тип**
 ```c++
Box b; // default values to height and width and length if given

Box b2 = {3, 4, 3.4}; // height = 3, width = 3, length = 3.4

Box b2{3, 4, 3.4}; // height = 3, width = 3, length = 3.4
 ```

###  **Достъп до член-данните**
  ```c++
Box b;
b.height = 13;
b.width = 14;
b.length = 20;
 ```

### **Създаване на динамични обекти**
 ```c++
#include <iostream>

struct Box
{
    double height;
    double width;
    double length;
};

double calculcateVolume(const Box& b)
{
    return b.height * b.width * b.length;
}

int main()
{
    Box* boxPtr = new Box();

    // different types of assigning a value to a property when you have a pointer
    (*boxPtr).height = 3;
    (*boxPtr).width = 1;
    boxPtr->length = 4;
	
    std::cout << calculcateVolume(*boxPtr) << std::endl;
	
    delete boxPtr;
}
```

### **Подаване във функции**
Ако няма да променяме обекта го подаваме по **константна референция.**
 ```c++
double calculcateVolume(const Box& b)
{
    return b.height * b.width * b.length;
}
```
Може и само по **референция**, но тогава може да се правят промени върху подадения аргумент. 
   
 ```c++
void readBox(Box& b)
{
    cin >> b.height >> b.width >> b.length;
}
 ```
Може и да го подаваме по **копие**.
 ```c++
Box revertBox(Box b)
{
    double temp = b.height;
    b.height = b.width;
    b.width = temp;

    return b;
}
```

### **Масиви от обекти**
 ```c++
struct Box
{
    double height;
    double width;
    double length;
};

int main()
{
    Box arr1[30]; // 30 boxes
    Box* arr2 = new Box[20]; // 20 boxes in dynamic mem.
	
    std::cout << arr1[0].height << " " << arr2[3].width << std::endl;

    delete[] arr2;
}
```

### **Влагане на обекти**
 ```c++
struct Box
{
    double height;
    double width;
    double length;
};

class Warehouse
{
public:
    char name[1024];
    Box b1;
    Box b2;
};

int main()
{
    Warehouse w = { "Ekont", { 1, 2, 3 }, { 4, 5, 3 } };

    std::cout << w.name;
}
```

### **Подравняване на паметта**
Всяка структура/клас има alignment requirement - разликата между адресите на 2 съседни член-данни. Определя се от размера на най-голямата примитивна член-данна.

 ```c++
struct A
{
    int i; // 4
    bool b; // 1
};

struct B
{
    double a; // 8
    int b; // 4
    bool c; // 1
    short d; // 2
};

struct C
{
    int i; // 4
    B b; // 16
};

struct D
{
    double a; // 8
    int b; // 4
    char c[]; // 4
};

struct E
{
    char c;
    int i;
    char c1;
}


struct EBetter
{
    int i;
    char c;
    char c1;
}


int main()
{
    std::cout << sizeof(A) << std::endl; // 8
    std::cout << sizeof(B) << std::endl; // 16
    std::cout << sizeof(C) << std::endl; // 24
    std::cout << sizeof(D) << std::endl; // 16
    std::cout << sizeof(E) << std::endl; // 12
    std::cout << sizeof(EBetter) << std::endl; // 8
}
```
### **Разлика между структури и класове**
На пръв поглед еднакви като държание със следните разлики в достъпа им по подразбиране:
- **Class** - по подразбиране всички член-данни и член-функции не са достъпни извън класа
- **Struct** - наследени от езика С, по подразбиране всички член-данни и член-функции са достъпни извън класа
- Ще разгледаме подробно разликите по-късно в курса

<br> <br>

Уговорка
- ***големи обекти*** - използваме клас
- ***малки обекти*** - използваме структура

##  **2. Обединения**
Подобно на структурите/класовете като идея за групиране на елементите, но на доста различен принцип откъм разпределение на ресурсите. Големината на структурата/класа трябва да се дели на размера на най-голямата член данна.

 ```c++
union A
{
    int i; // 4
    short s; // 2
    char c; // 1
};

int main()
{
    std::cout << sizeof(A) << std::endl; // 4
	
    A a;
    a.i = 65;
    std::cout << a.c << std::endl; // 'A'
}
```

##  **3. Пространство от имена**
Инструмент за избягване на конфликти на имена. Има scope, в който дефинираме символи

```c++
namespace myNamespace 
{
    int value = 42;

    void printValue() 
    {
        std::cout << "Value: " << value << std::endl;
    }
}
```

Използваме:
- чрез using namespace **myNamespace** - целия namespace
```c++
int main() 
{
    using namespace myNamespace;
    printValue();
}
```
- чрез using **myNamespace::printValue** - конкретен обект
```c++

int main() 
{
    using myNamespace::printValue;
    printValue();
}
```
- чрез оператора за резолюция
```c++
int main() 
{
    myNamespace::printValue();
}
```

##  **4. Енумерации**
### Unscoped enums
`enum` е дефиниран тип, който съдържа набор от именувани цели константи. Стойностите са имплицитно преобразуеми в `int`, като по подразбиране започват от 0. Ако укажем ст-ст **n**, то следващия елелемт има ст-ст **n+1**

 ```c++
#include <iostream>

enum Color 
{ 
    Red, // 0 
    Green, // 1
    Blue = 4, // 4
    Orange // 5
};

int main() 
{
    Color myColor = Green;
    int value = Green; 

    std::cout << "Color value: " << value << std::endl; // 1
}

```

Тъй като зад енумерациите седят числа, това може да доведе до нежелани резултати.
 ```c++
#include <iostream>

enum Color 
{ 
    Red, // 0 
    Green, // 1
    Blue, // 2
    Orange // 3
};

enum Fruits
{
    Apple, // 0
    Banana, // 1
    Cherry, // 2
    Rawsberry // 3
};

int main() 
{
    Color myColor = Orange;
    Fruits myFruit = Rawsberry; 

    if(myFruit == myColor)
        std::cout << "Fruit Rawsberry is the same as Color Orange!"; // logical error because a fruit is not a color 
}

```

### Scoped enums
`enum class` предоставя по-сигурна алтернатива на enum, като предотвратява имплицитното преобразуване и ограничава стойностите до собствения им обхват.

 ```c++
#include <iostream>

enum class Status 
{ 
    Success, 
    Failure, 
    Pending 
};

int main() 
{
    Status s = Status::Success; // Трябва да се използва операторът за обхват

    // int value = s; // ГРЕШКА: Няма имплицитно преобразуване към int
    int value = (int)(s); // Позволено при явно преобразуване(кастване)

    std::cout << "Статус стойност: " << value << std::endl; // Изход: 0
}
```

## Задача
Реализирайте система за управление на библиотека:
- Структура/клас **Book** със следните полета:
    - title (низ с дължина най-много 64 символа)
    - author (низ с дължина най-много 32 символа)
    - publicationYear (int)
    - status (enum: Available, Borrowed, Reserved)
- Структура/клас **Library**, която съдържа:
    - name (низ с дължина най-много 32 символа)
    - Масив от Book (максимум 10 книги)
    - bookCount (брой налични книги)
- Функции:
    - addBook(Library&, const char*, const char*, int) – добавя книга в библиотеката.
    - borrowBook(Book&) – маркира книга като заета.
    - reserveBook(Book&) – маркира книга като резервирана.
    - printLibrary(const Library&) – извежда всички книги и техния статус.
    - printLibraryAlphabetically(const Library&) - извежда всички книги и техния статус в азбучен ред.
