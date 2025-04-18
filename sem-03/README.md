# Файлове (част 2). Двоични файлове.

## Двоични файлове.

**Файл** - последователност от байтове (числа от 0 до 255). 

Пример: 
| Dec | Hex |
|-----|-----|
| 16 | 10 |
| 255 | FF |

Използваме функциите:

1. .read(char* memoryBlock, size_t size);
2. .write(const char* memoryBlock, size_t size);

Обърнете внимание, че функцията приема **char\***. Ако искаме да запазим променлива от друг вид, ще трябва експлицитно да преобразуваме указателя към тип char* (без значение, че указателят не сочи към елементи от тип char)

### Пример за писане в двоичен файл:
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

    f.write((const char*)&a, sizeof(int)); // the file will show 10 00 00 00

    f.close();
    return 0;
} 
 ```
 
### Пример за четене от двоичен файл:
 
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

### Пример за четене и писане на масив в двоичен файл

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

 
### Примери за запазване на структури във файл.
 
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

### Пример за запазване на масив от структури във файл.
  
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

### Подравняване
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

### Задача

Създайте C++ програма, която чете съобщения от конзолата. Всяко съобщение ще започва с **[ERROR]** или **[INFO]**, последвано от текст на съобщението с **произволна** дължина. Програмата трябва да съхранява тези логове в двоичен файл. Освен това, трябва да предоставя начин за показване само на новите съобщения за грешки от последната проверка.


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
