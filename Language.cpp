#include "Language.h"

const char* languageToString(Language language) {
    switch (language) {
    case Language::CPP:        return "C++";
    case Language::PYTHON:     return "Python";
    case Language::JAVA:       return "Java";
    case Language::CS:         return "C#";
    case Language::JAVASCRIPT: return "JavaScript";
    default:                   return "Unknown";
    }
}