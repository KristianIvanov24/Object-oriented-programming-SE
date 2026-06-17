#include <iostream>
#include <cstring>

/*
7. Реализирайте система за управление на студенти :

Структура / клас Student със следните член - данни :

    име(дължина до 32 символа)
    факултетен номер(число с точно 6 цифри)
    среден успех(реално число)
    специалност(enum class със специалности във ФМИ)

Структура / клас Course със следните член - данни:

масив от студенти(най - много 50)
брой студнети
Реализирайте следните функии :

Приема име, ФН и специалност и създава студент.
Извежда данните за даден студент на стандартния изход.
Извежда данните за студентите в даден курс на стандартния изход.
Приема курс и студент и добавя студента към курса.При достигната максимална бройка студенти в курса да не го добавя.
Приема курс и ФН и премахва студента с този ФН от курса.
Приема курс и указател към функция унарен предикат, приемаща студент.Функцията филтрира всички студенти от курса и извежда данните само на тези, за които предиката дава true.
Приема курс и сортира студентите по подаден бинарен предикат.
*/

const int MAX_NAME_LEN = 32;
const int FN_LEN = 6;
const int MAX_STUDENTS = 50;

enum class Major
{
    SI,
    KN,
    PM,
    IS
};

struct Student
{
    char name[MAX_NAME_LEN];
    int FN;
    double grade;
    Major major;
};

struct Course
{
    Student students[MAX_STUDENTS];
    int numberOfStudents = 0;
};

bool validFN(int FN)
{
    if (FN < 0)
        return false;
    int count = 0;
    do
    {
        count++;
    } while (FN /= 10);
    return count == FN_LEN;
}

Student createStudent(const char *name, int FN, Major major)
{
    Student student{};
    if (!validFN(FN))
    {
        return student;
    }

    strcpy(student.name, name);
    student.FN = FN;
    student.grade = 2;
    student.major = major;

    return student;
}

std::string majorToString(Major major)
{
    switch (major)
    {
    case Major::IS:
        return "IS";
    case Major::KN:
        return "KN";
    case Major::SI:
        return "SI";
    case Major::PM:
        return "PM";
    default:
        return "";
    }
}

void printStudentData(const Student &st)
{
    std::cout << st.name << " " << st.FN << " " << st.grade << " " << majorToString(st.major) << std::endl;
}

void printCourse(const Course &course)
{
    for (int i = 0; i < course.numberOfStudents; i++)
    {
        printStudentData(course.students[i]);
    }
}

void addStudent(Course &course, const Student &student)
{
    if (course.numberOfStudents >= MAX_STUDENTS)
    {
        std::cout << "Max number of students exceeded!" << std::endl;
        return;
    }

    Student *st = &course.students[course.numberOfStudents];
    course.numberOfStudents++;

    strcpy(st->name, student.name);
    st->FN = student.FN;
    st->grade = student.grade;
    st->major = student.major;
}

void removeStudent(Course &course, const int FN)
{
    if (!validFN(FN))
        return;

    int n = course.numberOfStudents;
    for (int i = 0; i < n; i++)
    {
        if (course.students[i].FN == FN)
        {
            course.students[i] = course.students[n - 1];
            course.numberOfStudents--;
            return;
        }
    }

    std::cout << "No student matches the given FN!" << std::endl;
}

void printSelected(const Course &course, bool (*validate)(const Student &st))
{
    for (int i = 0; i < course.numberOfStudents; i++)
    {
        if (validate(course.students[i]))
        {
            printStudentData(course.students[i]);
        }
    }
}

void swap(Student &a, Student &b)
{
    Student temp = a;
    a = b;
    b = temp;
}

void sort(Course &course, bool (*cmp)(const Student &a, const Student &b))
{
    for (int i = 0; i < course.numberOfStudents - 1; i++)
    {
        for (int j = 0; j < course.numberOfStudents - i - 1; j++)
        {
            if (cmp(course.students[j], course.students[j + 1]))
                swap(course.students[j], course.students[j + 1]);
        }
    }
}

int main()
{
    Course course;

    Student s1 = createStudent("abc", 123456, Major::SI);
    Student s2 = createStudent("def", 234567, Major::KN);
    Student s3 = createStudent("hig", 345678, Major::PM);
    Student s4 = createStudent("aac", 485929, Major::PM);

    addStudent(course, s1);
    addStudent(course, s2);
    addStudent(course, s3);

    printCourse(course);

    removeStudent(course, 234567);
    addStudent(course, s4);

    sort(course, [](const Student &a, const Student &b)
         { return strcmp(a.name, b.name) > 0; });
    printCourse(course);

    printSelected(course, [](const Student &st)
                  { return st.major == Major::PM; });

    return 0;
}