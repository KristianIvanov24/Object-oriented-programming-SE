#include <iostream>
#include <fstream>

namespace constants
{
   const size_t MAX_NAME_SIZE = 51;
   const size_t MAX_FACNUM = 11;
   const size_t MAX_FILENAME = 128;
   const size_t MAX_STUDENTS = 50;
   const size_t TEMP = 1024;
   const size_t MAX_COMMAND_SIZE = 128;
}

struct Student
{
    char name[constants::MAX_NAME_SIZE];
    char facNum[constants::MAX_FACNUM];
    double grade;
};

void myStrCpy(char* dest,const char* source)
{
    if (!dest || !source)
        return;
    while (*source)
    {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = '\0';
}

void addStudent(Student& student, size_t& studentCount,const char* name,const char* facNum, double grade)
{
    myStrCpy(student.name, name);
    myStrCpy(student.facNum, facNum);
    student.grade = grade;
    studentCount++;
}

bool readFile(const char* filename,Student students[],size_t& studentCount)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "failed to open file" << std::endl;
        return false;
    }
    char temp[constants::TEMP];
    file.getline(temp, constants::TEMP);
    file.getline(temp, constants::TEMP);
    
    while (!file.eof())
    {
            char name[constants::MAX_NAME_SIZE];
            char facnum[constants::MAX_FACNUM];
            double grade;
            size_t fileIndex = file.tellg();
            file.seekg(++fileIndex);
            file.get(name, constants::MAX_NAME_SIZE, '|');
            fileIndex = file.tellg();
            file.seekg(++fileIndex);
            file.get(facnum, constants::MAX_FACNUM, '|');
            fileIndex = file.tellg();
            file.seekg(++fileIndex);
            file >> grade;
            fileIndex = file.tellg();
            file.getline(temp,constants::TEMP);
            addStudent(students[studentCount], studentCount, name, facnum, grade);
    }
    file.close();
    return true;
}

int findStudent(const Student students[],size_t studentCount, const char* toFind)
{
    for (int i = 0;i < studentCount; i++)
    {
        if(strcmp(students[i].facNum,toFind)==0)
            return i;
    }
    return -1;
}

bool saveFile(const char* filename, const Student students[], size_t studentCount)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "failed to save" << std::endl;
        return false;
    }
    file << "| Name | Faculty Number | Grade |\n";
    file << "|------|----------------|-------|\n";
    for (int i = 0;i < studentCount;i++)
    {
        file << '|' << students[i].name << '|' << students[i].facNum << '|' << students[i].grade << "|\n";
    }
    file.close();
    return true;
}

int main()
{
    std::cout << "Open file:" << std::endl;
    char filename[constants::MAX_FILENAME];
    std::cin >> filename;
    Student students[constants::MAX_STUDENTS];
    size_t studentCount = 0;
    bool success = readFile(filename,students,studentCount);
    if (success)
    {
        char command[constants::MAX_COMMAND_SIZE];
        std::cin >> command;
        while (strcmp(command, "exit") != 0)
        {
            if (strcmp(command, "print")==0)
            {
                char toFind[constants::MAX_FACNUM];
                std::cin >> toFind;
                int index = findStudent(students, studentCount, toFind);
                if (index != -1)
                    std::cout << students[index].name << ' ' << students[index].facNum << ' ' << students[index].grade << std::endl;
                else
                    std::cout << "Not found!" << std::endl;
            }
            else if (strcmp(command, "update_grade") == 0)
            {
                char toFind[constants::MAX_FACNUM];
                std::cin >> toFind;
                double grade;
                std::cin >> grade;
                int index = findStudent(students, studentCount, toFind);
                if (index != -1)
                    students[index].grade = grade;
                else
                    std::cout << "Not found!" << std::endl;
            }
            else if (strcmp(command, "save") == 0)
            {
                std::cin >> filename;
                bool saved = saveFile(filename, students, studentCount);
                if (saved)
                    std::cout << "Saved successfully" << std::endl;
                else
                    std::cout << "Unsuccsessfull save" << std::endl;
            }
            std::cin >> command;
        }
        
    }
}
