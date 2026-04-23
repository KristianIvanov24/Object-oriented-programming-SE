# Умни указатели

## Умни указатели (Smart Pointers)

Обвиващ клас около обикновен указател, който автоматично освобождава паметта.

## Защо съществуват Smart Pointers

Преди да използваме умни указатели, управлението на паметта извършвахме ръчно.

```cpp
int* p = new int(5);
...
delete p;
```

Ако забравим `delete`, получаваме memory leak.

Основният проблем е:
* кой притежава ресурса
* кой трябва да извика delete
* кога трябва да бъде освободена паметта

Умните указатели решават този проблем чрез автоматично управление на ресурса.

## unique_ptr - 1 указател за 1 обект

* единствен собственик на ресурса
* не може да се копира
* може да се прехвърля чрез `std::move`
* освобождава ресурса автоматично

```cpp
#include <memory>
#include <iostream>

class A
{
public:
    A() { std::cout << "A()\n"; }
    ~A() { std::cout << "~A()\n"; }
};

int main()
{
    std::unique_ptr<A> ptr = std::make_unique<A>();
}
```

### unique_ptr не позволява копиране

```cpp
std::unique_ptr<A> p1 = std::make_unique<A>();
std::unique_ptr<A> p2 = p1; // ERROR
```

Причината е, че не трябва да има двама собственици на един и същ ресурс.

### Прехвърляне на ownership

```cpp
std::unique_ptr<A> p1 = std::make_unique<A>();
std::unique_ptr<A> p2 = std::move(p1);
```

След move:

```cpp
if (!p1)
    std::cout << "p1 is null";
```

Ownership-ът е прехвърлен към `p2`.

## shared_ptr - 1 обект, много указатели

* пази указател към обект
* пази брояч колко shared_ptr сочат към него
* когато броячът стане 0 → обектът се изтрива

```cpp
#include <memory>
#include <iostream>

class A
{
public:
    A() { std::cout << "A()\n"; }

    void f()
    {
        std::cout << "A::f()";
    }

    ~A() { std::cout << "~A()\n"; }
};

int main()
{
    std::shared_ptr<A> p1 = std::make_shared<A>();
    std::shared_ptr<A> p2 = p1;
    std::shared_ptr<A> p3 = p1;

    p1->f();
}
```

### use_count()

```cpp
std::shared_ptr<A> p1 = std::make_shared<A>();

std::cout << p1.use_count() << "\n"; // 1

std::shared_ptr<A> p2 = p1;

std::cout << p1.use_count() << "\n"; // 2
```

Това показва колко shared_ptr използват един и същ ресурс.

## weak_ptr - слаба (non-owning) връзка

* сочи към обект, менажиран от shared_ptr
* не увеличава брояча
* не притежава ресурса
* може да сочи към вече изтрит обект

```cpp
#include <memory>
#include <iostream>

class A
{
public:
    A() { std::cout << "A()\n"; }
    void f() { std::cout << "A::f()"; }
    ~A() { std::cout << "~A()\n"; }
};

int main()
{
    std::shared_ptr<A> p1 = std::make_shared<A>();

    std::weak_ptr<A> wp = p1;
}
```

### weak_ptr не може да се dereference-ва директно

Следното няма да работи:

```cpp
wp->f();
```

Трябва да използваме:

```cpp
if (auto temp = wp.lock())
{
    temp->f();
}
```

Причината е, че weak_ptr може да сочи към вече унищожен обект.

### Проблем със shared_ptr

```cpp
class B;

class A
{
public:
    std::shared_ptr<B> ptr;
};

class B
{
public:
    std::shared_ptr<A> ptr;
};

int main()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->ptr = b;
    b->ptr = a;
}
```

В този случай destructors няма да се извикат.

Причината:

* A държи B
* B държи A
* reference count никога не достига 0

#### Решение чрез weak_ptr

Един от указателите трябва да стане:

```cpp
std::weak_ptr<A> ptr;
```

Така цикличната зависимост се прекъсва.

## Употреба на умни указатели

| Указател          | Собственост    | Копиране                        | Автоматично освобождаване | Типична употреба   |
| ----------------- | -------------- | ------------------------------- | ------------------------- | ------------------ |
| `std::unique_ptr` | Да             | Не може да се копира, само move | Да                        | Един owner         |
| `std::shared_ptr` | Да (споделена) | Да                              | Да                        | Shared ownership   |
| `std::weak_ptr`   | Не             | Да                              | Не                        | Избягване на цикли |

## Задачa - Library Archive System

Да се реализира система за управление на библиотечен архив. Системата трябва да моделира библиотека, която съдържа архиви, книги, читатели и библиотекари.

### Book
Всеки обект `Book` съдържа:
* заглавие
* автор
* година на издаване
* уникален идентификатор
* информация дали книгата е заета

### Archive
Всеки `Archive` представлява архив или секция в библиотеката и съдържа:

* име на архива
* масив от книги

#### Archive трябва да реализира:
* добавяне на книга
* премахване на книга по идентификатор
* търсене на книга
* извеждане на всички книги
* заемане на книга
* връщане на книга

### Reader

Всеки `Reader` представлява читател в библиотеката и съдържа:
* име
* номер на читателска карта
* колекция от заети книги

#### Reader трябва да реализира:
* заемане на книга
* връщане на книга
* извеждане на всички взети книги
* проверка дали вече е взел конкретна книга

### Librarian

Всеки `Librarian` представлява библиотекар и съдържа:
* име
* служебен номер
* архиви, които наблюдава

#### Librarian трябва да реализира:

* добавяне на архив за наблюдение
* извеждане на всички наблюдавани архиви
* проверка дали архивът все още съществува

### Library

Главният клас, който съдържа всички архиви.

`Library` съдържа:
* колекция от архиви
* колекция от библиотекари
* колекция от читатели
  
#### Library трябва да реализира:
* добавяне на архив
* премахване на архив
* преместване на книга между два архива
* извеждане на цялата информация за библиотеката
* търсене на архив по име
* добавяне на библиотекар
* търсене на библиотекар по служебен номер
* извеждане на всички библиотекари
* добавяне на читател
* търсене на читател по номер на карта
* извеждане на всички читатели

```cpp
int main()
{
    Library library;

    auto b1 = make_unique<Book>("The Hobbit", "J.R.R. Tolkien", 1937, 1);
    auto b2 = make_unique<Book>("1984", "George Orwell", 1949, 2);
    auto b3 = make_unique<Book>("Clean Code", "Robert Martin", 2008, 3);

    auto fiction = make_shared<Archive>("Fiction");
    auto programming = make_shared<Archive>("Programming");

    fiction->addBook(move(b1));
    fiction->addBook(move(b2));
    programming->addBook(move(b3));

    library.addArchive(fiction);
    library.addArchive(programming);

    auto reader = make_shared<Reader>("Ivan", 1001);
    library.addReader(reader);

    auto librarian = make_shared<Librarian>("Maria", 5001);
    librarian->addArchive("Fiction");
    librarian->addArchive("Programming");

    library.addLibrarian(librarian);

    cout << "Before moving book:\n";
    library.printLibrary();

    library.moveBook(2, "Fiction", "Programming");

    library.lendBookToReader(1001, 3, "Programming");

    cout << "\nAfter moving book:\n";
    library.printLibrary();

    return 0;
}
```
