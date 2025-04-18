# Теоретични примери #

**Задача 1:** Какво ще се изведе на конзолата?
```c++
#include <iostream>

class A {
public:
	A() {
		std::cout << "A()" << std::endl;
	}
	A(const A& other) {
		std::cout << "CC of A()" << std::endl;
	}
	A& operator=(const A& other) {
		std::cout << "OP= of A()" << std::endl;
		return *this;
	}
	~A() {
		std::cout << "~A()" << std::endl;
	}
};

class B {
public:
	B() {
		std::cout << "B()" << std::endl;
	}
	B(const B& other) {
		std::cout << "CC of B()" << std::endl;
	}
	B& operator=(const B& other) {
		std::cout << "OP= of B()" << std::endl;
		return *this;
	}
	~B() {
		std::cout << "~B()" << std::endl;
	}
};

class X {
	A obj1;
	B obj2;
public:
	X(const A& a, const B& b) {
		obj1 = a;
		obj2 = b;
		std::cout << "X()" << std::endl;
	}

	~X() {
		std::cout << "~X()" << std::endl;
	}
};

int main() {
	A obj1;
	B obj2;
	X obj(obj1, obj2);
}
```


**Задача 2:** Какво ще се изведе на конзолата?
```c++
#include <iostream>

class A
{
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}

	A(const A& other)
	{
		std::cout << "K.K A()" << std::endl;
	}

	A& operator=(const A& other)
	{
		std::cout << "OP= A()" << std::endl;
		return *this;
	}

	~A()
	{
		std::cout << "~A()" << std::endl;
	}
};

class B
{
public:
	B()
	{
		std::cout << "B()" << std::endl;
	}

	B(const B& other)
	{
		std::cout << "K.K B()" << std::endl;
	}

	B& operator=(const B& other)
	{
		std::cout << "OP= B()" << std::endl;
		return *this;
	}

	~B()
	{
		std::cout << "~B()" << std::endl;
	}
};

class X
{
private:
	A* obj1;
	B& obj2;

public:
	X(const A& a, B* b) : obj2(*b)
	{
		obj1=new A(a);
		std::cout << "X()" << std::endl;
	}

	~X()
	{
		delete obj1;
		std::cout << "~X()" << std::endl;
	}
};

int main()
{
	A obj1;
	B obj2;

	X obj(obj1, &obj2);

	return 0;
}
```

**Задача 3:** Кои функции ще се компилират и кои не? Има ли семантична грешка в някоя от функциите (да прави нещо, което не трябва, но да се компилира)?
```c++
class A{
    int first;
    mutable int second;

public:
    void f1(){
    };

    void f2() const 
    {     

    }

    void f3() const
    {
        f1();
    };

    void f4() {
        f1();
    }

    void f5() const
    {
        first++;
    }

    void f6() const
    {
        second++;
    }

    void f7() const
    {
        int temp = first;
        temp++;
    }

    int getFirst() const
    {
        return first;
    }

    int getSecond() const
    {
        return second;
    }
};
```
