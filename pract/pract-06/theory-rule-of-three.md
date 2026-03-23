# Rule of three
## Копиращ конструктор и operator=
**Копиращ конструктор** - приема обект от същия клас и текущият става негово копие
```c++
class A {
public:
    A(const A& other) {
        // copy logic
    }
};
```

**Ако не го разпишем компилаторът създава такъв! Той извиква рекурсивно копиращите конструктори на член-данните, които са от съставен тип, а примитивните типове данни ги копира по стойност.**

Можем да го извикаме по следните начини:
```c++
class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    A(const A& other) {
        std::cout << "A(const A&)" << std::endl;
    }
};

void f(A a) {...}

int main() {
    A obj; // A()
    A obj1 = obj; // A(const A&)
    A obj2(obj); // A(const A&)
    f(obj); // A(const A&)
}
```

Пример с член-данни:
```c++
class B {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    B(const B& other) {
        std::cout << "B(const B&)" << std::endl;
    }
};

class A {
public:
    B b;

    A() {
        std::cout << "A()" << std::endl;
    }

    // внимание: тук ако не използваме инициализиращ списък, понеже сме разписали
    // копиращия конструктор на А сами, ще се извиква дефолтен на В
    // затова трябва да го извикаме експлицитно чрез иниц. списък
    // ако оставим компилаторът да го разпише сам, това се случва автоматично
    A(const A& other) : b(other.b)
        std::cout << "A(const A&)" << std::endl;
    }
};

class C {
    B b;
};

int main() {
    A obj1;        // B() -> A()
    std::cout << "----" << std::endl;

    A obj2 = obj1; // B(const B&), A(const A&)

    C c;
    C c1 = c; // B(const B&) и за С не се отпечатва, понеже не сме го разписали
}
```

**operator=** - функция/оператор
- Приема обект от същия тип и текущият става негово копие
- Текущият обект трябва да е съществувал преди това

**Ако не го разпишем то компилаторът отново създава такъв, викайки operator= рекурсивно върху член-данните на нашия клас.**  
**Копиращият конструктор създава нов обект, а оператор= модифицира вече съществуващ такъв!**

```c++
class A {
public:
    A() = default;

    A(const A& other) {
        std::cout << "A(const A&)" << std::endl;
    }

    A& operator=(const A& other) {
        std::cout << "operator=(const A&)" << std::endl;
    }
};

int main() {
    A obj; // A()
    A obj1 = obj; // A(const A&) - въпреки че сме използвали =, тук се извика коп. констр., защото тепърва създаваме обекта
    А obj2; // A()
    obj2 = obj1; // operator=(const A&)
}
```

Пример с член-данни:
```c++
class B {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    B(const B& other) {
        std::cout << "B(const B&)" << std::endl;
    }

    B& operator=(const B& other) {
        std::cout << "operator=(const B&)" << std::endl;
        return *this;
    }
};

class A {
public:
    B b;
    // не сме разписали operator=
};

int main() {
    A obj1; // B()

    A obj2; // B()

    obj2 = obj1; // operator=(const B&) - извикан от operator= на А
}
```

## Проблем с генерираните от компилатор коп. констр. и operator=
Нека имаме следния клас:
```c++
class Person {
private:
    char* name;
    int age;

public:
    Person(const char* name, int age) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
    }

    ~Person() {
        delete this->name;
    }
};
```
В този случай компилаторът ни генерира коп. констр. и operator=, както винаги, но ще копира член-данните по стойност (типът int и указателят са примитивни типове). При следния код:
```c++
int main() {
    Person p1("Mitko", 20);
    Person p2 = p1; // коп. констр.
}
```
Копират се член-данните по стойност. Стойността на указател е адрес, следователно и двата обекта от тип Person ще имат указател, който сочи към една и съща памет (това се нарича shallow copy). Така в края на областта на видимост (scope), в който е дефиниран дадения обект (тоест, в случая, при затварящата скоба `}` на `main()`) ще се извикат техните деструктори и ще се опитат да изтрият една и съща памет, което най-вероятно ще накара програмата да крашне, а в някои случаи води до трудно откриваеми бъгове.

Поради този проблем за всеки клас, който работи с динамична памет, ни се налага да разписваме тези функции сами - копиращ конструктор, operator= и деструктор (rule of three).

Коректният клас Person ще изглежда по следният начин:
```c++
class Person {
private:
    char* name;
    int age;

public:
    Person(const char* name, int age) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
    }

    Person(const Person& other) {
        copyFrom(other);
    }

    Person& operator=(const Person& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Person() {
        free();
    }

private:
    void free() {
        delete[] name;
        name = nullptr;
        age = 0;
    }

    void copyFrom(const Person& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        age = other.age;
    }
};
```

Тук е изнесена логика във две private функции за триене и копиране, просто за да не я повтаряме в копиращия конструктор и operator=.  
Проверяваме дали адресите на обекта, чиято стойност присвояваме, се различават (тоест дали `this != &other`), за да избегнем self-assignment (присвояване на обекта към самия себе си), което може да доведе до изтриване на данните преди изобщо да сме ги копирали.

Operator= връща референция към текущия обект, за да позволи верижно присвояване (напр. `a = b = c`, както сте правили и по УП с числа). Да напомним, че поради дясната асоциативност на оператор=, оценяването на горния израз ще бъде `(a = (b = c))`, тоест първо ще се изпълни оператор= за b и c, а след това ще се изпълни оператор= за a и резултата от `b = c` (който е референция към b).
