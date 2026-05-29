## Задача 01
 
```cpp
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
using namespace std;
 
struct Student {
    string name;
    int grade;
    Student(const string& name, int g) : name(move(name)), grade(g) {
        cout << "S(" << this->name << ") ";
    }
    ~Student() { cout << "~S(" << this->name << ") "; }
};
 
int main() {
    vector<shared_ptr<Student>> v;
    v.push_back(make_shared<Student>("Ivan", 3));
    v.push_back(make_shared<Student>("Maria", 5));
    v.push_back(make_shared<Student>("Petar", 4));
    v.push_back(make_shared<Student>("Georgi", 2));
    v.push_back(v[0]);

    cout << v[0].use_count() << " ";

    erase_if(v, [](const auto& p) {
        return p.use_count() == 2;
    });

    cout << v.size() << " ";

    sort(v.begin(), v.end(),
        [](const auto& a, const auto& b) { return a->grade < b->grade; });

    if (!v.empty()) cout << v.front()->name << " ";
}
```
 
<details>
<summary>Обяснение</summary>

**Изход:**
```
S(Ivan) S(Maria) S(Petar) S(Georgi) 2 4 Georgi ~S(Georgi) ~S(Ivan) ~S(Petar) ~S(Maria)
```
 
Създават се четири обекта:
```
S(Ivan) S(Maria) S(Petar) S(Georgi)
```
 
**Състояние на вектора след `push_back(v[0])`:**
 
| Индекс | Обект | use_count |
|--------|-------|-----------|
| v[0] | Ivan (grade=3) | 2 |
| v[1] | Maria (grade=5) | 1 |
| v[2] | Petar (grade=4) | 1 |
| v[3] | Georgi (grade=2) | 1 |
| v[4] | Ivan (grade=3) | 2 (същия обект като v[0]) |
 
Съответно `v[0].use_count()` печата **`2`**
 
`erase_if` минава вътрешно и изтрива първия shared_ptr към Ivan, което намаля брояча за обекта "Ivan". Така на втория use_count става 1 и не бива изтрит от вектора.
 
| Елемент | use_count == 2? | Изтрива се? |
|---------|-----------------|-------------|
| Ivan (v[0]) | да | **да** |
| Maria (v[1]) | не | не |
| Petar (v[2]) | не | не |
| Georgi (v[3]) | не | не |
| Ivan (v[4]) | **не** (вече =1) | **не** |
 
`v.size()` печата **`4`**
 
**`sort` по `grade` възходящо:**
 
```
v[0] -> Georgi (2)
v[1] -> Ivan (3)
v[2] -> Petar  (4)
v[3] -> Maria  (5)
```
 
`v.front()->name` печата **`Georgi`**

**Деструктори:**
 
```
~S(Georgi) ~S(Ivan) ~S(Petar) ~S(Maria)
```
 
</details>
 
## Задача 02

```c++
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Vehicle {
    string brand;
    Vehicle(string b) : brand(move(b)) { cout << "V(" << brand << ") "; }
    Vehicle(const Vehicle& o) : brand(o.brand) { cout << "CV(" << brand << ") "; }
    virtual ~Vehicle() { cout << "~V(" << brand << ") "; }
    virtual void describe() const { cout << "vehicle "; }
};

struct Car : Vehicle {
    int doors;
    Car(string b, int d) : Vehicle(move(b)), doors(d) { cout << "C(" << doors << ") "; }
    Car(const Car& o) : Vehicle(o), doors(o.doors) { cout << "CC(" << doors << ") "; }
    ~Car() override { cout << "~C(" << doors << ") "; }
    void describe() const override { cout << "car "; }
};

struct Truck : Vehicle {
    Truck(string b) : Vehicle(move(b)) { cout << "T "; }
    void describe() const override { cout << "truck "; }
};

void inspect(Vehicle v) {
    v.describe();
}

Vehicle clone(const Vehicle& v) {
    return v;
}

int main() {
    unique_ptr<Vehicle> x = make_unique<Car>("Toyota", 4);
    unique_ptr<Vehicle> y = make_unique<Truck>("Volvo");

    x->describe();
    y->describe();

    inspect(*x);

    Vehicle z = clone(*x);
    z.describe();

    x = make_unique<Car>("BMW", 2);
    x->describe();
}
```

<details>
<summary>Обяснение</summary>

**Изход:**
```
V(Toyota) C(4) V(Volvo) T car truck CV(Toyota) vehicle ~V(Toyota) CV(Toyota) vehicle V(BMW) C(2) ~C(4) ~V(Toyota) car ~V(Toyota) ~V(Volvo) ~C(2) ~V(BMW)
```

`make_unique<Car>("Toyota", 4)` - първо базовият `Vehicle`, после `Car`:
```
V(Toyota) C(4)
```
`make_unique<Truck>("Volvo")`:
```
V(Volvo) T
```
 
**`x->describe()` и `y->describe()`:**
 
През `unique_ptr` се вика виртуалният метод
```
car truck
```
 
**`inspect(*x)`** — подаване по стойност:
 
`*x` е `Car`, но параметърът е `Vehicle` **object slicing**. Вика се copy constructor на `Vehicle`, не на `Car`:
```
CV(Toyota)
```
`v.describe()` — `v` е `Vehicle`, не `Car`  вика базовия:
```
vehicle
```
В края на `inspect` `v` се унищожава:
```
~V(Toyota)
```
 
**`Vehicle z = clone(*x)`:**
 
`clone` връща `Vehicle` по стойност — пак slicing, copy constructor на `Vehicle`. Компилаторът прилага **copy elision** при return, така че се вика само **едно** `CV`, не две:
```
CV(Toyota)
```
`z.describe()` — `z` е `Vehicle`  базовия:
```
vehicle
```
 
**`x = make_unique<Car>("BMW", 2)`:**
 
Старият Toyota `Car` се унищожава **тук, по средата на main**:
```
~C(4) ~V(Toyota)
```
После се конструира новият BMW:
```
V(BMW) C(2)
```
`x->describe()`:
```
car
```
 
**Деструкции в края на `main`:**
 
Локалните променливи се унищожават в **обратен ред на деклариране**.`z`, после `y`, после `x`. Truck не е дефинирал деструктор, печата се само базовият
```
~V(Toyota)  // z
~V(Volvo)   // y
~C(2) ~V(BMW) // x
```
 
</details>
 

## Задача 03
```c++
#include <iostream>
#include <stdexcept>
using namespace std;

struct X : public runtime_error {
    X() : runtime_error("x_error") { cout << "X "; }
    ~X() { cout << "~X "; }
};

struct Y : public X {
    Y() { cout << "Y "; throw 42; }
    ~Y() { cout << "~Y "; }
};

struct Z : public Y {
    Z() { throw X(); cout << "Z "; }
    ~Z() { cout << "~Z "; }
};

int main() {
    try {
        Z z;
    }
    catch (const exception& e) {
        cout << e.what() << " ";
    }
    catch (int i) {
        cout << "int: " << i << " ";
    }
    catch (...) {
        cout << "unknown ";
    }
}
```

<details>
<summary>Обяснение</summary>

**Изход:**
```
X Y ~X int: 42
```
 
**Конструиране на `Z z`:**
 
`Z` наследява `Y`, `Y` наследява `X`, конструкторите се викат от базовия нагоре:
 
1. `X()` се вика успешно и печата `X`
2. `Y()` се вика, печата `Y` и хвърля `42` (int)
3. `Y` не е конструиран докрай, `~Y` **не се вика**
4. `X` е конструиран успешно, при stack unwinding `~X` **се вика**, печата `~X`
5. `Z()` никога не е започнал, `~Z` **не се вика**, `"Z "` никога не се печата
**`catch` блоковете:**
 
- `catch (const exception& e)` не хваща `int`
- `catch (int i)` хваща `42`, печата `int: 42`  
**Забележка:** `Z::Z()` съдържа `throw X()` след конструктора на `Y`, но понеже `Y()` хвърля пръв, до `throw X()` в `Z` никога не се стига.
 
</details>
