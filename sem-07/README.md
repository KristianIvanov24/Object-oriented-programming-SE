# Ключова дума static. Стринг.

### Static локални променливи 
- държи се в паметта на глобалните/статичните променливи
- променяме продължителността на локалната променлива от automatic (т.е. до края на scope-а) на static (променливата се създава в началото на програмата и се унищожава в края на програмата, точно като глобалните променливи) 
- инициализира се само веднъж - при първото влизане в съответния scope и запазва стойността си дори след като излезе от scope-а

```cpp
int increment()
{
    static int value = 0;
    ++value;
    return value;
}

int main()
{
    std::cout << increment() << std::endl; //1
    std::cout << increment() << std::endl; //2
    std::cout << increment() << std::endl; //3
}
```

### Static функции
- обвързва се с една компилационна единица и не може да се използва от други файлове
- тоест не можем да използваме тази функция в друг .cpp файл


### Static член-данна на клас
- не е обвързана с конкретен обект, а с целия клас
- всички обекти от класа използват една и съща инстанция
- инициализира се извън класа

```cpp
#include <iostream>

class Counter
{
public:
    static int count;
    
    void increment()
{
        count++;
    }
};

int Counter::count = 0; // Инициализация извън класа

int main()
{
    Counter a, b;
    a.increment();
    b.increment();
    std::cout << Counter::count << std::endl; // 2
}
```

### Static член-функция на клас
- не е обвързана с конкретен обект, а с целия клас
- използва се за достъпване на статичните член-данни
- няма указател **this**
- не е нужен обект, за да се достъпи

```cpp
class Test
{
private:
    static int x; 
public:
    static void f()
    { 
        x *= 2; // може да достъпва само статичните член-данни
    }
};

int Test::x = 0; // трябва да я инициализираме извън класа

int main()
{
    Test::f(); // не ни трябва обект
}
```
 
## Задачи
**Задача 1:**
Да се създаде програма за управление на дигитален музикален плейлист. Програмата трябва да поддържа два основни класа: Song и Playlist. Всеки обект от тип Song описва отделна песен със заглавие, изпълнител и продължителност. Класът Playlist управлява списък от песни и предлага възможности за съхраняване и зареждане на плейлист в двоичен файл.

Програмата трябва да поддържа следните функционалности:
- Добавяне на песни към плейлист
- Сливане на два плейлиста
- Извеждане на информация за песен или цял плейлист
- Следене на общата продължителност на всички песни в плейлиста
- Запис и зареждане на плейлист в/от двоичен файл

Пример:
```
=== PLAYLIST MENU ===

1. Add new song
2. View all songs
3. Merge playlists from files
4. Save playlist to file
5. Load playlist from file
6. Show total duration
7. Exit

> 1
Enter song title: Bohemian Rhapsody  
Enter artist: Queen  
Enter duration (in seconds): 354  
Song added!

> 1  
Enter song title: Imagine  
Enter artist: John Lennon  
Enter duration (in seconds): 183  
Song added!

> 4  
Enter filename to save: playlist1.dat  
Playlist saved successfully!

> 1  
Enter song title: Stairway to Heaven  
Enter artist: Led Zeppelin  
Enter duration (in seconds): 482  
Song added!

> 4  
Enter filename to save: playlist2.dat  
Playlist saved successfully!

> 3  
Enter first playlist file: playlist1.dat  
Enter second playlist file: playlist2.dat  
Enter filename for merged playlist: fullplaylist.dat  
Playlists merged successfully into fullplaylist.dat!

> 5  
Enter filename to load: fullplaylist.dat  
Playlist loaded successfully!

> 2  
Current Playlist:
1. Bohemian Rhapsody by Queen [5 min 54 sec]  
2. Imagine by John Lennon [3 min 3 sec]  
3. Stairway to Heaven by Led Zeppelin [8 min 2 sec]

> 6  
Total time of all songs in memory: 16 min 59 sec

> 7  
Exiting...
```

**Задача 2:**
Следвайки добрите ООП практики реализирайте клас **MulString**, предвиден за работа със символни низове, който да поддържа следните оператори:
- оператор *= , който по подадено цяло число k мултиплицира съдържанието на даден стринг k пъти
- оператор * , който по подадени стринг и число връща стринг, чието съдържание е мултиплицираното k пъти съдържание на поддадения стринг
- оператор за записване в поток <<
- оператор != , сравнява два стринга по тежест, връща true <=> двата стринга са с различна тежест
- оператор %= , който като резултат дава обеднинението без повторения на даден стринг с друг
- оператор % , който като резултат дават обеднинението без повторения на два стринга

**Упътване:**
Обединение без повторения на два стринга дефинираме като: Всички символи , които се съдържат в първия и втория стринг, записани еднократно. Наредбата в резултата не е от значение.
Пример : ABCDEFABJ % BCDGHJ -> ABCDEFJGH

Тежест на стринг : сумата от ASCII кодовете на символите на стринга.

Демонстрирайте използването на операторите в кратка main функция
