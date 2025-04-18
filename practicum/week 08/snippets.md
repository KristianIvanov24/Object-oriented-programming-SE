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
3. Какво ще отпечата следният фрагмент?

```c++
#include <iostream>
#include <stdexcept>

class A {
public:
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
};

class B {
public:
    B() { 
        std::cout << "B()" << std::endl; 
    }
    ~B() { std::cout << "~B()"<< std::endl;
            throw std::runtime_error("Exception in B constructor");
}
};

class C {
public:
    C() { std::cout << "C()" << std::endl; }
    ~C() { std::cout << "~C()" << std::endl; }
};

void func() {
    A a;
    B b;
    C c;
    throw std::runtime_error("Exception in func");
}

int main() {
    try {
        func();
    } catch (...) {
        std::cout << "Caught exception\n";
    }
}
```
4. Какво ще се изпечата?

```c++
class A {
    int* ptr1;
    int* ptr2;

public:
    A() {
        std::cout << "Allocating ptr1\n";
        ptr1 = new int[100]; 
        
        std::cout << "Allocating ptr2\n";
        ptr2 = new int[999999999999]; 
    }

    ~A() {
        delete[] ptr1;
        std::cout << "deleting ptr1" << std::endl;
        delete[] ptr2;
        std::cout << "deleting ptr2" << std::endl;
    }
};

int main() {
    try {
        A a;
    } catch (const std::bad_alloc& e) {
        std::cout << "Caught memory allocation exception: " << e.what() << "\n";
    }
}
```
<details>
  <summary>Решение</summary>

  ```cpp
  class A {
      int* ptr1;
      int* ptr2;

  public:
      A() {
          std::cout << "Allocating ptr1\n";
          ptr1 = new int[100]; 
          try {
              std::cout << "Allocating ptr2\n";
              ptr2 = new int[999999999999];
          } catch (const std::bad_alloc& e) {
              delete[] ptr1;
              throw;
          }
    }
    ~A() {
          delete[] ptr1;
          std::cout << "deleting ptr1" << std::endl;
          delete[] ptr2;
          std::cout << "deleting ptr2" << std::endl;
    }
};

