# Теоретични примери

За задачи 1, 2 и 3 са дадени следните класове и функции:

```c++
class A {  
public:
   A() {  
       std::cout << "A()" << std::endl;  
   }  
 
   A(const A& other) {  
       std::cout << "A(const A&)" << std::endl;  
   }  
 
   A& operator=(const A& other) {  
       std::cout << "operator=(const A&)" << std::endl;  
       return *this;  
   }  
 
   ~A() {  
       std::cout << "~A()" << std::endl;  
   }  
};  
 
class B {  
   A a;

public:
   B() {  
       std::cout << "B()" << std::endl;  
   }  
 
   B(const B& other) : a(other.a) {  
       std::cout << "B(const B&)" << std::endl;  
   }  
 
   B& operator=(const B& other) {  
       std::cout << "operator=(const B&)" << std::endl;
   	a = other.a;    
       return *this;  
   }  
 
   ~B() {  
       std::cout << "~B()" << std::endl;  
   }  
};

void f1(const B& b) {};  
void f2(B b) {};  
void f3(B* ptr) {};
```

**Задача 1:** Какво ще изведе на конзолата следният код при извикване на функцията?

```c++
void task1() {  
    A a;  
    A copy = a;  
    A aa;  
    aa = a;  
}
```

**Задача 2:** Какво ще изведе на конзолата следният код при извикване на функцията?

```c++
void task2 () {  
    B b;  
    f1(b);  
  
    f2(b);  
    A a;  
}
```

**Задача 3:** Какво ще изведе на конзолата следният код при извикване на функцията?

```c++
void task3 () {  
    f2(B());  
    B b;  
    f3(&b);  
}
```

**Задача 4:** Ще се компилира ли следният код?
```c++
class Foo {
    int value;
    static int sValue;
public:
    Foo(int v) : value(v) {}

    static void f() {
        std::cout << sValue << std::endl;
        std::cout << value << std::endl;
    }

    void g() {
        std::cout << sValue << std::endl;
        std::cout << value << std::endl;
    }

    static int getStatic() { return sValue; }
    void increment() { sValue++; }  
};
int Foo::sValue = 5;
```