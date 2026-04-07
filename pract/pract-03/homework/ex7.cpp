#include <iostream>
#include <fstream>
#include <cstring>

enum class Major;

const size_t MAX_STUDENTS = 100;
const size_t BUFFER_SIZE = 1024;
const size_t FN_SIZE = 10;
const size_t MAX_NAME_LEN = 20;
const size_t MAX_MAJOR_LEN = 10;
const Major DEFAULT_MAJOR = Major::SI;

enum class Major
{
    KN,
    SI,
    IS,
    PM
};

struct Student
{
    char fn[FN_SIZE + 1];
    char firstName[MAX_NAME_LEN + 1];
    char lastName[MAX_NAME_LEN + 1];
    Major major;
    unsigned year;
    unsigned group;
};

Major stringToMajor(const char *major)
{
    if (strcmp(major, "KN") == 0)
    {
        return Major::KN;
    }
    else if (strcmp(major, "SI") == 0)
    {
        return Major::SI;
    }
    else if (strcmp(major, "IS") == 0)
    {
        return Major::IS;
    }
    else if (strcmp(major, "PM") == 0)
    {
        return Major::PM;
    }
    return DEFAULT_MAJOR;
}

const char *majorToString(Major major)
{
    switch (major)
    {
    case Major::KN:
        return "KN";
    case Major::SI:
        return "SI";
    case Major::IS:
        return "IS";
    case Major::PM:
        return "PM";
    default:
        return "??";
    }
}

Student parse(std::ifstream &file)
{
    Student s;

    file.getline(s.fn, FN_SIZE, ',');
    file.getline(s.firstName, MAX_NAME_LEN, ',');
    file.getline(s.lastName, MAX_NAME_LEN, ',');
    char major[MAX_MAJOR_LEN + 1];
    file.getline(major, MAX_MAJOR_LEN, ',');
    s.major = stringToMajor(major);
    file >> s.year;
    file.ignore();
    file >> s.group;
    file.ignore();

    return s;
}

void filterByCourse(Student *students, size_t studentCount, unsigned year, void (*doSomething)(Student &))
{
    for (size_t i = 0; i < studentCount; i++)
    {
        if (students[i].year == year)
        {
            doSomething(students[i]);
        }
    }
}

bool changeGroup(Student *students, size_t studentCount, const char *fn, unsigned newGroup)
{
    for (size_t i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].fn, fn) == 0)
        {
            students[i].group = newGroup;
            return true;
        }
    }
    return false;
}

bool removeStudent(Student *students, size_t &studentCount, const char *fn)
{
    for (size_t i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].fn, fn) == 0)
        {
            students[i] = students[studentCount - 1];
            studentCount--;
            return true;
        }
    }
    return false;
}

void sort(Student *students, size_t studentCount, bool (*cmp)(const Student &, const Student &))
{
    for (size_t i = 0; i < studentCount - 1; i++)
    {
        for (size_t j = 0; j < studentCount - i - 1; j++)
        {
            if (cmp(students[j], students[j + 1]))
            {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}

void load(const char *fileName, Student *&students, size_t &studentCount)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    size_t capacity = MAX_STUDENTS;
    studentCount = 0;
    while (!file.eof())
    {
        if (studentCount == capacity)
        {
            capacity += MAX_STUDENTS;

            Student *studentsCopy = new Student[capacity];
            std::copy(students, students + studentCount, studentsCopy);

            delete[] students;
            students = studentsCopy;
        }
        students[studentCount++] = parse(file);
    }
}

void save(const char *fileName, const Student *students, size_t studentCount)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    for (size_t i = 0; i < studentCount; i++)
    {
        file << students[i].fn << ',' << students[i].firstName << ',' << students[i].lastName << ','
             << majorToString(students[i].major) << ',' << students[i].year << ',' << students[i].group << std::endl;
    }
}

int main()
{
    char fileName[BUFFER_SIZE];
    std::cin >> fileName;

    Student *students = new Student[MAX_STUDENTS];
    size_t studentCount;

    load(fileName, students, studentCount);

    delete[] students;

    return 0;
}