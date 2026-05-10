# Шаблони

## Шаблон (template)
Функция/клас, която работи не с променливи от някакъв дефиниран тип, а с абстрактни променливи.

### Шаблонни функции

Компилаторът генерира т. нар. шаблонна функция, като замества параметрите на шаблона с типовете на съответните фактически параметри.

```cpp
#include <iostream>

template <typename T>
T max(T a, T b) 
{
    return a > b ? a : b;
}

int main()
{
    auto res = max<int>(3, 5);
    auto res2 = max<double>(2.5, 4.1);
}
```

```template <typename T>``` - декларация, че ще работим с тип параметър

```<type>``` - казваме конкретния тип за параметрите на функцията

Обработването на типовете става по време на компилация, не по време на изпълнение.

```c++
max(3, 5); // еднакъв тип, компилаторът преобразува Т = int
max(3, 2.5); // може да доведе до грешка или нежелано преобразуване
```

Когато искаме да работим с фукнции, които приемат повече от един тип, можем да изброяваме различните типове.
```c++
template <typename T, typename U>
auto add(T a, U b) 
{
    return a + b;
}
```

### Шаблонни класове
Можем да пишем класове, чийто член-данни са без специфициран тип и да посочим конкретния тип при създаването на инстанция към класа. Всеки шаблонен клас генерира различни класове за различните типове (напр. Box<int> и Box<double> са различни класове).

```c++
template <typename T>
class Box 
{
    T value;
public:
    Box(T v) : value(v) {}

    T get() const
    {
        return value;
    }
};

int main()
{
    Box<int> b1(5);
    Box<double> b2(3.14);
}
```

## Темплейтна специализация
Различно поведение на темплейтния клас/функция за определени типове

```c++
#include <iostream>

template<typename T>
void print(T* arr, size_t size) 
{
	for (size_t i = 0; i < size; i++) 
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template<> // !!!
void print(char* arr, size_t size) 
{
	for (size_t i = 0; i < size; i++) 
	{
		std::cout << arr[i] << " ---- ";
	}
	std::cout << std::endl;
}

int main() 
{
	int arr1[] = { 1, 2 };
	print<int>(arr1, 2);
	char arr2[] = { 'a', 'b' };
	print<char>(arr2, 2);
}

// This is not a specialization
// void print(char* arr, size_t size) {
// 	for (size_t i = 0; i < size; i++) {
// 		std::cout << arr[i] << " ---- ";
// 	}
// 	std::cout << std::endl;
// }
```

## Non-type template parameters

``` c++
template <typename T, int N>
class Array {
    T data[N];
};

int main()
{
    Array<int, 10> arr;
}
```

Създаваме масив с фиксирана дължина. Шаблоните ни позволяват да приемаме конкретни стойности като константи, чиято стойност да укажем по-късно при създаване на обекта.

## Разделна компилация при шаблони
В C++ всеки .cpp файл се компилира отделно като самостоятелна единица, след което линкерът свързва получените обектни файлове (.o), като намира дефинициите на използваните функции и символи. При шаблоните обаче не съществува реален код до момента на тяхното инстанциране - компилаторът генерира конкретни функции или класове едва когато шаблонът бъде използван с даден тип. Поради това, за да може компилаторът да създаде необходимия код във всeki .cpp файл, той трябва да има достъп до пълната дефиниция на шаблона. Ако дефиницията се намира само в отделен изходен файл, тя не е видима при инстанцирането и не се генерира необходимият код, което води до грешки при свързването. Затова шаблоните се дефинират в header файлове(.hpp), така че всяка единица на компилация, която ги използва, да може да генерира нужните конкретни реализации. Шаблоните не генерират код сами по себе си, а само при използване, затова дефиницията трябва да е видима.

## Задачи 

**Задача 1:** Да се реализира клас ```MyVector```, който имитира основната функционалност на стандартния контейнер ```std::vector```. Класът трябва да работи с произволен тип данни. Класът трябва да позволява следните операции:

- push_back(value) – добавя елемент чрез копиране
- push_back(value) – добавя елемент чрез преместване (move)
- pop_back() – премахва последния елемент
- достъп до елемент чрез конкретен индекс
- front() – връща първия елемент
- back() – връща последния елемент
- size() – брой елементи
- capacity() – заделена памет
- empty() – дали е празен
- clear() – изтрива всички елементи

```c++
#include <iostream>
#include "MyVector.hpp"

template<typename T>
void printVector(const MyVector<T>& v)
{
    std::cout << "Vector: ";
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << "\nSize: " << v.size()
        << ", Capacity: " << v.capacity() << "\n\n";
}

int main()
{
    MyVector<int> v;

    std::cout << "=== push_back (copy) ===\n";
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    printVector(v);

    std::cout << "=== push_back (move) ===\n";
    int x = 10;
    v.push_back(std::move(x));
    printVector(v);

    std::cout << "=== operator[] ===\n";
    v[0] = 100;
    printVector(v);

    std::cout << "=== front / back ===\n";
    std::cout << "Front: " << v.front() << "\n";
    std::cout << "Back: " << v.back() << "\n\n";

    std::cout << "=== pop_back ===\n";
    v.pop_back();
    printVector(v);

    std::cout << "=== copy constructor ===\n";
    MyVector<int> v2 = v;
    printVector(v2);

    std::cout << "=== copy assignment ===\n";
    MyVector<int> v3;
    v3 = v;
    printVector(v3);

    std::cout << "=== move constructor ===\n";
    MyVector<int> v4 = std::move(v2);
    printVector(v4);

    std::cout << "=== move assignment ===\n";
    MyVector<int> v5;
    v5 = std::move(v3);
    printVector(v5);

    std::cout << "=== clear ===\n";
    v5.clear();
    printVector(v5);

    std::cout << "=== empty ===\n";
    std::cout << (v5.empty() ? "Vector is empty\n" : "Vector is not empty\n");

    return 0;
}
```
