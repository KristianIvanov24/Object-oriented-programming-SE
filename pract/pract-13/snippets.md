# Теоретични примери

1. Какво ще изпечата следният фрагмент?

```c++
#include <iostream>

class A {
public:
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
};

class B {
public:
    B() { std::cout << "B()" << std::endl; }
    ~B() { std::cout << "~B()" << std::endl; }
};

void func() {
    A a;
    B b;
    throw std::runtime_error("Exception in func");
}

int main() {
    try {
        func();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}

```
2. Какво ще отпечата следният фрагмент?

```c++
class C {
public:
    C() { std::cout << "C()" << std::endl; }
    ~C() { std::cout << "~C()" << std::endl; }
};

class D {
public:
    D() { 
        std::cout << "D()" << std::endl; 
        throw std::runtime_error("Exception in D constructor");
    }
    ~D() { std::cout << "~D()"<< std::endl; }
};

int main() {
    try {
        C c;
        D d; 
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}
```


3. Какво ще се отпечата?
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