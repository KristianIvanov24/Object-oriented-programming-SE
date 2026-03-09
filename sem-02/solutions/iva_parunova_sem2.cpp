#include <iostream>
#include <fstream>

namespace constants {
    const int MAX_STUDENTS = 50;
    const int NAME_SIZE = 51;
    const int FN_SIZE = 11;
}

struct Student {
    char name[constants::NAME_SIZE];
    char fn[constants::FN_SIZE];
    double grade;
};

void cleanName(char* destination, const char* sorce) {
    int i = 0;
    while (sorce[i] == ' ' || sorce[i] == '|') i++;

    int j = 0;
    while (sorce[i] != '\0') {
        destination[j++] = sorce[i++];
    }
    destination[j] = '\0';

    j--;
    while (j >= 0 && (destination[j] == ' ' || destination[j] == '|' || destination[j] == '\n')) {
        destination[j] = '\0';
        j--;
    }
}

bool areEqual(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }
    return s1[i] == s2[i];
}

void printStudent(const Student students[], int count, const char* fn) {
    for (int i = 0; i < count; i++) {
        if (areEqual(students[i].fn, fn)) {
            std::cout << "Name: " << students[i].name
                << ", Faculty Number: " << students[i].fn
                << ", Grade: " <<  students[i].grade << std::endl;
            return;
        }
    }
    std::cout << "Student not found." << std::endl;
}

void updateGrade(Student students[], int count, const char* fn, double newGrade) {
    for (int i = 0; i < count; i++) {
        if (areEqual(students[i].fn, fn)) {
            students[i].grade = newGrade;
            std::cout << "Grade updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "Student not found." << std::endl;
}

void saveToFile(const Student students[], int count, const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "| Name | Faculty Number | Grade |" << std::endl;
    file << "|------|----------------|-------|" << std::endl;
    for (int i = 0; i < count; i++) {
        file << "| " << students[i].name << " | " << students[i].fn << " | "
             << students[i].grade << " |" << std::endl;
    }
    std::cout << "File " << filename << " was saved successfully!" << std::endl;
    file.close();
}

int main() {
    char filename[100];
    std::cout << "Open file: " << std::endl << ">";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    Student students[constants::MAX_STUDENTS];
    int count = 0;
    char buffer[256];

    file.getline(buffer, 256);
    file.getline(buffer, 256);

    while (count < constants::MAX_STUDENTS && !file.eof()) {
        file.ignore(256, '|');
        if (file.eof()) break;

        char temp[100];

        file.getline(temp, 100, '|');
        cleanName(students[count].name, temp);

        file.getline(temp, 100, '|');
        cleanName(students[count].fn, temp);

        file >> students[count].grade;

        file.ignore(256, '\n');

        count++;
    }

    file.close();

    std::cout << "File successfully opened!" << std::endl;

    char command[20];
    while (true) {
        std::cout << "\n> "<<"Chose a command: print, update_grade, save or exit!\n";
        std::cin >> command;

        if (areEqual(command, "print")) {
            char fn[constants::FN_SIZE];
            std::cout << "FN: ";
            std::cin >> fn;
            printStudent(students, count, fn);
        }
        else if (areEqual(command, "update_grade")) {
            char fn[constants::FN_SIZE];
            double g;
            std::cout << "Write down the fn of the student and the new grade: ";
            std::cin >> fn >> g;
            updateGrade(students, count, fn, g);
        }
        else if (areEqual(command, "save")) {
            char outName[100];
            std::cout << "Write the name of the new file: ";
            std::cin >> outName;
            saveToFile(students, count, outName);
        }
        else if (areEqual(command, "exit")) {
            break;
        }
    }

    return 0;
}