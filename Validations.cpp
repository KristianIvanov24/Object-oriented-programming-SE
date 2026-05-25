#include "Validations.h"

const char* Validations::validateName(const char* name) {
    return (name && name[0] != '\0') ? name : "unnamed";
}

int Validations::validateMemory(const int memory) {
    return memory >= 0 ? memory : 0;
}
