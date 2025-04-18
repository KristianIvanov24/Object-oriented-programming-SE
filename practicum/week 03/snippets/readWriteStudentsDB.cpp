#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

struct Student
{
	char* name;
	int gradesCount;
	double averageGrade;
};

struct StudentsDatabase
{
    Student* students;
    size_t count = 0;
};

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

void saveStudentsDatabaseToFile(std::ofstream& f, const StudentsDatabase& db)
{
    f.write((const char*)&db.count, sizeof(size_t));

    for (size_t i = 0; i < db.count; i++)
    {
        saveStudentToFile(f, db.students[i]);
    }
}

StudentsDatabase readStudentsDatabaseFromFile(std::ifstream& f)
{
    StudentsDatabase db;

    f.read((char*)&db.count, sizeof(size_t));

    db.students = new Student[db.count]{};

    for (size_t i = 0; i < db.count; i++)
    {
        db.students[i] = readStudentFromFile(f);
    }
}

void freeStudent(Student& s)
{
    delete[] s.name;
    s.name = nullptr;
    s.averageGrade = s.gradesCount = 0;
}

void freeStudentsDatabase(StudentsDatabase& db)
{
    for (size_t i = 0; i < db.count; i++)
    {
        freeStudent(db.students[i]);
    }

    delete[] db.students;
    db.count = 0;
}

int main()
{
    return 0;
}
