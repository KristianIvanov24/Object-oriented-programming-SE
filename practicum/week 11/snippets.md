# Теоретични примери

**Задача 1:** Какво ще се отпечата?
```c++
#include <iostream>
using namespace std;

class A {
public:
    virtual void f() {
        cout << "A::f()" << endl;
    }
    virtual ~A() = default;
};

class B : public A {
public:
    void f() override {
        cout << "B::f()" << endl;
    }
    virtual void g() {
        cout << "B::g()" << endl;
    }
};

class C : public B {
public:
    void f() const {
        cout << "C::f()" << endl;
    }
    void g() override {
        cout << "C::g()" << endl;
    }
};

int main() {
    A* ptr1 = new C();
    ptr1->f();
    
    B* ptr2 = new C();
    ptr2->f();
    ptr2->g();

    C obj;
    obj.f();

    delete ptr1;
    delete ptr2;
}
```

**Задача 2:** Какво ще се отпечата? Приемаме, че работим на 64-битова архитектура.
```c++
#include <iostream>

using namespace std;

class A
{
    int a;
public:
    virtual void f()
    {
        std::cout << "A";
    }
};

class B : public A
{
    double b;
    bool c;
public:
    void f() override
    {
        std::cout << "B";
    }
};

int main()
{
    std::cout << sizeof(A);
    std::cout << sizeof(B);
}
```

**Задача 3:** Какво ще се отпечата? Има ли проблем в кода? Ако има, къде е точно?
```c++
#include <iostream>
using namespace std;
class Base {
	int a=0;
public:
	Base() {
		std::cout << "Base()" << std::endl;
	}
	virtual void f() const {
		std::cout << "Base::f()" << std::endl;
	}
	~Base() {
		std::cout << "~Base()";
	}

};

class Der1 : public Base {
	int b=0;
public:
	Der1() {
		std::cout << "Der1()" << std::endl;
	}
	void f() const override {
		Base::f();
		std::cout << "Der1::f()" << std::endl;
	}

	~Der1() {
		std::cout << "~Der1()" << std::endl;
	}
};

class Der2 : public Der1 {
	int c=0;
public:
	Der2() {
		std::cout << "Der2()" << std::endl;
	}

	~Der2() {
		std::cout << "~Der2()" << std::endl;
	}

};

int main() {
	Base* ptr = new Der2();
	ptr->f();
	delete ptr;
}
```
