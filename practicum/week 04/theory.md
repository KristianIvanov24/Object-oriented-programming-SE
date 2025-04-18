# Теоретични примери #

1. Какво ще изведе следният код?

```c++
class Product {
  char name[20]{};
  double price = 0;
};

int main() {
  Product product;
  std::cout<<product.price;
  return 0;
}
```

2. Кои от следните извиквания на функции са възможни?

```c++
class A {
public:
    void f() {}
    void f() const {}
    void g() const {
        f();
    }
    void t() {}
};

void testFunc1(const A* ptr) {
    if (!ptr) {
        return;
    }
    ptr->f();
}

void testFunc2(const A& ref){
    ref.t();
}

int main(){
    A obj;
    obj.f();
    testFunc1(&obj);
    obj.g();
    testFunc2(obj);
    return 0;
}
```

3. Какво ще се изведе на стандартния изход след изпълнение на следния код?
```c++
#include <iostream>

class X {
	char ch = 'a';

public:
	X() {
		std::cout << "X()" << std::endl;
	}

	X(char ch) : ch(ch) {
		std::cout << "X(char)" << std::endl;
	}

	~X() {
		std::cout << "~X()" << std::endl;
	}
};

class Y{	
public:

	Y() {
		std::cout << "Y()" << std::endl;
	}

	~Y() {
		std::cout << "~Y()" << std::endl;
	}
};
int main() {
	Y* ptr = new Y[2]{};
	X obj = 'a';
	Y arr[3]{};

	delete[] ptr;
	return 0;
}
```

4. Какво ще се изведе на стандартния изход след изпълнение на следния код?
 ```c++
class C {
	double d;
public:

	C() {
		d = 3.14;
		std::cout << "C()" << std::endl;
	}

	C(double d) {
		this->d = d;
		std::cout << "C(double d)" << std::endl;
	}

	~C() {
		std::cout << "~C()" << std::endl;
	}
};

void f(C obj) {
	std::cout << "f(C obj)" << std::endl;
}

int main() {
	C obj;
	f(5.12);

	return 0;
}
```  
5. Какво ще се отпечата?

```c++
#include <iostream>

struct C {
	double d;

	C(double d) {
    		this->d = d;
    		std::cout << "C(double d)" << std::endl;
	}

	~C() {
    		std::cout << "~C()" << std::endl;
	}
};


int main() {
	C arr[2];
	C* ptr = new C[1];

	delete[] ptr;
}
```

6. Какво ще се изведе на стандартния изход след изпълнение на следния код?
```c++
class A {
public:
	A() {
		std::cout << "A()" << std::endl;
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
	~B() { 
		std::cout << "~B()" << std::endl;
	}
};

class C {
	A a;
	B b;
public:
	C() : b(), a() {
		std::cout << "C()" << std::endl;
	}
	~C() {
		std::cout << "~C()" << std::endl;
	}
};

int main() {
	C arr1[2];
	C* ptr = new C();
	return 0;
}
```
