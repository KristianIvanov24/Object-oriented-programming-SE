##  Потоци. Работа с файлове.

### Потоци
**Поток (stream)** - последователност от байтове данни влизащи в и излизащи от програмата.
* При операциите за вход, байтовете идват от източник за вход (клавиатура, файл, мрежа или друга програма)
* При операциите за изход, байтовете данни излизат от програмата и се "вливат" във външно "устройство" (конзола, файл, мрежа или друга програма)
* Потоците служат като посредници между програмите и самите IO устройства по начин, който освобождава програмиста от боравене с тях.
* Потокът дефинира интерфейс с операции върху него, които не зависят от избора на IO устройство

![image](https://drive.google.com/uc?export=view&id=12uOxL7Det6d8NdzZ71FEfZd3Rtwb1CT_)

  За да извърши вход или изход, една C++ програма:
  * Създава поток;
  * Свързва потока с I/O устройството (напр. конзола, клавиатура, файл, мрежа или друга програма);
  * Извършва операции за вход/изход върху потока;
  * Прекъсва връзка с потока;
  * Освобождава потока;    
  
Видове потоци:
 - Потоци за вход ([istream](https://en.cppreference.com/w/cpp/io/basic_istream)).
 - Потоци за изход ([ostream](https://en.cppreference.com/w/cpp/io/basic_ostream)).
 
![image](https://drive.google.com/uc?export=view&id=1IDRKuGDB1tNMHBYiBM_NE32M4vZW9ETx)


#####  Пример за работа с вход от конзолата. [cin](https://en.cppreference.com/w/cpp/io/cin) (обект от тип istream).
 ```c++
#include <iostream>

int main()
{
	int a, b;
	std::cin >> a >> b; // read two integers from the console input stream
}
 ```
 Четем от стандартния вход.

#####  Пример за работа с поток за изход. [cout](https://en.cppreference.com/w/cpp/io/cout) (обект от тип ostream).
 ```c++
#include <iostream>

int main()
{
	int a = 10;
	int b = 12;
	int c = a + b;

	std::cout << a << " + " << b << " = " << c << std::endl; // write two integers in the console output stream
}
 ```

### Потоци за изход
- **put** указател - сочи към позиция в потока. От там ще започне да се пише при следващата изходна операция.
- форматиран изход
```c++
<поток> << <обект>;
```
- неформатиран изход
    - .put(char) - поставя 1 символ и отмества put
    - .write(const char*, size_t) - използваме при двоични файлове
- позициониране
    - tellp() - връща число, позицията на put указателя
    - seekp(index) - поставя put на позиция index
    - seekp(offset, direction) - поставя put на offset позиция от direction:
        - ios::beg
        - ios::end
        - ios::cur

### Потоци за вход
- **get** указател - сочи към позиция в потока. От там ще започне да се чете при следващата входна операция.
- форматиран вход
```c++
<поток> >> <обект>;
```
- неформатиран вход
    - .get() - чете 1 символ
    - .get(char&) - чете 1 символ
    - .get(char* buffer, size_t N) - чете N символи и ги записва в buffer
    - .get(char* buffer, size_t N, char delimeter) - чете символи и ги записва в buffer, докато достиген брой N или срещне delimeter
    - .get(char* buffer, size_t N, char delimeter = '\n')
    - .ignore() - игнорира 1 символ
    - .read(char*, size_t) - използваме при двоични файлове
- позициониране
    - tellg() - връща число, позицията на get указателя
    - seekg(index) - поставя get на позиция index
    - seekg(offset, direction) - поставя get на offset позиция от direction

### Работа с файлове
**Файлове** - последователност от байтове

#### [Режими на работа](https://en.cppreference.com/w/cpp/io/ios_base/openmode)

 ```c++
ifstream str("file.txt", <режим на работа>).
 ```
Режимът на работа е цяло число. Ако искаме да зададем повече от един ги изреждаме с побитово или ('|').

| ios         | Ефект:                                                                                                                           |    |
|-------------|----------------------------------------------------------------------------------------------------------------------------------|----|
| ios::in     | Отваря файл за извличане.                                                                                                        | 1  |
| ios::out    | Отваряне на файл за вмъкване. Допуска се вмъкване на произволни места във файла. Ако файлът съществува, съдържанието се изтрива. | 2  |
| ios::ate    | Отваря за вмъкване и установява указателя put в края на файла. Допуска вмъкване на произволни места.                             | 4  |
| ios::app    | Отваря за вмъкване и установява указателя put в края на файла                                                                    | 8  |
| ios::trunc  | Ако файлът съществува, съдържанието се изтрива.                                                                                  | 16 |
| ios::binary | Превключва режима от текстов в двоичен                                                                                           | 32 |
 

 ```c++
ofstream file("file.txt", ios::out | ios::app).
 ```
 
#### [Флагове на състоянията на потока](https://en.cppreference.com/w/cpp/io/ios_base/iostate)
| Флаг:| Значение:                                                                      | 
|--------|------------------------------------------------------------------------------|
|bad()   | Има загуба на информация. Някоя операция за четене и писане не е изпълнена. Обикновено при non-recoverable грешки. |
|fail() |Последната входно/изходна операция е невалидна. Обикновено при грешки при форматиране.|
|good() | Всички операции са изпълнени успешно.|
|clear()| Изчиства състоянието на потока (Вече good() ще върне истина).|
| [eof()](https://en.cppreference.com/w/cpp/io/basic_ios/eof) | Достигнат е края на файла. |

**Важно!** eof() се вдига след като прочетем от файл, в който сме достигнали вече края.

Ако bad() е вдигнат, fail() също е вдигнат. 


![image](https://drive.google.com/uc?export=view&id=1sQ5yFepXli_9CRWUxXdeFrT1qLUCmcBF)

#### Работа с поток за вход от текстов файл ([ifstream](https://en.cppreference.com/w/cpp/io/basic_ifstream))
Пример за четене от файл!
 ```c++
#include <iostream>
#include <fstream>

const char FILE_NAME[] = "myFile.txt";

int main()
{
	std::ifstream file(FILE_NAME); // create input file stream associated with myFile.txt

	if (!file.is_open()) 
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	
	int a, b;
	file >> a >> b;

	file.close();
}
```
Пример за прочитане на цялото съдържание файл:
 ```c++
#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;
const char FILE_NAME[] = "myFile.txt";

int main()
{
	std::ifstream file(FILE_NAME);

	if (!file.is_open()) 
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}

	char buff[BUFF_SIZE];
	while (true) 
	{
		file.getline(buff, BUFF_SIZE);

		if (file.eof()) {
			break;
		}

		//do something with the line
		std::cout << buff << std::endl;
	}
	
	file.close();
}
```
#### Работа с поток за изход към текстов файл ([ofstream](https://en.cppreference.com/w/cpp/io/basic_ofstream))
   
 ```c++
#include <iostream>
#include <fstream>

const char FILE_NAME[] = "myFile.txt";

int main()
{
	std::ofstream file(FILE_NAME);  // create output file stream associated with myFile.txt

	if (!file.is_open()) 
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	
	int a = 3;
	int b = 10;

	file << a << " " << b << " " << a + b << std::endl; // write into the output file stream

	file.close();
}
 ```
 
#### Работа със структури и текстови файлове
```c++
#include <iostream>
#include <fstream>

struct Student 
{
    char name[50];
    int age;
    double grade;
};

const char FILE_NAME[] = "students.txt";

int main() 
{
    // serialize struct
    {
        std::ofstream file(FILE_NAME);
        if (!file.is_open()) 
        {
            std::cout << "Error!" << std::endl;
            return -1;
        }
        
        Student s = {"Ivan Ivanov", 21, 5.50};
        file << s.name << std::endl << s.age << std::endl << s.grade << std::endl;
        
        file.close();
    }
    
    // deserialize struct
    {
        std::ifstream file(FILE_NAME);
        if (!file.is_open()) 
        {
            std::cout << "Error!" << std::endl;
            return -1;
        }
        
        Student s;
        file.getline(s.name, 50);
        file >> s.age;
        file >> s.grade;
        
        std::cout << "Name: " << s.name << " Age: " << s.age << " Grade: " << s.grade << std::endl;
        
        file.close();
    }

   return 0;    
}
```

### Двоични файлове.

1. .read(char* memoryBlock, size_t size);
2. .write(const char* memoryBlock, size_t size);

Обърнете внимание, че функцията приема **char\***. Ако искаме да запазим променлива от друг вид, ще трябва експлицитно да преобразуваме указателя към тип char* (без значение, че указателят не сочи към елементи от тип char)

#### Пример за писане в двоичен файл:
 ```c++
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream f("file.bin", std::ios::binary);

    if(!f.is_open())
    {
        return -1;
    }

    int a = 16;

    f.write((const char*)&a, sizeof(int)); // the file will show 10 00 00 00 (little-endian)

    f.close();
    return 0;
} 
 ```
 
#### Пример за четене от двоичен файл:
 
```c++
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream f("file.bin", std::ios::binary);
	
	if(!f.is_open())
	{
	    return -1;
	}
	
	int a;
	f.read((char*)&a, sizeof(int));

	std::cout << a << std::endl;

	f.close();
	
	return 0;
}
 ```

#### Пример за четене и писане на масив в двоичен файл

```c++
#include <iostream>
#include <fstream>

namespace constants
{
    const int MAX_SIZE = 100;    
}

size_t getFileSize(std::ifstream& f)
{
    size_t currentPos = f.tellg();
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();

    f.seekg(currentPos);
    return size;
}

int main()
{
    {
        int arr[constants::MAX_SIZE] = { 1,2,3,4,5 };
        size_t size = 5;

        std::ofstream file("file.bin", std::ios::binary);

        if (!file.is_open())
        {
            return -1;
        }

        file.write((const char*)arr, size * sizeof(int));

        file.close();
    }

    {
        std::ifstream file("file.bin", std::ios::binary);

        if (!file.is_open())
        {
            return -1;
        }

        size_t size = getFileSize(file) / sizeof(int);
        int* arr = new int[size] {};

        file.read((char*)arr, size * sizeof(int));

        file.close();

        for (size_t i = 0; i < size; i++)
        {
            std::cout << arr[i] << ' ';
        }

        delete[] arr; // !!!!!!!!!!!
    }
    return 0;
}
```
 
#### Примери за запазване на структури във файл.
 
- запазване и четене на структура, която не използва динамична памет

```c++
#include <iostream>
#include <fstream>

struct A
{
	bool b;
	int i;
};

int main()
{
	{
		A a = { true, 45 };
		std::ofstream file("file.bin", std::ios::binary);

		if (!file.is_open()) 
		{
			return -1;
		}

		file.write((const char*)&a, sizeof(a));
	}

	{
		A a;
		std::ifstream file("file.bin", std::ios::binary);

		if (!file.is_open()) 
		{
			return -1;
		}

		file.read((char*)&t, sizeof(t));
		std::cout << a.b << " " << a.i << std::endl;
	}
}
```

- запазване и четене на структура с член-данна масив, който не използва динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

struct Student 
{
	char name[25];
	int fn;
	int age;
};

int main()
{
	{
		Student st;
		strcpy(st.name, "Ivan");
		st.fn = 1234;
		st.age = 33;

		std::ofstream file("student.bin", std::ios::binary);

		if (!file.is_open()) 
		{
			std::cout << "Error while writing to binary file!" << std::endl;
			return -1;
		}

		//since the data is grouped in the struct, we can save it like this.
		file.write((const char*)&st, sizeof(st));
	}

	{
		Student st;
		std::ifstream file("student.bin", std::ios::binary);

		if (!file.is_open()) 
		{
			std::cout << "Error while reading from binary file!" << std::endl;
			return -1;
		}

		file.read((char*)&st, sizeof(st));
		std::cout << st.name << " " << st.fn << " " << st.age << std::endl;
	}
}
```
      
- запазване и четене на структура, която използва динамична памет

**NOTE 1**: Всички член-данни се записват една по една! Във файла записваме винаги размера на динамично заделения масив/стринг преди да запишем данните от масива/стринга!

**NOTE 2**: При създаване на обект, ползващ динамчина памет, всички член-данни се четат една по една! Прочита се първо записаният размер на динамично заделения ресурс, заделяме необходимата памет и след това прочитаме съответната информация! 

Подредба на член-данните на обект от тип Student в двоичен файл:
```
<размер-на-името><име><брой-оценки><среден-успех>
```

```c++
#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

struct Student 
{
	char* name;
	int gradesCount;
	double averageGrade;
};

namepace studentManager
{
    Student createStudent(const char* name, int gradesCount, double avGrade) 
    {
    	Student obj;
    
    	size_t nameLen = strlen(name);
    
    	obj.name = new char[nameLen + 1];
    	strcpy(obj.name, name);
    
    	obj.gradesCount = gradesCount;
    	obj.averageGrade = avGrade;
    
    	return obj;
    }
    
    void saveStudentToFile(std::ofstream& f, const Student& st) 
    {
    	size_t nameLen = strlen(st.name);
    
    	f.write((const char*)&nameLen, sizeof(nameLen));  //first we write the size of the name!
    	f.write(st.name, nameLen);
    
    	f.write((const char*)&st.gradesCount, sizeof(st.gradesCount));
    	f.write((const char*)&st.averageGrade, sizeof(st.averageGrade));
    
    }
    
    Student readStudentFromFile(std::ifstream& f) 
    {
    	Student res;
    
    	size_t nameLen;
    
    	f.read((char*)&nameLen, sizeof(nameLen)); //first we read the size of the name!
    
    	res.name = new char[nameLen + 1]; // + 1 for '\0'
    	f.read(res.name, nameLen);
    	res.name[nameLen] = '\0';
    
    	f.read((char*)&res.gradesCount, sizeof(res.gradesCount));
    	f.read((char*)&res.averageGrade, sizeof(res.averageGrade));
    
    	return res;
    }
    
    void freeStudent(Student& s) 
    {
    	delete[] s.name;
    	s.name = nullptr;
    	s.averageGrade = s.gradesCount = 0;
    }
    
    void print(const Student& st) 
    {
    	std::cout << st.name << " " << st.gradesCount << " " << st.averageGrade << std::endl;
    }

}

int main()
{
	{
		Student s1 = studentManager::createStudent("Ivan", 2, 4);
		Student s2 = studentManager::createStudent("Petur", 5, 5.5);

		std::ofstream f1("uni.bin", std::ios::binary);

		if (!f1.is_open()) 
		{
			cout << "Error" << endl;
			return -1;
		}

		studentManager;;saveStudentToFile(f1, s1);
		studentManager::saveStudentToFile(f1, s2);

		studentManager::freeStudent(s1);
		studentManager::freeStudent(s2);
	}

	{
		std::ifstream f2("uni.bin", std::ios::binary);

		if (!f2.is_open()) 
		{
			cout << "Error" << endl;
			return -1;
		}
		
		Student s1 = studentManager::readStudentFromFile(f2);
		Student s2 = studentManager::readStudentFromFile(f2);

		print(s1);
		print(s2);

		studentManager::freeStudent(s1);
		studentManager::freeStudent(s2);
	}
}
```

**NOTE 3**: При запазване на масив от обекти, използващи динамична памет, се записва първо размера на масива, a след това обектите от масива се записват един по един по показания горе начин!

#### Пример за запазване на масив от структури във файл.
  
- запазване на масив от обекти, които не използват динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

namespace constants
{
    const size_t MAX_SIZE = 30;
}

struct Student 
{
	char name[constants::MAX_SIZE];
	char fn[constants::MAX_SIZE];
	double grade;
};

namespace studentManager
{
    void initStudent(Student& st, const char* name, const char* fn, int grade) 
    {
    	strcpy(st.name, name);
    	strcpy(st.fn, fn);
    	st.age = age;
    }
    
    void saveStudentToFile(std::ofstream& file, const Student* students, size_t count) 
    {
    	file.write((const char*)students, count * sizeof(Student));
    }
    
}

int main()
{
	Student* students = new Student[2];
	studentManager::initStudent(students[0], "ivan", "0MI0600000", 5.5);
	studentManager::initStudent(students[1], "petur", "1MI0600000", 4.5);

	std::ofstream file("students.bin", std::ios::binary);

	if (!file.is_open()) 
	{
		std::cout << "Error while opening the file!" << std::endl;
		delete[] students; //!
		return -1;
	}

	saveToFile(file, students, 2);

	delete[] students;
}
```

- четене на масив от обекти, които не използват динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>

namespace constants
{
    const size_t MAX_SIZE = 30;
}

struct Student 
{
	char name[constants::MAX_SIZE];
	char fn[constants::MAX_SIZE];
	double grade;
};

size_t getFileSize(ifstream& f) 
{
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}

void readFromFile(std::ifstream& f, Student*& ptr, size_t& studentsCount) 
{
	size_t sizeOfFile = getFileSize(f);
	studentsCount = sizeOfFile / sizeof(Student);
	ptr = new Student[studentsCount];
	f.read((char*)ptr, sizeOfFile);
}

void printStudent(const Student& student)
{
    std::cout << "Name: " << student.name 
              << ", fn: " << student.fn 
              << ", grade: " << student.grade << std::endl;
}
    

int main()
{
	Student* students;
	size_t studentsCount;
	std::ifstream file("students.bin", std::ios::binary);

	if (!file.is_open()) 
	{
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	readFromFile(file, students, studentsCount);

	for (int i = 0; i < studentsCount; i++) 
	{
		printStudent(students[i]);
	}

	delete[] students;
}
```

#### Подравняване
```c++
#include <iostream>
#include <fstream>

struct A 
{
 	char ch;
 	int i;
};

int main()
{
    std::ofstream f("output.bin", std::ios::binary);
    
    if(!f.is_open()) 
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }
    
    A arr[3] = {{'a', 400},{'b', 500},{'c', 600}};
    
    f.write((const char*)arr, sizeof(arr));
    /*
        file will look like this:
        
        hex: 61 cc cc cc 90 01 00 00 
        dec: a |подравня| 400
               |  ване  |
               
        hex: 62 cc cc cc f4 01 00 00 
        dec: b |подравня| 500
               |  ване  |
               
        hex: 63 cc cc cc 58 02 00 00 
        dec: c |подравня| 600
               |  ване  |
    */
    
    f.close();
}
 ```

##  Задачи
 
**Задача 1**: Напишете функция, която намира големината на файл.

**Задача 2**: Напишете програма, която отпечатва собствения си код.

##  Задачи за допълнителна подготовка
**Задача 1**: Напишете програма, която чете Markdown таблица със студенти със следните полета: **Име** (до 50 символа), **Факултетен номер** (точно 10 символа), **Средна оценка** (реално число).
Със стартирането на програмата потребителят трябва да въведе име на файл, който да бъде зареден в паметта. Всяка таблица да може да съдържа инфромация за най-много 50 студенти.
- Напишете функция, която при подаден факултетен номер отпечатва информация за студента.
- Напишете функция, която по подаден факултетен номер променя оценката на студента.
- Напишете функция, която записва студентите обратно във формат Markdown таблица, за да може програмата да прочете актуализираните данни при следващо стартиране.

*Формат на файла (students.md):*

 ```
| Name | Faculty Number | Grade |
|------|----------------|-------|
| Ivan Ivanov | 0MI0600000 | 5.50 |
| Georgi Georgiev | 1MI0600000 | 4.75 |
```

- Може да тествате как изглежда таблицата на следния линк: https://markdownlivepreview.com 

*Интерфейс в конзолата:*

 ```
Open file:  
>students.md  
File successfully opened!  

>print 0MI0600000  
Name: Ivan Ivanov, Faculty Number: 0MI0600000, Grade: 5.50

>update_grade 0MI0600000 6  
Grade updated successfully.  

>print 0MI0600000  
Name: Ivan Ivanov, Faculty Number: 0MI0600000, Grades: 6

>save students2.md
File students2.md was saved successfully!

```

**Задача 2**: Създайте C++ програма, която чете съобщения от конзолата. Всяко съобщение ще започва с **[ERROR]** или **[INFO]**, последвано от текст на съобщението с **произволна** дължина. Програмата трябва да съхранява тези логове в двоичен файл. Освен това, трябва да предоставя начин за показване само на новите съобщения за грешки от последната проверка.


**1. Четене на вход от конзолата**

- Програмата трябва да чете входа непрекъснато.

- Съобщенията трябва да бъдат във формат:

        [ERROR] текст_на_съобщението
        [INFO] текст_на_съобщението

**2. Съхраняване на логовете**

- Логовете трябва да се записват в двоичен файл (logs.bin).

- Всеки запис трябва да съдържа типа (ERROR или INFO) и текста на съобщението.

**3. Проследяване на последната прочетена позиция**

- Поддържайте втори файл (last_read_position.bin), който съдържа:

    - Името на лог файла.
    - Последната прочетена позиция.
    
***Интерфейс в конзолата:***
```
> show_errors
Nothing new to be shown.

> input
> [INFO] System booting.
> [ERROR] Connection lost.
> [INFO] Upgrade finished.

> show_errors
[ERROR] Connection lost.

> input
> [ERROR] Disk is full.

> show_errors
[ERROR] Disk is full.
```
