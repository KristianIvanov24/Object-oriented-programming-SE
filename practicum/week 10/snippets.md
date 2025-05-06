# Теоретични примери #

**Задача 1:** Какво ще се отпечата?
```c++
#include <iostream>
using namespace std;

class Base
{
  public:
  Base()
  {
    cout << "Base()" << std::endl;
  }
  ~Base()
  {
    cout<<"~Base()" << std::endl;
  }
};

class Derived : public Base
{
  public:
  Derived(int i)
  {
    cout << i << std::endl;
  }
  ~Derived()
  {
    cout<<"~Derived()" << std::endl;
  }
};

int main()
{
  Derived obj(10);
  return 0;
}
```
**Задача 2:** Какво ще се отпечата?

```c++
#include <iostream>

using namespace std;

class A
{
public:
	void f() const
	{
		cout << "A::f()" << std::endl;
	}
};

class B : public A
{
public:
	void f() const
	{
		cout << "B::f()" << std::endl;
	}
};

int main()
{
	B obj;
	obj.f();

	const A& ref = obj;
	ref.f();

	return 0;
}
```

**Задача 3:** Какво ще се отпечата?
```c++
#include <iostream>
using namespace std;
class X {
public:
	void f() const {
		cout << "X::f()" << endl;
	}
};

class Y : public X {
public:
	void f() const {
		cout << "Y::f()" << endl;
	}
};

class Z : protected Y {
public:
	void g() const {
		cout << "Z:g()" << endl;
	}
};

void func1(const X& obj) {
	obj.f();
}

void func2(const Y& obj) {
	obj.f();
}

void func3(const Z& obj) {
	obj.g();
	obj.f();
}

int main()  {
	Y obj1;
	Z obj2;

	func1(obj1);
	func2(obj2);
	func3(obj2);
	return 0;
}
```

**Задача 4:** Какво ще се отпечата?
```c++
#include <iostream>

using namespace std;

class A
{
	int a = 0;
public:

	void change(int i) {
		a = i;
	}
	void value_of_a() {
		cout << a << endl;
	}
};

class B : public A
{
	int a = 15;
public:
	void print() {
		cout << a << endl;
	}
};

int main()
{
	B b;
	b.change(10);
	b.print();
	b.value_of_a();

	return 0;
}
```
**Задача 5:**  Изберете подходящи модификатори за достъп в дадения код, така че функцията d3 и работата с обекта Der x да се компилират изпълняват кореткно, а работата с обекта Der y да води до грешки.
```c++
#include <iostream>
using namespace std;

class Base		  
{
...: int b1;
...: int b2;
...: int b3();
};

class Der : ... Base
{
...: int d1;
...: int d2;
...: int d3()
   {
	b1++;
	b3();
	cout << d2 << "\n";
	return b1+d2;
   }
};

int main()
{
	Der x;
	x.d1 = 15;
	x.d3();
	x.b3();

	Der y;
	y.b1 = 1;
	y.d2 = 2;
	y.b2 = 3;

	return 0;
}
```

**Задача 6:** Какво не е наред със следния код?
```c++
#include <iostream>
using namespace std;

class Base {
	char* str1;

public:
	// Приемаме, че имаме коректно разписана голяма четворка
	Base(const char* data) {}

};

class Der : public Base {
	char* str2;

	void copyFrom(const Der& other);
	void free();

public:

	Der(const char* str1, const char* str2) {
		...
	}

	Der(const Der& other) {
		copyFrom(other);
	}

	Der& operator=(const Der& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}

	~Der() {
		free();
	}
};

int main()  {
	return 0;
}
```
