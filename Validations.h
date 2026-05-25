#pragma once
#include "Constants.h"

namespace Validations {
	bool isValidNumber(const char* digits, int base);
	bool isValidBase(int base);
	bool isValidLength(const char* digits);
}