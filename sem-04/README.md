# Обектно-ориентираното програмиране. Класове и обекти. Конструктори и деструктори. Използване на член-функции.

## **Обектно-ориентирано програмиране**
Програмна парадигма -  представлява фундаменталния стил на програмиране. <br/>

Обектно-ориентирано програмиране е **програмна парадигма**, при която една програмна система се моделира като набор от обекти, които взаимодействат помежду си, за разлика от традиционното виждане, в което една програма е списък от инструкции, които компютърът изпълнява. Всеки обект е способен да получава съобщения, обработва данни и праща съобщения на други обекти.

### **Принципи:**
- Абстракция
  - процесът на скриване на ненужни подробности от потребителя
- Капсулация
  - един обект трябва да предоставя на ползващия го само пряко необходимите му средства за управление.
- Наследяване
  - позволява да бъдат дефинирани и създавани обекти, които са специализирани варианти на вече съществуващи обекти.
  - класът наследник взема всички свойства и методи на класа-родител
- Полиморфизъм
  - представлява свойството на обектите от един и същи тип да имат един и същи интерфейс, но с различна реализация на този интерфейс.


## Член-функции.
Член-функциите са функции, които работят с член-данните на обекта от дадена структура.
 ```c++
struct Point
{
	int x;
	int y;
};

bool IsInFirstQuadrant(const Point& p)
{
	return p.x >= 0 && p.y >= 0;
}

int main()
{
	Point p1 = {3, 4};
	Point p2 = {-9, 8};
	std::cout << IsInFirstQuadrant(p1) << std::endl;
	std::cout << IsInFirstQuadrant(p2) << std::endl;
}
 ```
 
Може функцията да бъде член-функция:
 ```c++
struct Point
{
	int x, y;

	bool IsInFirstQuadrant() const
	{
		return x >= 0 && y >= 0;
	}
	
};

int main()
{
	Point p1 = {3, 4};
	Point p2 = {-9, 8};
	std::cout << p1.IsInFirstQuadrant() << std::endl;
	std::cout << p2.IsInFirstQuadrant() << std::endl;
}
 ```
#  
**Член-функциите**:
 - Работят с член-данните на класа.
 - Извикват се с обект на класа
 - Компилаторът преобразува всяка **член-функция** на дадена структура в
   обикновена функция с уникално име и един допълнителен параметър
   – **константен указател към обекта**.

```c++
bool Point::isInFirstQuadrant()
{
	return x >= 0 && y >= 0;
}
```

се превежда в:

```c++
bool Point::isInFirstQuadrant(Point* const this)
{     
	//remember since this is a pointer (const) to Point we use the -> operator instead, which is equivalent to (*this).member;
	return this->x >= 0 && this->y >= 0;
}
```

Като забележете, че this е const указател към Point, т.е. не можем да меним this, но можем да променяме обекта, който е сочен от него (четем декларациите на указателите отдясно наляво).
и съответно

```c++
pt.isInFirstQuadrant();
```

се превежда в:

```c++
Point::isInFirstQuadrant(&pt);
```

**Константни член-функции**:

 - Не променят член-данните на структурата.
 -  Указва се чрез записването на ключовата  дума **const** в декларацията и в края на заглавието в дефиницията им
 -  Константните обекти могат да викат **ЕДИНСТВЕНО** своите константни член-функции.
 -  В тялото на константни член-функции **НЕ МОЖЕ** да се викат неконстантни член-функции.

```c++
struct A
{
  void f() {} // f(A* const this)
  void g() const {} // g(const A* const this)
};
```

## Конструктори и деструктор.

**Жизнен цикъл на обект**:
 - Създаване на обект в даден scope – заделя се памет и член-данните се инициализират.
 - Достига се до края на скоупа(област).
 - Обектът и паметта, която е асоциирана с него се затрива.
</br> </br> </br>

**Конструктор**:
 - Извиква се веднъж - при създаването на обекта.
 - Не се указва експлицитно тип на връщане (връща констатна референция).
 - Има същото име като класа/ структурата.
 - Може да се overload-ва
 - Задава стойности на член-данните на класа/ структурата (в тялото си или чрез **member initializer list**) 
</br> </br> </br>

**Конструктор без параметри** - наричаме default (по подразбиране) :
- Ако експлицитно не сме разписали, нито един конструктор, компилаторът създава default-ен
 ```c++
 struct A
 {
     
 };
 
 // automatically will be transformed as:
 struct A
 {
     A() {};
 };
 ```

 ```c++
 struct A
 {
     
 };
 
 int main()
 {
     A arr[10]; // will call default constructor 10 times
 }
 ```

**Деструктор**:
 - Извиква се веднъж - при изтриването на обекта.
 - Не се оказва експлицитно тип на връщане.
 - Има същото име като класа със символа '~' в началото.
 - Може да има само един / не може да се overload-ва

 **При липсата на дефиниран деструктор, компилаторът автоматично създава такива по подразбиране.**
 ```c++
#include <iostream>

struct Test 
{
  Test()
  {
  	std::cout << "Object is created" << std::endl;
  }
  
 ~Test()
  {
  	std::cout << "Object is destroyed" << std::endl;
  }

  int a, b;
};

int main()
{
	{
		Test t; // Object is created 
			{
				Test t2; // Object is created 
			} // Object is destroyed (t2)

	} //Object is destroyed (t)
}
 ```
 
***Деструктори използваме за освобождаване на "външни ресурси", на които сме собственици.***
 
## Конструктори и деструктор при влагане на обекти.
 
  ```c++
#include <iostream>
#include <iomanip>

using namespace std;

struct A
{
	A()
	{
		std::cout << "Constructor(default) of A" << std::endl;
	}

	~A()
	{
		std::cout << "Destructor of A" << std::endl;
	}
};

struct B
{
	B()
	{
		std::cout << "Constructor(default) of B" << std::endl;
	}

	~B()
	{
		std::cout << "Destructor of B" << std::endl;
	}
};

struct C
{
	C()
	{
		std::cout << "Constructor(default) of C" << std::endl;
	}

	~C()
	{
		std::cout << "Destructor of C" << std::endl;
	}
};

struct X
{
	A first;
	B second;
	C obejectsArray[3];

	X()
	{ //calls Constructor(default) of A, Constructor(default) of B, Constructor(default) of C" (x3)
		std::cout << "Constructor of X" << std::endl;
	}
	~X()
	{
		std::cout << "Destructor of X" << std::endl;
	} //calls Destructor of C" (x3) , Destructor of B, Destructor of A

};

int main()
{
	X  obj; //Constructor of X
} // Destructor of X
 ```
## Абсракция.
- Използваме нещо, без да се интересуваме как работи то
- Скриваме ненужните детайли

## Капсулация (encapsulation).
 **Капсулацията** (известно още като "скриване на информация") е един от основните принципи в ООП. Тя налага разбиването на един клас на интерфейс и имплементация. Интерфейсът представлява набор от операции, които потребителят може да изпълнява свободно по начин, който не "бърка" в имплементацията.
Понякога искаме потребителите да **нямат достъп до всички член-данни и методи на даден клас**.
Това е така, защото тяхната промяна може да доведе до **неочаквано поведение** на нашата програма. Принципът за **капсулация** ни помага като позволява да определим кои методи и атрибути може да използват потребителите на нашия клас.

**Модификатор за достъп**:
 
| Модификатор за достъп: | Достъп:                         |
|------------------------|---------------------------------|
| private                | В текущия клас.                 |
| protected              | В текущия клас и *наследниците. |
| public                 | За всеки                        |

 ## Get-ъри и set-ъри (Селектори и мутатори)
Това са публични член-функции, които се използват за достъпване (get) и промяна (set) на член-данни, които са декларирани в private/protected секция на един клас.

**Пример за get-ъри и set-ъри**
```c++
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

namespace constants
{
    const int NAME_MAX_LEN = 40;
    const int NAME_MIN_LEN = 2;
    const int AGE_MIN = 0;
    const int AGE_MAX = 130;
}

namespace charUtils
{
    bool isSmallLetter(char ch)
    {
    	return ch >= 'a' && ch <= 'z';
    }
    
    bool isCapitalLetter(char ch)
    {
    	return ch >= 'A' && ch <= 'Z';
    }
    
    bool containsOnlySmallChars(const char* str)
    {
    	size_t len = strlen(str);
    
    	for (size_t i = 0; i < len; i++)
    	{
    		if (!isSmallLetter(str[i]))
    			return false;
    	}
    	return true;
    }
}

struct Person 
{
private:
	char name[constants::NAME_MAX_LEN];
	int age;
	
	bool isValidName(const char* name)
	{
		if (!name)
			return false;
			
        size_t nameLen = strlen(name);
        
		if (nameLen <= constants::NAME_MIN_LEN || nameLen >= constants::NAME_MAX_LEN)
			return false;
			
		if (!charUtils::isCapitalLetter(*name))
			return false;
			
		return charUtils::containsOnlySmallChars(name + 1);
	}
	
	bool isValidAge(int age)
	{
		return age >= constants::AGE_MIN && age <= constants::AGE_MAX;
	}
	
public:
    Person(const char* name) : age(0)
    {
        setName(name);
    }
    
	Person(const char* name, int age)
	{
		setName(name);
		setAge(age);
	}

	const char* getName() const
	{
		return name;
	}

	int getAge() const
	{
		return age;
	}

	void setName(const char* name)
	{
		if (isValidName(name))
			strcpy(this->name, name);
		else
			strcpy(this->name, "Unknown");

	}
	void setAge(int age)
	{
		if (isValidAge(age))
			this->age = age;
		else
			this->age = 15;
	}
};
```

### Класове VS Структури
На пръв поглед еднакви като държание със следните разлики в достъпа им по подразбиране:
- **Class** - по подразбиране всички член-данни и член-функции са private
- **Struct** - по подразбиране всички член-данни и член-функции са public
- Има и други разлики, които ще разгледаме по-късно в курса
</br> </br> </br> 

**Уговорка**
- ***големи обекти*** - използваме клас
- ***малки обекти*** - използваме структура


## Задачa

Реализирайте клас **Time**, който ще се използва за работа с часове (13:05:45).
Вашият клас трябва да има следния интерфейс:

 - Подразбиращ се контруктор, който създава часа на **00:00:00**.
 - Конструктор, който приема три параметъра - **час, минути и секунди**.
 - Член-функция, която връща оставащото време до **полунощ**.
 - Член-функция, която увеличава часа с 1 секунда.
 - Член-функция, която връща дали е **време за вечеря**. В рамките на задачата време за вечеря е между **20:30** и **22:00**.
 - Член-функция, която връща дали е **време за парти**. В рамките на задачата време за парти е между **23:00** и **06:00**.
  - Член-функция, която приема друг обект от тип **Time** и връща обект от тип **Time**, което е разликата между двете времена. 
  - Член-функция, която която приема друг обект от тип **Time**  и сравнява двата обекта (по-къснен/по-ранен)
  - Член-функция за принтиране на часа.

Да се направи масив от 10 времена и да се сортира с някоя от изучаваните сортировки.
