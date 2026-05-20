## std::expected (C++23)

`std::expected<T, E>` е шаблонен тип, който представлява стойност, която може да е или **очаквания резултат от тип `T`**, или **грешка от тип `E`**. Използва се като алтернатива на изключенията и на `std::optional`, когато искаме да върнем или резултат, или смислена информация за причината за неуспех.

### Защо не просто изключения или `std::optional`?

- **Изключенията** са скъпи и не са подходящи за очаквани/чести грешки (напр. "файлът не е намерен", "невалиден вход").
- **`std::optional`** казва само "има или няма стойност", но не обяснява *защо* тя липсва.
- **`std::expected`** позволява да върнем грешка като стойност, без хвърляне на изключение

```c++
#include <expected>
#include <string>

std::expected<int, std::string> parse(const std::string& s) {
    if (s.empty()) {
        return std::unexpected("Empty string");
    }

    return 42; 
}
```

- **`std::unexpected(e)`** — използва се за конструиране на стойност-грешка при връщане.
- **`.has_value()`** — връща `true` ако обектът съдържа очаквана стойност.
- **`.value()`** — връща стойността (хвърля `std::bad_expected_access` ако е грешка).
- **`.error()`** — връща грешката (UB ако има стойност).
- **`operator*` и `operator->`** — достъп до стойността (като при указател).

---

### Пример 1: Деление с грешка

```c++
#include <expected>
#include <iostream>

std::expected<double, std::string> divide(double a, double b) {
    if (b == 0.0) {
        return std::unexpected("Division by zero");
    }
    return a / b;
}

int main() {
    auto expc1 = divide(10.0, 2.0);
    if (expc1.has_value()) {
        std::cout << "Result: " << expc1.value() << std::endl; // 5.0
    }

    auto expc2 = divide(5.0, 0.0);
    if (!expc2.has_value()) {
        std::cout << "Error: " << expc2.error() << std::endl; // Division by zero
    }
}
```

### Верижни операции с `and_then` и `transform`

`std::expected` поддържа функционален стил на работа чрез методи:

- **`.and_then(f)`** — извиква `f` върху стойността, ако има такава; иначе предава грешката нататък. `f` трябва да върне `std::expected`.
- **`.transform(f)`** — трансформира стойността с `f`, ако има такава (като `map`).
- **`.or_else(f)`** — извиква `f` върху грешката, ако има такава.

```c++
#include <expected>
#include <string>
#include <iostream>

std::expected<int, std::string> parsePositive(const std::string& s) {
    try {
        int val = std::stoi(s);
        if (val <= 0) 
            return std::unexpected("Number is not positive");
        return val;
    } catch (...) {
        return std::unexpected("Invalid input: " + s);
    }
}

std::expected<int, std::string> doubleIt(int x) {
    if (x > 1000) return std::unexpected("Too big for doubling");
    return x * 2;
}

int main() {
    auto result = parsePositive("21")
                    .and_then(doubleIt) // 21 -> 42
                    .transform([](int x) { return x + 8; }); // 42 -> 50

    if (result) {
        std::cout << "End result: " << *result << std::endl; // 50
    } else {
        std::cout << "Error: " << result.error() << std::endl;
    }

    // пример с грешка
    auto err = parsePositive("-5")
                 .and_then(doubleIt); // не се изпълнява, грешката се предава
    std::cout << err.error() << std::endl; // числото не е положително
}
```

`and_then` позволява да навързваме операции, всяка от които може да се провали, ако някоя върне грешка, останалите се прескачат автоматично.

---

- Достъпът до `.value()` при обект-грешка хвърля `std::bad_expected_access<E>` — за разлика от директното дерефериране с `*`, което е **undefined behavior**.
- `std::expected` е **value type** — копира се и се мести нормално, включително работи с Rule of Three/Five ако `T` или `E` са класове с ресурси.