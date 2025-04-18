# Теоретични примери

За задачи 1, 2 и 3 са дадени следните класове и функции:

```c++
class A {  
public:
   A() {  
       std::cout << "A()" << std::endl;  
   }  
 
   A(const A& other) {  
       std::cout << "CC A" << std::endl;  
   }  
 
   A& operator=(const A& other) {  
       std::cout << "op= A" << std::endl;  
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
       std::cout << "CC B" << std::endl;  
   }  
 
   B& operator=(const B& other) {  
       std::cout << "op= B" << std::endl;
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
