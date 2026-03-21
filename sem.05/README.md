# Ключови думи static и constexpr. Копиращ конструктор и оператор за присвоявяне (=). Голяма четворка.

## Static
### Static локални променливи 
- държи се в паметта на глобалните/статичните променливи
- променяме продължителността на локалната променлива от automatic (т.е. до края на scope-а) на static (променливата се създава в началото на програмата и се унищожава в края на програмата, точно като глобалните променливи) 
- инициализира се само веднъж - при първото влизане в съответния scope и запазва стойността си дори след като излезе от scope-а

```cpp
int increment()
{
    static int value = 0;
    ++value;
    return value;
}

int main()
{
    std::cout << increment() << std::endl; //1
    std::cout << increment() << std::endl; //2
    std::cout << increment() << std::endl; //3
}
```

### Static функции
- обвързва се с една компилационна единица и не може да се използва от други файлове
- тоест не можем да използваме тази функция в друг .cpp файл


### Static член-данна на клас
- не е обвързана с конкретен обект, а с целия клас
- всички обекти от класа използват една и съща инстанция
- инициализира се извън класа

```cpp
#include <iostream>

class Counter
{
public:
    static int count;
    
    void increment()
{
        count++;
    }
};

int Counter::count = 0; // Инициализация извън класа

int main()
{
    Counter a, b;
    a.increment();
    b.increment();
    std::cout << Counter::count << std::endl; // 2
}
```

### Static член-функция на клас
- не е обвързана с конкретен обект, а с целия клас
- използва се за достъпване на статичните член-данни
- няма указател **this**
- не е нужен обект, за да се достъпи

```cpp
class Test
{
private:
    static int x; 
public:
    static void f()
    { 
        x *= 2; // може да достъпва само статичните член-данни
    }
};

int Test::x = 0; // трябва да я инициализираме извън класа

int main()
{
    Test::f(); // не ни трябва обект
}
```

## Constexpr - от C++11
- Стойността е известна при компилация
- Задължително се инициализира
- Може да се използва за array size, template-и

```cpp
constexpr int x = 5;

constexpr int square(int a) 
{
    return a * a;
}

constexpr int y = square(4); // compile-time
```

### const VS constexpr
|                   | const | constexpr |
| ----------------- | ----- | --------- |
| Не се променя     | ✔     | ✔         |
| Compile-time      | ❌     | ✔         |
| Runtime стойности | ✔     | ❌         |


## Копиращ конструктор и оператор =
Заедно с конструктора по подразбиране и деструктора във всеки клас се дефинират и следните член-функции:
 - Копиращ конструктор - конструктор, който приема обект от същия клас и създава новият обект като негово копие.
 - Оператор= - функция/оператор, който приема  обект от същия клас и променя данните на съществуващ обект от същия клас (обектът от който извикваме функцията).

**При липсата на дефиниран/и копиращ конструктор и/или оператор=, компилаторът автоматично създава такива по подразбиране.**
**Забележка:** Копиращият конструктор създава нов обект, а оператор= модифицира вече съществуващ такъв!

```c++
#include <iostream>

struct Test 
{
    Test() 
    {
        std::cout << "Default constructor\n";
    }

    Test(const Test& other) 
    {
        std::cout << "Copy constructor\n";
    }

    Test& operator=(const Test& other) 
    {
        std::cout << "operator=\n";
	    return *this;
    }

    ~Test() 
    {
        std::cout << "Destructor\n";
    }
};

void f(Test object) 
{
    //do Stuff
}

void g(Test& object) 
{
    //do Stuff
}

int main()
{
    Test t;      //Default constructor;

    Test t2(t);  // Copy constructor
    Test t3(t2); // Copy constructor	
    t2 = t3;     // operator=
    t3 = t;      // operator=

    Test newTest = t; //Copy constructor !!!!!!!

    f(t);   // Copy constructor	
    g(t);   // nothing. We are passing it as a reference. We are not copying it!

    Test* ptr = new Test();  // Default constructor // we create a new object in the dynamic memory. The destructor must be invoked explicitly  (with delete)

    delete ptr; // Destructor	

} //Destructor Destructor Destructor Destructor
```

## Голяма четворка
- Конструктор по подразбиране (default constructor)
- Копиращ конструктор
- Оператор=
- Деструктор

**Разписваме Г4 само, когато имаме динамична памет в класа/ структурата!**

## **Задачи**

**Задача 1:** Да се реализира клас ```MachineProcess```, който моделира процес в операционна система. Всеки процес се характеризира с цяло число ```pid```, име на процеса, както и цяло число, описващо използваната памет (в мегабайти).

Класът трябва да съхранява броя на съществуващите процеси в даден момент, както и функция за достъп до тази стойност. При създаване на обект броячът трябва да се увеличава, а при унищожаване – да се намалява.

Да се реализират следните функции за класа:
- промяна на използваната памет;
- извеждане на информация за процеса;
- извеждане на текущия брой на всички създадени процеси.
- сравнение на два процеса по използвана памет.

``` c++
#include <iostream>
#include "MachineProcess.h"

int main()
{
    MachineProcess p1(1, "Chrome", 200);
    MachineProcess p2(2, "", -50);

    p1.print();
    p2.print();

    std::cout << "Processes: " << MachineProcess::getProcessesCount() << std::endl;

    p2.setMemory(300);

    if (p2.hasMoreMemoryThan(p1))
        std::cout << "p2 uses more memory\n";

    MachineProcess p3 = p1;

    std::cout << "Processes: " << MachineProcess::getProcessesCount() << std::endl;

    return 0;
}
```
