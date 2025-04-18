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

## Разлики между `assert` и `exception`

| Характеристика | `assert`              | `exception`                        |
|----------------|------------------------|------------------------------------|
| Тип грешка     | Програмистка           | Грешка по време на работа          |
| Включен в      | Debug версии           | Всички версии                      |
| Реакция        | Прекъсване             | Позволява обработка                |

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

Можем да създадем наши собствени класове за изключения, като наследяваме```*``` от стандартните класове:

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

```* Ще говорим повече, когато учим Наследяване.```

## Задачи

**Задача 1:** Да се напише функция `throwSomething()`, която пита потребителя какъв тип изключение иска да бъде хвърлено. След това да се създаде `caller()` функция, която прихваща някои от тях, и `main()`, която прихваща останалите.

Изисквания:
- В `throwSomething()` да се използва `switch`, като се хвърля:
  - `char`
  - `int`
  - `double`
  - `std::runtime_error`
  - `std::out_of_range`
  - друго → `std::logic_error`
- В `caller()` прихващайте само `int` и `double`
- В `main()` прихващайте `std::out_of_range`, `std::exception`, и останалото (`...`)


**Задача 2:** Да се напише програма, която анализира данни от сензори за температура и влажност, идващи от IoT устройства. Данните се подават чрез файл с име `sensorReadings.txt`, който се намира в зададена директория.

Всеки ред от файла е във формат:

```
<ID>;<timestamp>;<temperature>;<humidity>
```

Където:
- `ID` е уникален идентификатор на сензора – низ от латински букви и цифри (с дължина между 4 и 8 символа)
- `timestamp` е дата и час във формат `YYYY-MM-DD HH:MM:SS`
- `temperature` е десетично число в интервала **[-50.0, 100.0]**
- `humidity` е цяло число между **0 и 100**

Примерен вход:
```
A12T9;2025-04-06 13:20:00;21.4;55
B98X2;2025-04-06 13:21:30;-12.3;102
C77Q1;2025-04-06 13:22:10;105.0;50
```

- Обработка:
   - Валидните редове да се записват във файл `processedReadings.txt` в следния формат:
     ```
     <ID> at <timestamp>: Temp=<temperature>°C, Humidity=<humidity>%
     ```
   - Невалидните редове да се записват във файл `invalidReadings.log` с информация за типа грешка.
