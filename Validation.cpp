#include "Validation.h"
#include "Constants.h"
#include <cstring>

namespace Validation {
    bool isValidName(const char* name) {
        return name && strlen(name) <= Constants::MAX_NAME_LEN;
    }

    bool isValidAge(unsigned age) {
        return age >= Constants::MIN_AGE;
    }

    bool isValidSalary(unsigned salary) {
        return salary >= Constants::MIN_SALARY && salary <= Constants::MAX_SALARY;
    }

    bool isValidLang(Language lang) {
        return (int)lang >= 0 && (int)lang < (int)Constants::LANGUAGES_COUNT;
    }
}