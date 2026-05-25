#include "Validation.h"
#include "Constants.h"

bool Validations::isValidGrade(int grade) {
    return grade >= Constants::MIN_GRADE && grade <= Constants::MAX_GRADE;
}

bool Validations::isValidGradeArray(const int* grades, int count) {
    if (grades == nullptr || count <= 0)
        return false;

    for (int i = 0; i < count; i++) {
        if (!isValidGrade(grades[i]))
            return false;
    }
    return true;
}

bool Validations::isValidName(const char* name) {
    if (name == nullptr) return false;
    if (name[0] == '\0') return false;
    return true;
}