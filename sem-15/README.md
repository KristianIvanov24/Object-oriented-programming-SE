# Type casting. Увод в Design Patterns. SOLID принципи.

## Type casting.

Добре е да избягваме C-style cast:
```c++
int x = (int)3.14;
```

Основни видове cast в модерния C++:
- static_cast
- dynamic_cast
- reinterpret_cast
- const_cast


### static_cast
- подходящ за преобразуване между съвместими типове
- подходящ за примитивни типове
- може да се използва при наследяване
- няма runtime проверка
- compile time check

```c++
float f = 3.14;
int i = static_cast<int>(f); // безопасно, но губим информация
```
``` c++
class Base {};
class Derived : public Base {};

Base* b = new Base();
Derived* d = static_cast<Derived*>(b); // компилира, но е опасно
```

### dynamic_cast
- използва се при полиморфизъм
- при cast-ване към Derived(наследник) клас.
- нужна е поне една виртуална функция.
- runtime check
- за указатели може да върне nullptr
- за референции хвърля std::bad_cast

```c++
class Base 
{
public:
    virtual void f() {}
};

class Derived : public Base 
{
public:
    void g() {}
};

int main() 
{
    {
        Base* b = new Derived();
        Derived* d = dynamic_cast<Derived*>(b);
        if (d) 
            d->g(); // безопасно проверено по време на изпълнение
    }

    {
        Base* b = new Base();
        Derived* d = dynamic_cast<Derived*>(b);

        if (!d)
            std::cout << "Invalid cast";
    }
}
```

### const_cast
- използва се за добавяне/премахване на const към променлива
- не прави обекта non-const
- ако оригиналният обект е const и го променяме -> undefined behavior

```c++
void print(char* str) 
{
    std::cout << str << "\n";
}

int main() 
{
    char text[] = "Hello";
    const char* ptr = text;

    print(const_cast<char*>(ptr));
}
```

### reinterpret_cast
- преобразуване на указател от произволен тип към указател от произволен тип
- няма проверка за безопасност
- използва се рядко

```c++
int* p = new int(10);
char* c = reinterpret_cast<char*>(p); // char* ще сочи към байтовете на int-а
```

## [Design Patterns (Шаблони за проектиране)](https://refactoring.guru/)

* Утвърдени добри практики за често срещани проблеми в ОО дизайна.
* Представляват готови идеи за организация на класове и обекти.
* Позволяват кодът да бъде по-гъвкав, разширяем и лесен за поддръжка.
* Дават общ език между програмистите.

Design patterns не са готов код, а шаблони за решаване на проблеми.

**Недостатък:** Ако се използват без нужда, могат да доведат до прекалено сложен дизайн.

Design patterns се разделят на:
* Creational
* Structural
* Behavioral

## Creational Patterns

Creational patterns се фокусират върху създаването на обекти.

### Singleton

Singleton гарантира, че от даден клас ще съществува само една инстанция.

Използва се когато:

* имаме глобален ресурс
* искаме централизирано управление
* не искаме многократно създаване на тежки обекти

Пример от реалния живот:

* президент
* правителство
* database connection

Основна идея:

* private constructor
* забранено копиране
* static функция за достъп до инстанцията

```cpp
#include <iostream>

class President
{
private:
    President() = default;

public:
    President(const President&) = delete;
    President& operator=(const President&) = delete;

    static President& getInstance()
    {
        static President instance;
        return instance;
    }

    void makeDecision() const
    {
        std::cout << "President makes a decision\n";
    }
};

int main()
{
    President& p1 = President::getInstance();
    President& p2 = President::getInstance();

    p1.makeDecision();

    std::cout << (&p1 == &p2) << "\n";
}
```

### Factory Method

Factory Method позволява наследниците да определят какви обекти ще се създават.

Основна идея:

* базовият клас работи с абстракции
* наследниците решават какъв конкретен обект да се създаде

Пример от реалния живот:

* RoadLogistics използва Truck
* SeaLogistics използва Ship

```cpp
#include <iostream>
#include <memory>

class Transport
{
public:
    virtual void deliver() const = 0;
    virtual ~Transport() = default;
};

class Truck : public Transport
{
public:
    void deliver() const override
    {
        std::cout << "Truck delivery\n";
    }
};

class Ship : public Transport
{
public:
    void deliver() const override
    {
        std::cout << "Ship delivery\n";
    }
};

class Logistics
{
public:
    virtual std::unique_ptr<Transport>
        createTransport() const = 0;

    void planDelivery() const
    {
        auto transport = createTransport();
        transport->deliver();
    }

    virtual ~Logistics() = default;
};

class RoadLogistics : public Logistics
{
public:
    std::unique_ptr<Transport>
        createTransport() const override
    {
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics
{
public:
    std::unique_ptr<Transport>
        createTransport() const override
    {
        return std::make_unique<Ship>();
    }
};

int main()
{
    RoadLogistics road;
    road.planDelivery();

    SeaLogistics sea;
    sea.planDelivery();
}
```

### Abstract Factory

Abstract Factory създава цели семейства свързани обекти.

Пример:

* Modern furniture
* Victorian furniture

Искаме:

* Chair
* Sofa

Но всички обекти трябва да бъдат в един стил.

```cpp
#include <iostream>
#include <memory>

class Chair
{
public:
    virtual void sitOn() const = 0;
    virtual ~Chair() = default;
};

class Sofa
{
public:
    virtual void lieOn() const = 0;
    virtual ~Sofa() = default;
};

class ModernChair : public Chair
{
public:
    void sitOn() const override
    {
        std::cout << "Modern chair\n";
    }
};

class VictorianChair : public Chair
{
public:
    void sitOn() const override
    {
        std::cout << "Victorian chair\n";
    }
};

class ModernSofa : public Sofa
{
public:
    void lieOn() const override
    {
        std::cout << "Modern sofa\n";
    }
};

class VictorianSofa : public Sofa
{
public:
    void lieOn() const override
    {
        std::cout << "Victorian sofa\n";
    }
};

class FurnitureFactory
{
public:
    virtual std::unique_ptr<Chair>
        createChair() const = 0;

    virtual std::unique_ptr<Sofa>
        createSofa() const = 0;

    virtual ~FurnitureFactory() = default;
};

class ModernFactory : public FurnitureFactory
{
public:
    std::unique_ptr<Chair>
        createChair() const override
    {
        return std::make_unique<ModernChair>();
    }

    std::unique_ptr<Sofa>
        createSofa() const override
    {
        return std::make_unique<ModernSofa>();
    }
};

class VictorianFactory : public FurnitureFactory
{
public:
    std::unique_ptr<Chair>
        createChair() const override
    {
        return std::make_unique<VictorianChair>();
    }

    std::unique_ptr<Sofa>
        createSofa() const override
    {
        return std::make_unique<VictorianSofa>();
    }
};

void createFurniture(const FurnitureFactory& factory)
{
    auto chair = factory.createChair();
    auto sofa = factory.createSofa();

    chair->sitOn();
    sofa->lieOn();
}

int main()
{
    ModernFactory modern;
    createFurniture(modern);
}
```

### Prototype

Prototype позволява създаване на нови обекти чрез копиране на вече съществуващи.

Използва се когато:

* създаването на обекта е скъпо
* искаме копие на съществуващ обект

Пример:

* клониране на овца

```cpp
#include <iostream>
#include <memory>

class Sheep
{
    std::string color;

public:
    Sheep(const std::string& color)
        : color(color)
    {}

    std::unique_ptr<Sheep> clone() const
    {
        return std::make_unique<Sheep>(*this);
    }

    void print() const
    {
        std::cout << color << " sheep\n";
    }
};

int main()
{
    auto original =
        std::make_unique<Sheep>("White");

    auto cloned = original->clone();

    original->print();
    cloned->print();
}
```

## Structural Patterns

Structural patterns описват как класове и обекти се комбинират в по-големи структури.

### Composite

Composite позволява дървовидна структура от обекти, която може да се използва като един обект.

Има:

* Leaf
* Composite

Пример:

* кутии в кутии
* файлови системи
* UI дървета

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Item
{
public:
    virtual void show() const = 0;
    virtual ~Item() = default;
};

class Product : public Item
{
    std::string name;

public:
    Product(const std::string& name)
        : name(name)
    {}

    void show() const override
    {
        std::cout << "Product: "
                  << name << "\n";
    }
};

class Box : public Item
{
    std::vector<std::unique_ptr<Item>> items;

public:
    void add(std::unique_ptr<Item> item)
    {
        items.push_back(std::move(item));
    }

    void show() const override
    {
        std::cout << "Box contains:\n";

        for(const auto& item : items)
            item->show();
    }
};

int main()
{
    auto bigBox = std::make_unique<Box>();

    bigBox->add(
        std::make_unique<Product>("Phone"));

    bigBox->add(
        std::make_unique<Product>("Laptop"));

    auto smallBox = std::make_unique<Box>();

    smallBox->add(
        std::make_unique<Product>("Charger"));

    bigBox->add(std::move(smallBox));

    bigBox->show();
}
```

## Behavioral Patterns

Behavioral patterns описват как обектите комуникират помежду си.

### Command

Command капсулира действие в обект.

Позволява:

* undo/redo
* queues
* GUI buttons

Пример:

* remote control

```cpp
#include <iostream>
#include <memory>

class Light
{
public:
    void on()
    {
        std::cout << "Light ON\n";
    }
};

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class LightOnCommand : public Command
{
    Light& light;

public:
    LightOnCommand(Light& light)
        : light(light)
    {}

    void execute() override
    {
        light.on();
    }
};

class RemoteControl
{
    std::unique_ptr<Command> command;

public:
    void setCommand(
        std::unique_ptr<Command> cmd)
    {
        command = std::move(cmd);
    }

    void pressButton()
    {
        command->execute();
    }
};

int main()
{
    Light light;

    RemoteControl remote;

    remote.setCommand(
        std::make_unique<LightOnCommand>(light));

    remote.pressButton();
}
```

### Iterator

Iterator позволява обхождане на колекция без да знаем вътрешната ѝ структура.

Пример:

* TV remote traversing channels

```cpp
#include <iostream>
#include <vector>
#include <string>

template<typename T>
class Iterator
{
    const std::vector<T>& data;
    size_t index = 0;

public:
    Iterator(const std::vector<T>& data)
        : data(data)
    {}

    bool hasNext() const
    {
        return index < data.size();
    }

    T next()
    {
        return data[index++];
    }
};

class TVCollection
{
    std::vector<std::string> channels;

public:
    void add(const std::string& channel)
    {
        channels.push_back(channel);
    }

    Iterator<std::string> getIterator() const
    {
        return Iterator<std::string>(channels);
    }
};

int main()
{
    TVCollection tv;

    tv.add("Discovery");
    tv.add("HBO");
    tv.add("National Geographic");

    auto it = tv.getIterator();

    while(it.hasNext())
    {
        std::cout << it.next() << "\n";
    }
}
```

### Visitor

Visitor позволява добавяне на нова функционалност към група обекти без да променяме самите класове.

Основна идея:

* обектите приемат visitor
* visitor реализира различно поведение за различните типове

Пример:

* insurance company visiting buildings

```cpp
#include <iostream>
#include <memory>
#include <vector>

class House;
class Factory;

class Visitor
{
public:
    virtual void visit(House&) = 0;
    virtual void visit(Factory&) = 0;
    virtual ~Visitor() = default;
};

class Building
{
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Building() = default;
};

class House : public Building
{
public:
    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

class Factory : public Building
{
public:
    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

class InsuranceAgent : public Visitor
{
public:
    void visit(House&) override
    {
        std::cout << "Insuring house\n";
    }

    void visit(Factory&) override
    {
        std::cout << "Insuring factory\n";
    }
};

int main()
{
    std::vector<std::unique_ptr<Building>>
        buildings;

    buildings.push_back(
        std::make_unique<House>());

    buildings.push_back(
        std::make_unique<Factory>());

    InsuranceAgent agent;

    for(auto& building : buildings)
        building->accept(agent);
}
```

## Solid Principles
SOLID е акроним за пет принципа на проектиране, предназначени да направят софтуерния дизайн по-разбираем, гъвкав и поддържащ.
- Single Responsibility principle
- Open-Closed Principle
- Liskov Substitution Principle
- Interface Segregation Principle
- Dependency Inversion Principle

**Single Responsibility principle**: A class should have only one reason to change
```c++
// Нарушен SRP	
class Report 
{
public:
	void generate() { /* ... */ }
	void print() { /* ... */ } // нарушава SRP – отговаря и за принтиране
};
```
```c++
// Приложен SRP
class Report 
{
public:
	std::string generate() { return "Report data"; }
};

class Printer 
{
public:
	void print(const std::string& content) 
    {
		std::cout << content << "\n";
	}
};
```

**Open-Closed Principle:** Software entities should be open for extension, but closed for modification

```c++
// Нарушен OCP
class Shape 
{
public:
	std::string type;
};

double calculateArea(const Shape& s) 
{
	if (s.type == "circle") { /* ... */ }
	else if (s.type == "rectangle") { /* ... */ }
	// При добавяне на нов тип трябва да променим функцията – лоша практика
}
```

```c++
// Приложен OCP
class Shape 
{
public:
	virtual double area() const = 0;
	virtual ~Shape() = default;
};

class Circle : public Shape 
{
	double r;
public:
	Circle(double r) : r(r) {}
	double area() const override { return 3.14 * r * r; }
};

class Rectangle : public Shape 
{
	double w, h;
public:
	Rectangle(double w, double h) : w(w), h(h) {}
	double area() const override { return w * h; }
};

double printArea(const Shape& shape) 
{
	return shape.area(); // без нужда от промяна при нови типове
}
```

**Liskov Substitution Principle:** If S is a subtype of T, then objects of type T in a program may be replaced with objects of type S without altering any of the desirable properties of that program (e.g. correctness)

```c++
// Нарушен LSP
class Bird 
{
public:
	virtual void fly() { std::cout << "Flying\n"; }
};

class Penguin : public Bird 
{
public:
	void fly() override { throw std::runtime_error("Penguins can't fly"); }
};
```

```c++
// Приложен LSP
class Bird 
{
public:
	virtual void move() = 0;
};

class Sparrow : public Bird 
{
public:
	void move() override { std::cout << "Flying\n"; }
};

class Penguin : public Bird 
{
public:
	void move() override { std::cout << "Swimming\n"; }
};
```


**Interface Segregation Principle:** No client should be forced to depend on methods it does not use

```c++
// Нарушен ISP
class IMachine 
{
public:
	virtual void print() = 0;
	virtual void scan() = 0;
	virtual void fax() = 0;
};

class SimplePrinter : public IMachine { };

// Класът SimplePrinter трябва да имплементира неща, които не ползва
```

```c++
// Приложен ISP
class IPrinter 
{
public:
	virtual void print() = 0;
};

class IScanner 
{
public:
	virtual void scan() = 0;
};

class SimplePrinter : public IPrinter 
{
public:
	void print() override { std::cout << "Printing\n"; }
};
```

**Dependency Inversion Principle:** High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g. interfaces). Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

```c++
// Нарушен DIP
class FileLogger 
{
public:
	void log(const std::string& msg) { /* запис във файл */ }
};

class App 
{
	FileLogger logger;
public:
	void doSomething() 
    {
		logger.log("Started");
	}
};
```

```c++
// Приложен DIP
class ILogger 
{
public:
	virtual void log(const std::string& msg) = 0;
	virtual ~ILogger() = default;
};

class FileLogger : public ILogger 
{
public:
	void log(const std::string& msg) override 
    {
		std::cout << "Logging to file: " << msg << "\n";
	}
};

class App 
{
	ILogger& logger;
public:
	App(ILogger& logger) : logger(logger) {}
	void doSomething() 
    {
		logger.log("Started");
	}
};
```
