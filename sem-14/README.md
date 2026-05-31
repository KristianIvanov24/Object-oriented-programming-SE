# Колекция от обекти в полиморфна йерархия. Множествено наследяване. Диамантен проблем. 

## Полиморфна колекция
Когато имаме полиморфна йерархия, можем да съхраняваме различни наследници в една обща колекция чрез указатели към базовия клас.

При модерния C++ използваме std::unique_ptr и std::vector.
```c++
std::vector<std::unique_ptr<Shape>> shapes;
```

Така в колекцията можем да съхраняваме различни фигури: ```Circle```, ```Rectangle```, ```Triangle```, но достъпвани през общия базов клас Shape.

### Защо използваме указатели?
Ако пазим обектите директно, например като ```std::vector<Shape>``` ще получим object slicing. При копиране на наследник в обект от базов тип се губи информацията за реалния тип на обекта. Затова използваме указатели към базовия клас.

### Виртуален деструктор
Базовият клас трябва да има виртуален деструктор. 
```c++
virtual ~Shape() = default;
```
Това гарантира, че при триене през указател към Shape ще се извика правилният деструктор на наследника.

### Копиране на полиморфна колекция
```std::unique_ptr``` е move-only тип и не може да бъде копиран. Следното е невалидно: 
```c++
std::vector<std::unique_ptr<Shape>> copy = shapes;
```
Освен това, дори да можехме да копираме базовия клас директно, би се получил object slicing.

#### Виртуалната функция clone()
За да реализираме полиморфно копиране, дефинираме виртуална функция clone.
```c++
class Base
{
public:
    virtual std::unique_ptr<Base> clone() const = 0;

    virtual ~Base() = default;
};

// Der.cpp
std::unique_ptr<Base> Der::clone() const
{
    return std::make_unique<Der>(*this);
}
```
Създава нов обект от реалния тип на наследника чрез копиране на текущия обект и връща ownership-а чрез ```std::unique_ptr```

#### Имплементация в наследниците
Всеки наследник трябва сам да знае как да създаде свое копие.

```c++
class Circle : public Shape
{
public:
    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Circle>(*this);
    }
};

class Rectangle : public Shape
{
public:
    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Rectangle>(*this);
    }
};

class Triangle : public Shape
{
public:
    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Triangle>(*this);
    }
};
```

## Множествено наследяване

Клас може да наследява от повече от един базов клас.

```c++
class A 
{ 
public: 
	int a;
};

class B 
{ 
public: 
	int b;
};

class C : public A, public B {};

```

Няма значение, че класа може да не е в началото, има механизъм, чрез който обекта се намира.
```c++
void f(A& obj) {}

void g(B* ptr) {}

int main()
{
	C obj;
	f(obj);
	g(&obj);
}
```

От значение е реда, в който наследяване класовете. 
```c++
// BaseClass = BC

class BC1 {...};
class BC2 {...};
class BC3 {...};

class Der : public BC1, public BC2, public BC3 
{
public:
	Der(...) : BC1(...), BC2(...), BC3(...) // we can permutade those, so BC2(...), BC3(...), BC1(...) is valid and so on..., but constr will always be called in the order of inheritance

	Der& operator=(const Person& other)
	{
		if(this != &other)
		{
			BC1::operator=(other);
			BC2::operator=(other);
			BC3::operator=(other);
			// it's best practice to call base class operator= in the order of inheritance
			free();
			copyFrom(other);
		}

		return *this;
	}
};
```

## Диамантен проблем
```c++
class A { public: int x; };

class B : public A {};

class C : public A {};

class D : public B, public C {};

int main() 
{
    D obj;
}
```

Конструктора на ```A``` бива извикан 2 пъти, а ако имахме и деструктор - той също щеше да бъде извикан 2 пъти.
Тоест, обектът ```obj``` има 2 копия на всички данни на базовия клас ```A```, което предизвиква двусмислия/неяснотии(ambiguous behaviour).

## Виртуално наследяване
Решението на горният проблем е използването на виртуално наследяване.
Класовете ```B``` и ```C``` трябва да наследят виртуално ```A```, за да избегнем 2-те копия на ```A```.

Когато използваме ключовата дума ```virtual``` при наследяване, конструкторът по подразбиране на прародителя се извиква по подразбиране, дори ако родителските класове извикват изрично конструктор с параметри. Тоест всеки наследник на клас, който наследява друг като ```virtual```, трябва да избере кой конструктор се вика на прародителя(виртуално наследения клас). В случая ```D```, трябва експлицитно да каже кой конструктор на ```A``` да се извика.

```c++
class A { public: int x; };

class B : virtual public A {};

class C : virtual public A {};

class D : public B, public C {};

int main() 
{
    D obj;
}
```

## Виртуални таблици при множествено и виртуално наследяване
### При множествено наследяване
```c++
#include <iostream>

class BC1
{
public:
    virtual void f()
    {
        std::cout << "BC1::f()\n";
    }

    virtual void k()
    {
        std::cout << "BC1::k()\n";
    }
};

class BC2
{
public:
    virtual void g()
    {
        std::cout << "BC2::g()\n";
    }
};

class BC3
{
public:
    virtual void f()
    {
        std::cout << "BC3::f()\n";
    }

    virtual void t()
    {
        std::cout << "BC3::t()\n";
    }
};

class Der : public BC1, public BC2, public BC3
{
public:
    void f() override
    {
        std::cout << "Der::f()\n";
    }

    void g() override
    {
        std::cout << "Der::g()\n";
    }
};

int main()
{
    Der d;

    BC1* ptr1 = &d;
    BC2* ptr2 = &d;
    BC3* ptr3 = &d;

    ptr1->f();
    ptr1->k();

    std::cout << "----------------\n";

    ptr2->g();

    std::cout << "----------------\n";

    ptr3->f();
    ptr3->t();
}
```
Указателя на ```ptr2``` съдържа адрес към BC2, който се намира в Der, а не към този на Der, затова при множественето наследяване към виртуалната таблица има допълнителен параметър - Δ <br>
**Δ(class)** - колко е отместването на даден клас от началото на наследника му
- Δ(BC1) = 0
- Δ(BC2) = sizeof(BC1)
- Δ(BC3) = sizeof(BC1) + sizeof(BC2)

### При виртуално наследяване
``` c++
#include <iostream>

class A
{
public:
    virtual void f()
    {
        std::cout << "A::f()\n";
    }

    virtual void g()
    {
        std::cout << "A::g()\n";
    }

    virtual void k()
    {
        std::cout << "A::k()\n";
    }

    virtual void t()
    {
        std::cout << "A::t()\n";
    }
};

class B : virtual public A
{
public:
    void g() override
    {
        std::cout << "B::g()\n";
    }
};

class C : virtual public A
{
public:
    void f() override
    {
        std::cout << "C::f()\n";
    }
};

class D : public B, public C
{
public:
    void t() override
    {
        std::cout << "D::t()\n";
    }
};

int main()
{
    D d;

    A* ptr = &d;

    ptr->f(); 
    ptr->g(); 
    ptr->k(); 
    ptr->t();
}
```

| Функция | Отместване |
|---|---|
|  C::f() |  -Δ(A) + Δ(C) |
|  B::g() |  -Δ(A) |
|  D::t() |  -Δ(A) | 
|  A::k() |  0 | 

## Задачи
В една фирма съществуват различни видове служители. Всеки служител има име и служебен номер. Мениджърите ръководят проекти, а инженерите работят по технически задачи. Съществува и служител, наречен **технически мениджър** – той изпълнява едновременно ролите на инженер и мениджър.

1. **Създайте клас `Employee`**, който съдържа:
   - `име` на служителя (низ)
   - `идентификационен номер` (цяло число)
   - метод `printInfo()`, който извежда информацията за служителя

2. **Създайте клас `Manager`**, който:
   - наследява `Employee`
   - съдържа `име на проект` (низ)
   - има собствена имплементация на `printInfo()`

3. **Създайте клас `Engineer`**, който:
   - наследява `Employee`
   - съдържа `техническа специализация` (низ)
   - има собствена имплементация на `printInfo()`

4. **Създайте клас `TechManager`**, който:
   - наследява едновременно от `Manager` и `Engineer`
   - съдържа метод `assignTask(const MyString& task)`, който извежда съобщение от вида:  
     ```
     TechManager [name] assigns task: [task]
     ```
5. **Създайте клас `Firm`**, който:
  - съдържа колекция от работници
  - съдържа метод, който дава пълна информация за всички работници
  - съдържа метод, който добавя работник 
  - съдържа метод, който премахва работник по идентификационен номер
