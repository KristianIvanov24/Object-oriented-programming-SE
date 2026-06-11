#include <iostream>
#include <fstream>
#include <cstring>

namespace constants
{
    const size_t MAX_NAME_LEN = 50;
    const size_t FN_LEN = 10;
    const int MAX_PARAMETERS = 2;
    const size_t MAX_STUDENTS = 50;
    const size_t MAX_FILE_NAME_LEN = 50;
    const size_t BUFFER_SIZE = 1024;
}

struct Student
{
    char name[constants::MAX_NAME_LEN + 1];
    char fn[constants::FN_LEN + 1];
    double grade;
};

Student students[constants::MAX_STUDENTS];
size_t studentCount;
bool endSession = false;

void parse(char *line, Student &student)
{
    char *token = strtok(line, "|");

    token = strtok(nullptr, "|");
    strncpy(student.name, token + 1, constants::MAX_NAME_LEN);
    student.name[constants::MAX_NAME_LEN] = '\0';

    token = strtok(nullptr, "|");
    strncpy(student.fn, token + 1, constants::FN_LEN);
    student.fn[constants::FN_LEN] = '\0';

    token = strtok(nullptr, "|");
    student.grade = atof(token + 1);
}

bool load(const char *fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }
    std::cout << "File successfully opened!" << std::endl;

    char buffer[constants::BUFFER_SIZE];
    file.getline(buffer, constants::BUFFER_SIZE);
    file.getline(buffer, constants::BUFFER_SIZE);

    while (file.getline(buffer, constants::BUFFER_SIZE) && studentCount < constants::MAX_STUDENTS)
    {
        parse(buffer, students[studentCount++]);
    }
    file.close();

    return true;
}

bool save(const char *fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    file << "| Name | Faculty Number | Grade |" << std::endl;
    file << "|------|----------------|-------|" << std::endl;

    for (size_t i = 0; i < studentCount; i++)
    {
        file << "| " << students[i].name << "| " << students[i].fn << "| " << students[i].grade << " |" << std::endl;
    }
    file.close();

    std::cout << "File " << fileName << " was saved successfully!" << std::endl;
    return true;
}

void printStudent(const Student &student)
{
    std::cout << "Name: " << student.name << "Faculty number: " << student.fn << "Grade: " << student.grade << std::endl;
}

size_t find(const char *fn)
{
    for (size_t i = 0; i < studentCount; i++)
    {
        if (strncmp(students[i].fn, fn, constants::FN_LEN) == 0)
        {
            return i;
        }
    }
    return studentCount;
}

void print(const char *fn)
{
    size_t i = find(fn);
    if (i == studentCount)
    {
        std::cout << "Unknown faculty number!" << std::endl;
        return;
    }
    printStudent(students[i]);
}

void updateGrade(const char *fn, double newGrade)
{
    size_t i = find(fn);
    if (i == studentCount)
    {
        std::cout << "Unknown faculty number!" << std::endl;
        return;
    }
    students[i].grade = newGrade;
    std::cout << "Grade updated successfully." << std::endl;
}

bool isValidFileLen(size_t fileLen)
{
    return fileLen <= constants::MAX_FILE_NAME_LEN;
}

void executeCommand(char *line)
{
    char *token = strtok(line, " ");
    if (!token)
    {
        endSession = true;
        return;
    }

    if (strcmp(token, "print") == 0)
    {
        char *fn = strtok(nullptr, " ");
        if (fn)
            print(fn);
    }
    else if (strcmp(token, "update_grade") == 0)
    {
        char *fn = strtok(nullptr, " ");
        char *newGrade = strtok(nullptr, " ");

        if (fn && newGrade)
            updateGrade(fn, atof(newGrade));
    }
    else if (strcmp(token, "save") == 0)
    {
        char *fileName = strtok(nullptr, " ");

        if (fileName)
        {
            save(fileName);
            endSession = true;
        }
    }
}

int main()
{
    std::cout << "Open file: " << std::endl;
    char fileName[constants::MAX_FILE_NAME_LEN];

    std::cout << ">";
    std::cin >> fileName;
    if (!isValidFileLen(strnlen(fileName, constants::MAX_FILE_NAME_LEN)))
    {
        std::cout << "Invalid file name!";
        return 1;
    }
    load(fileName);

    std::cin.ignore();
    char buffer[constants::BUFFER_SIZE];
    while (!endSession)
    {
        std::cout << ">";
        std::cin.getline(buffer, constants::BUFFER_SIZE);
        executeCommand(buffer);
    }

    return 0;
}