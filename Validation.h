#pragma once
#include "Language.h"

namespace Validation {
    bool isValidName(const char* name);
    bool isValidAge(unsigned age);
    bool isValidSalary(unsigned salary);
    bool isValidLang(Language lang);
}