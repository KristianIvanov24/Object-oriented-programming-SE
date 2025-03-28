# Предефиниране на оператори. Приятелски класове и функции.
Предефинирането на оператори ни позволява да дефинираме поведение на оператор, който се прилага върху операнда(и) от даден тип. Те са функции със специални имена: ключовата дума **operator** последвана от символа на респективния оператор (например **operator=**). Както всяка функция, те имат return type, лист от параметри и тяло.  

## [Oператори](https://en.cppreference.com/w/cpp/language/operators)
### Видове оператори.
в C++ има три вида оператори:

 - Унарни (на един аргумент) -> ```++, !, ~```
 - Бинарни (на два аргумента) -> ```+, -, *, /```
 - Тернарен -> ```? :```
 
Изключение е function call операторът **operator()**, който може да приема произволен брой аргументи!

При бинарните лявата операнда се подава като първи параметър, а втората - като втори.

Ако един предефиниран параметър бива дефиниран като член-функция на класа, то лявата операнда бива директно асоциирана с обекта, върху който се извиква функцията, т.е. с **this**, като в този случай оператора има с един по-малко параметри.  

**Можем да предефинираме единствено съществуващи вече оператори и не можем да създаваме нови "операторни" символи!**

Четирите символа (+,-,* и /) служат както за унарни, така и за бинарни оператори. Всеки от тях може да бъде предефиниран, като бройката параметри определя кой оператор влиза в употреба.  

### Операторите се характеризират с:
 - **Приоритет** - при изрази с повече от един на брой оператора, определят последователността, в която ще бъдат извършени операциите; (Пр.: * > +)
 - **Асоциативност** - при изрази с оператори от еднакъв порядък, аналогично дефинират последователността, в която ще бъдат извършени операциите;
    - **Ляво асоциативни** (((a$b)$c)$d)$f) -> +, -, *, /
    - **Дясно асоциативни** (a$(b$(c$(d$f)))) -> +=, -=, *=, /=
 -  **Позиция на оператора спярмо аргумента** 
    - **префиксен** -> ++a, !a, *a
    - **инфиксен** -> a + b
    - **суфиксен** -> a++

При предефинирането на оператор **не могат** да се променят *приоритета*, *асоциативността*, броят и позицията на *аргументите* му.

### Списъка на операторите в C++:
| Оператор                                       | Асоциативност                   |
|------------------------------------------------|---------------------------------|
| () [] -> . ++ - -                              |         лявоасоциативен       |
|  + - ! ~ ++ - - (type)* & sizeof               |         дясноасоциативен      |
| * / %                                          | лявоасоциативен     |
|  + -        									 |      лявоасоциативен|
|    << >>      								 |      лявоасоциативен|
|  <  <=  >  >=         						 |      лявоасоциативен|
|    ==  !=       								 |      лявоасоциативен|
|      &     									 |     лявоасоциативен |
|     ^      									 |     лявоасоциативен |
|      \|     									 |      лявоасоциативен|
|       &&    									 |      лявоасоциативен|
|      \|\|     									 |      лявоасоциативен|
|      ?:    									 |      дясноасоциативен         |
|     =  +=  -=  *=  /=  %=  >>=  <<=  &=  ^=    |      дясноасоциативен         |

_В допълнение погледнете https://en.cppreference.com/w/cpp/language/operator_precedence  - тук са описани операторите в C++, не всички от които могат да бъдат предефинирани обаче!_  

При дизайн на клас: 
- Ако се извършва IO върху класа, то се дефинират shift операторите **<<** и **>>**;
- Ако класът изисква проверка за равенство, то се дефинира оператора **==**. Ако е дефиниран операторът **==**, то най-вероятно трябва да се дефинира и оператора **!=**;
- Ако класът притежава някакъв вид наредба, то се дефинира оператора **<**. При наличието на дефиниран този оператор, то трябва и да се дефинират всички останали релационни оператори;
- return type-a на един предефиниран оператор трябва да бъде съвместим с return-a на вградените (built in) оператори. Логическите и релационните оператори връщат **bool**, аритметичните - стойност от същия тип (нова, т.е. не връщаме референция), а при операторите за присвояване (```*=,  /=, +=, -=``` и т.н.) връщат референция към лявата операнда (lhs) в операцията.   

### Предефиниране на оператор (пример)
```c++
class MyDouble
{
  int a;
  int b;
  
public:
    MyDouble(int a, int b);
    MyDouble& MyDouble::operator+=(const MyDouble& other);
};

MyDouble::MyDouble(int a, int b) : a(a), b(b)
{
    
}

MyDouble& MyDouble::operator+=(const MyDouble& other)
{
	a += other.a;
	b += other.b;
	return *this;
}
 ```
Вече може да правим следното:
```c++
int main()
{
	MyDouble d1(1, 3); //1,3;
	MyDouble d2(10,20) // 10,2;
	d1 += d2 // now d1 is 11,5
}
 ```
 
 ### Директно извикване на предефиниран оператор
Да допуснем, че сме предефинирали **operator+** за някакъв клас, а **test1** и **test2** са обекти от този клас. Тогава следните са еквивалентни
```c++
test1+test2;             //normal expression
//or equivalently        
operator+(test1,test2);  //equivalent expression
```
съответно извикваме оператор, дефиниран като член-функция (т.е. върху обект от съответния тип) аналогично на всяка такава
```c++
test1+=test2;
//or equivalently
test1.operator+=(test2);
```  
### Предефиниране на аритметични оператори
В рамките на курса ще ги дефинираме извън класа, т.е. не като член-функции, т.к. те не налагат промяна върху лявата операнда (в случая - **this**), а единствено връщат нова стойност. Тези операции **НЕ** променята състоянията на коя-да е от операндите, затова те се подават като референция към константа.  
Те обикновено генерират нова стойност, която е резултатът в следствие на използване на съоветната аритметична операция. Тази стойност се държи в локална променлива, която се връща в края на функцията.  
Когато се дефинира аритметичен оператор най-удобно е той да бъде дефиниран посредством съответстващия му съставен такъв. Причината главно е, че съставните се дефинират като член функции и всичко става много по-просто (съставните имат достъп до защитените член-данни, а също и директно могат да се използват върху локалното при дефиницията на аритметичния оператор копие, което се връща като стойност). 

Пример:

```c++
MyDouble operator+(const MyDouble& lhs, const MyDouble& rhs)
{
	MyDouble temp(lhs);        //create a local copy of lhs, calling the copy constructor of complex
	temp+=rhs;                //call to the already defined compound operator +=
	return temp;
}
```
където съответстващия съставен оператор е дефиниран като  
```c++
MyDouble& MyDouble::operator+=(const MyDouble& other)
{
	real += other.real;
	im += other.im;
	return *this;
}
 ``` 
 
### Въпрос: Кога дефинираме един оператор като член-функция?  
При предефиниране на оператори трябва да решим - да се дефинира ли като член-функция или не. В някои случаи нямаме избор, в други няма да успеем да дефинираме оператора подходящо, ако е дефиниран като член-функция.    
Следните "правила" могат да се следват като насока при решаване на този проблем:
- Присвояващия (**=**), индексния (**[]** - за достъпване на елемент, предимно при контейнери), function-call (**()**) и member access (**->** - за достъпване на елементи, при итератори и smart pointer-и) **трябва** да бъдат дефинирани като членове;
- Съставните присвояващи оператори обикновено **трябва** да бъдат дефинирани като членове. За разлика от **=** обаче, те не са задължени да бъдат такива;
- Оператори, които променят състоянието на техния обект (такива като операторите за инкрементиране, декрементиране и дереференциране) обикновено се дефинират като членове;
- Симетричните оператори - тези, които могат да преобразуват коя-да е от операндите, напр. аритметичните, релационните, побитовите - обикновено се дефинират извън класа;

![image](https://user-images.githubusercontent.com/49128895/229921765-9662c062-a990-4be0-9513-59bbf3ea095a.png)

## [Приятелски класове и приятелски функции](https://en.cppreference.com/w/cpp/language/friend)
Декларират се с на запазената дума **friend** пред прототипа на функцията.  
Даденият friend-клас/фунцкия има достъп до всички компоненти на класа. 
Т.е. всички членове на класа са public за friend-класовете/функциите приятели.

Приятелски класове/функции:
- Не се наследяват
- Не са транзитивни (приятелски клас на ваш приятелски клас, не е приятелски клас на вас)
- Може да се напишат в private, protected, public частта на class-a (Добрата практика е само в public)


### Приятелски функции (пример)

 ```c++
class MyDouble 
{
private:
	int num1;
	int num2;
public:
	friend MyDouble operator*(const MyDouble& d, int n);
	friend MyDouble operator*(int n, const MyDouble& d);
}

MyDouble operator*(const MyDouble& d, int n) 
{
	 MyDouble temp(d);
	 temp.num1 *= n;
	 temp.num2 *= n;
	
	 return temp;
}

//since the multiplication is commutative we can use the previous function in the definition of the next one
MyDouble operator*(int n, const MyDouble& d) 
{
	 return (obj * scalar);
}
```

### Оператори за вход/изход от/към поток
Както знаем вече, IO библиотеката използва shift операторите **>>** и **<<** за вход и изход от/към поток. Тя сама дефинира версии на тези оператори за четене и писане на вградени типове. 
### Предефиниране на operator<< и operator>>
```c++
class MyDouble
{
    int num1;
    int num2;
public:
	friend std::ostream& operator<<(std::ostream& os, const MyDouble& d);
	friend std::istream& operator>>(std::istream& is, MyDouble& d);
};

std::ostream& operator<<(std::ostream& os, const MyDouble& d) 
{
	return os << d.num1 << ',' << d.num2;
}

std::istream& operator>>(std::istream& is, MyDouble& d) 
{
	return is >> d.num1 >> d.num2;
}
```

### Предефиниране на оператори за равенство
Съобразно и с капсулацията се избира дали те биват дефинирани като приятели, т.к. се достъпват една по една членовете на класа, а те не биват дефинирани като член-функции.

```c++
friend bool operator==(const MyDouble& lhs, const MyDouble& rhs){
	return (lhs.num1==rhs.num1 && lhs.num2==rhs.num2);
}
```
и съответно при дефиниран такъв оператор винаги дефинираме и **operator!=**
```c++
friend bool operator!=(const MyDouble& lhs, const MyDouble& rhs){
	return !(lhs==rhs);
}
```
Принципите за дизайн на този оператор са следните
- Ако класът притежава операция за проверка за еквивалентност на два обекта, то тя бива дефинирана чрез **operator==**.
- Ако класът дефинира **operator==**, то той еднозначно трябва да проверява дали двата обекта са еквивалентни!
 - Той трябва да е транзитивен, т.е. ако ```a==b``` и ```b==c``` са true, то ```a==c``` е true;
 - Ако един клас дефинира **operator==**, то той трябва да дефинира и **operator!=**. Потребителите очакват и двете функционалности;
 - Имплементацията на един от двата оператори трябва да бъде включена в другия, т.е. не е необходимо да се дефинират независимо един от друг;

### Предефиниране на оператори за инкрементация и декрементация (++ и --)
- Префиксните връщат lvalue (обектът, от който са извикани)
- Постфиксните връщат rvalue (нов временен обект). В параметрите на предефинирания оператор се добавя dummy параметър, който не се ползва, но указва, че предефинираме постфиксен оператор

```c++
class MyDouble
{
  int a;
  int b;
  
public:

    MyDouble(int a, int b) : a(a), b(b)
    {}
    
    MyDouble& operator++() // prefix
    {
        a++; // update the state of the object
        b++;
        return *this;
    }
    
    MyDouble operator++(int dummy) // postfix
    {
        MyDouble temp = *this; // copy the current state of the object
        a++; // update the state of the object
        b++;
        return temp; // return a temp object
    }
};

int main()
{
    MyDouble obj(3, 4);
    MyDouble obj2 = obj++;
    ++obj;
    return 0;
}
 ```

## Задачи

 **Задача 1:**
Реализирайте клас **ComplexNumber**, който ще се използва за работа с комплексни числа.
Предефинирайте оператори със следната функционалност:
 - Събиране на комплексни числа.
 - Изваждане на комплексни числа.
 - Умножение на комплексни числа.
 - Деление на комплексни числа
 - Вход и изход от потоци.
 - Равенство и различност на комплексни числа
 
```c++
int main()
{
	ComplexNumber c1;
	cin >> c;

	ComplexNumber c2;
	cin >> c2;

	ComplexNumber result = c2 / c1;

	cout << result << endl;
}
 ```

**Задача 2:** 
Да се реализира клас **SpecialCustomFunction**. Класът да съдържа указател към функция, която връща и приема цели числа, както и редица от "специални" стойности. Обектите от този клас да се държат като функции. 
- За тази цел да се предефинира оператор ```()```, който приема стойност. Ако подадената стойност е специална, обектът трябва да връща нейния квадрат, в противен случай – резултата от function pointer-а.
- Да се предефинират постфиксните и префиксните оператори ```++``` и ```--```, които да увеличават и намаляват специалните стойности с единица.
- Да се предефинира оператор ```!```, който връща нов обект, в който всяка специална стойност е заменена с противоположната ѝ по стойност.

```c++
int main()
{
    int arr[5] = { 3,-4,0,10,40 };
    SpecialCustomFunction func(arr, 5, [](int num) -> int { return num * num + num; });

    std::cout << func(7) << std::endl << func(-4); // 56 16

    func--; // special values : 2, -5, -1, 9, 39

    std::cout << func(-5) << std::endl; // 25

    SpecialCustomFunction func2 = !func; // special values : -2, 5, 1, -9, -39

    std::cout << func2(5) << std::endl; // 25


    return 0;
}
```
