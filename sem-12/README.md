# Изключения.

## Въведение

Изключенията (exceptions) са механизъм за обработка на логически грешки, които могат да възникнат по време на изпълнение на програмата. Те позволяват отделяне на кода за обработка на грешки от основната логика на програмата.

```cpp
double divide(int x, int y) 
{
    if (y == 0)
        throw std::invalid_argument("Division by zero!");
    return x / y;
}
```

## Защо да използваме изключения?

### Алтернативи:
- Връщане на кодове за грешки (некомфортно и податливо на грешки)
- Връщане чрез референции/указатели

```cpp
bool divide2(int x, int y, double& result) 
{
    if (y == 0) return false;
    result = x / y;
    return true;
}
```

### Недостатъци:
- По-сложен и труден за поддръжка код
- Лесно може да се пропусне проверка за грешка

## Хвърляне и прихващане на изключения

```cpp
void f() 
{
    throw std::runtime_error("Something went wrong!");
}

int main() 
{
    try 
    {
        f();
    }
    catch (const std::exception& e) 
    {
        std::cout << e.what();
    }
}
```

## Stack Unwinding

```cpp
class A { ~A() { std::cout << "~A()\n"; } };
class B { ~B() { std::cout << "~B()\n"; } };

void g() 
{
    throw 1;
}

void f() 
{
    A a;
    B b;
    g(); // ще се изпълнят ~B() и ~A()
}

int main() 
{
    try 
    { 
        f(); 
    } 
    catch (...) 
    { 
        std::cout << "Exception caught\n"; 
    }
}
```

## [Видове изключения](https://cplusplus.com/reference/exception/exception/)

| Грешка              | Описание                          |
|---------------------|-----------------------------------|
| `std::bad_alloc`    | Невъзможност за заделяне на памет |
| `std::bad_cast`     | Невалиден cast                    |
| `std::runtime_error`| Грешка по време на изпълнение     |
| `std::logic_error`  | Нарушен инвариант на клас         |

```cpp
void f(int n) 
{
    if (n < 0) 
        throw std::invalid_argument("n must be >= 0");
}
```

## Хвърляне в конструктори
При хвърляне на изключения в конструктори, се викат деструктори само на напълно създадените обекти. Наша отговорност е да зачистваме заделените външните ресурси в конструктора!
```cpp
class Example 
{
    char* name;

public:
    Example(const char* n, int value) 
    {
        name = new char[strlen(n)+1];
        strcpy(name, n);
        if (value == 0) 
        {
            delete[] name;
            throw std::invalid_argument("Invalid value");
        }
    }
};
```

```cpp
class Example2 
{
    A obj1;
    B obj2;

public:
    Example2(const A& obj1, const B& obj2) : obj1(obj1), obj2(obj2)
    {
        // imagine obj2 throws an exception => only destr of A is called
    }
};
```

## Изключения в деструктори
В деструкторите не се хвърлят изключения. Една програма не може да поддържа две изключения едновременно, което при stack unwinding-а ще доведе до терминиране на програмата със [std::terminate](https://cplusplus.com/reference/exception/terminate/). Ако в краен случай се налага хвърляне на изключение в деструктор, то трябва да се обработи локално. (Все пак да се избягва!)
```cpp
~X() 
{
    try 
    {
        // risky operation
    } 
    catch (...) 
    {
        // handle locally
    }
}
```

## Йерархия и ред на `catch` блоковете

```cpp
try 
{
    throw std::out_of_range("Index");
}
catch (const std::out_of_range& e) 
{
    std::cout << "Out of range\n";
}
catch (const std::exception& e) 
{
    std::cout << "Generic exception\n";
}
catch (...) 
{
    std::cout << "Unknown error\n";
}
```

## Еxception Safety (Гаранции при изключения)

| Ниво                        | Гаранция                                                                 |
|-----------------------------|---------------------------------------------------------------------------|
| No-throw                    | Никога не хвърля                                                         |
| Strong guarantee            | Нищо не е променено при грешка                                           |
| Basic guarantee             | Обектът е във валидно състояние, но може да е променен                   |
| No guarantee                | Няма гаранции, може да има изтичане или непредсказуемо поведение         |

```cpp
Student& Student::operator=(const Student& other) 
{
    char* newName = new char[strlen(other.name) + 1];
    strcpy(newName, other.name);
    delete[] name;
    name = newName;
    return *this;
}
```

## Създаване на собствени изключения

Можем да създадем наши собствени класове за изключения, като наследяваме от стандартните класове:

```cpp
class SensorException : public std::runtime_error
{
public:
    SensorException(const std::string& msg) : std::runtime_error(msg) {}
};

void readSensor(int value)
{
    if (value < 0)
        throw SensorException("Negative sensor value detected!");
}

int main()
{
    try 
    {
        readSensor(-5);
    } 
    catch(const SensorException& e) 
    {
        std::cout << e.what() << '\n';
    }    
}
```

## Задачи

**Задача 1:** Да се разработи система за обработка на данни от IoT сензори за температура и влажност.

Да се реализира клас **Sensor**, който описва данни за сензор и валидира своето състояние.
Всеки сензор е във формат:
```
<ID>;<timestamp>;<temperature>;<humidity>
```

Където:
- ID е низ от латински букви и цифри с дължина между 4 и 8 символа;
- timestamp е във формат ```YYYY-MM-DD HH:MM:SS```;
- temperature е число в интервала [-50.0, 100.0];
- humidity е цяло число в интервала [0, 100].

Да се реализират следните custom exception класове:
- ```InvalidSensorIdException```
- ```InvalidTimestampException```
- ```InvalidTemperatureException```
- ```InvalidHumidityException```
- ```FileOpenException```

Класът **Sensor** трябва:
- да валидира своите данни;
- при невалидни стойности да хвърля подходящ exception;
- да предефинира операторите >> и <<.

Данните за сензорите ще се четат от файл ```sensorReadings.txt```, като за целта трябва да се резлизира допълнителен клас **SensorManager**, който да съхранява и обработва данните. При обработка:
- валидните данни да се записват във файл ```processedReadings.txt```;
- невалидните редове да се записват във файл ```invalidReadings.log``` заедно със съответното съобщение за грешка.

При възникване на грешка програмата не трябва да прекратява работа, а да продължава обработката на следващите редове.
