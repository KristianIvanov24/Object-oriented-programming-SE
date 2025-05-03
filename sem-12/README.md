# Колекции от обекти в полиморфна йерархия. Копиране, триене, разпознаване и прихващане. Шаблони.

## Колекции от обекти в полиморфна йерархия. Копиране и триене.
### Колекция.

Можем да реализираме колекция от различни типове (но с общ базов клас), чрез масив от указатели.
Указателите трябва да са от типа на базовия клас.

```c++
class Fruit 
{
public:
	virtual void printColor() const = 0;
	virtual ~Fruit() = default;
};

class Apple : public Fruit 
{
public:
	void printColor() const override 
	{
		std::cout << "Red or green!\n ";
	}
};

class Orange : public Fruit 
{
public:
	void printColor() const override 
	{
		std::cout << "Orange!\n";
	}
};

class Lemon : public Fruit 
{
public:
	size_t sourness;

	Lemon(size_t sourness) : sourness(sourness) {}
	
	void printColor() const override 
	
		std::cout << "Yellow!\n";
	}
};

class FruitStore 
{
private:
	Fruit** fruits;
	size_t capacity;
	size_t count;
public:
	FruitStore();
	FruitStore(const FruitStore&);
	FruitStore& operator=(const FruitStore&);
	~FruitStore();
	
	void addApple();
	void addOrange();
	void addLemon(size_t sourness);
private:          
	void copyFrom(const FruitStore& other);
	void free();
};

void FruitStore::addApple() 
{
	fruits[count++] = new Apple();
}

void FruitStore::addOrange() 
{
	fruits[count++] = new Orange();
}

void FruitStore::addLemon(size_t sourness) 
{
	fruits[count++] = new Lemon(sourness);
}
```

# Триене
Понеже имаме виртуален деструктор в базовия клас, не се интересуваме в колекцията какви са обектите, които трием.
```c++
void FruitStore::free() 
{
	for(size_t i = 0; i < count; ++i) 
	{
		delete fruits[i];
	}
	
	delete[] fruits;
}
```

## Копиране
Искаме да реализираме копиране на колекцията.
Това трябва да стане без да нарушаваме абстракцията - искаме обеките да се копират без да се налага да запитваме за техния тип.
За това дефинираме виртуална функция clone, която ще връща копие на обекта. Тази функция я разписваме във всеки от наследниците.

```c++
class Fruit 
{
public:
    virtual void printColor() const = 0;
    virtual Fruit* clone() const = 0;

    virtual ~Fruit() = default
};

class Apple : public Fruit 
{
public:
    void printColor() const override 
	{
	    std::cout << "Red or green!\n";
    }

    Fruit* clone() const override 
	{
        return new Apple(*this);
    }
};

class Orange : public Fruit 
{
public:
    void printColor() const override 
	{
	    std::cout << "Orange!\n";
    }
	
    Fruit* clone() const override 
	{
	    return new Orange(*this);
    }
};

class Lemon : public Fruit {
public:
    size_t sourness;

    Lemon(size_t sourness) : sourness(sourness) {}
	
    void printColor() const override 
	{
	    std::cout << "Yellow!\n";
    }
	
    Fruit* clone() const override 
	{
	    return new Lemon(*this);
    }
};
```

От тук копирането става тривиално:
```c++
void FruitStore::copyFrom(const FruitStore& other) 
{
	fruits = new Fruit*[other.capacity];
	
	for(size_t i = 0; i < other.count; ++i) 
	{
		fruits[i] = other.fruits[u]->clone();
	}
		
	count = other.count;
	capacity = other.capacity;
}
```

## Шаблони
Функция/клас, която работи не с променливи от някакъв дефиниран тип, а с абстрактни променливи, се нарича шаблонна функция/клас

```c++
#include <iostream>
using namespace std;

template <class T>
T sum(const T& a, const T& b) 
{
    return a + b;
}

int main() 
{
    int a = 4;
    int b = 9;
    cout << sum<int>(a, b) << endl;

    double c = 3.14;
    double d = 4.5;
    cout << sum<double>(c,d) << endl;
	
    return 0;
}
```

Компилаторът генерира т. нар. шаблонна функция, като замества параметрите на шаблона с типовете на съответните фактически параметри.

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

**Необходима функция**

```c++
struct Test 
{
	void func() {}
}

template<typename T>
void f1(Test& t) 
{
	t.func();
}

template<typename T>
void f2(T& t) 
{
	t.func1();
}

int main() 
{
	Test t;
	f1<Test>(t); // ok
	f2<Test>(t); // compile error
}
```

## Задачи

**Задача 1:**
Релизирайте структурата от данни опашка. Опашката трябва да работи с **произволни типове**. След като е добавен един елемент в края на опашката, той ще може да бъде извлечен (премахнат) единствено след като бъдат премахнати всички елементи преди него в реда, в който са добавени.

**Пример**:
 ```c++
int main()
{
	queue<int> q;
	q.push(3);
	q.push(5);
	q.push(10);

	cout << q.peek() << endl; //3
	q.pop();
	
	cout << q.peek() << endl; //5
	q.pop();

	cout << q.peek() << endl; //10
	q.pop();
	
	cout << q.isEmpty() << endl; //1	
}
 ```
  **Задача 2:**
 Създайте **шаблонна** опашка с k приоритета. При взимане на елемент от опашката трябва да се връща най-отдавна добавения елемент от тези с най-висок приоритет.
 
  ```c++
int main()
{
	kPriorityQueue<char> q(4); // 4 priorities - 0, 1, 2 и 3.
	
	q.push('A',0): //adds A with lowest priority: 0
	q.push('B',3);
	q.push('C',2);
	q.push('D',2);
	q.push('E',1);
	
	//q.push('F', 5); //error! No such priority!
	
	q.peek(); // B
	q.pop();
	
	q.peek(); // C
	q.pop();
	
	q.peek(); // D
	q.pop();
	
	q.peek(); // E
	q.pop();
	
	q.peek(); // A
	q.pop();
}
 ```
