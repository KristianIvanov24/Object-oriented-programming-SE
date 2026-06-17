#include "Validations.h"
#include "Constants.h"

bool Validations::isValidK(int k) { return k >= Constants::MIN_K && k <= Constants::MAX_K; }
bool Validations::isValidN(int n) { return n >= 0; }
bool Validations::isValidNumber(int number, int n) { return number >= 0 && number <= n; }