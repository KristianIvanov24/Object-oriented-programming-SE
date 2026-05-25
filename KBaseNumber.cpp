#include <iostream>
#include "KBaseNumber.h"
#include "Validations.h"
#include <cstring>
#include <fstream>
#pragma warning(disable : 4996)

long long KBaseNumber::toDecimal() const {
	long long result = 0;
	for (int i = 0; number[i] != '\0'; i++) {
		char c = number[i];
		int digit = (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;
		result = result * base + digit;
	}
	return result;
}

void KBaseNumber::fromDecimal(long long value, int base, char* out) {
	if (value == 0) {
		out[0] = '0';
		out[1] = '\0';
		return;
	}
	char temp[Constants::MAX_LEN + 1];
	int idx = 0;
	while (value > 0) {
		int rem = value % base;
		temp[idx++] = (rem < 10) ? ('0' + rem) : ('A' + rem - 10);
		value /= base;
	}
	for (int i = 0; i < idx; ++i)
		out[i] = temp[idx - 1 - i];
	out[idx] = '\0';
}

KBaseNumber::KBaseNumber() {
	number[0] = '0';
	number[1] = '\0';
	base = 10;
}

KBaseNumber::KBaseNumber(const char* digits, int base){
	if (!Validations::isValidBase(base)) {
		std::cout << "Invalid base. Base set to 10.";
		this->base = 10;
	}
	else {
		this->base = base;
	}
	if (!Validations::isValidLength(digits)) {
		std::cout << "Invalid length. Setting to 0." << std::endl;
		strcpy(number, "0");
	}
	else if (!Validations::isValidNumber(digits, base)) {
		std::cout << "Invalid number. Setting to 0." << std::endl;
		strcpy(number, "0");
	}
	else {
		strcpy(number, digits);
	}
	number[Constants::MAX_LEN] = '\0';
}

int KBaseNumber::compareWith(const KBaseNumber& other) const {
	long long a = toDecimal();
	long long b = other.toDecimal();
	if (a == b) return 0;
	return (a > b) ? 1 : -1;
}

void KBaseNumber::update(const char* digits, int base) {
	if (!Validations::isValidBase(base)) {
		std::cout << "Invalid base." << std::endl;
		return;
	}
	if (!Validations::isValidLength(digits) || !Validations::isValidNumber(digits, base)) {
		std::cout << "Invalid digits." << std::endl;
		return;
	}
	strcpy(number, digits);
	number[Constants::MAX_LEN] = '\0';
	this->base = base;
}

void KBaseNumber::print() const {
	std::cout << number << "(" << base << ")" << std::endl;
}

void KBaseNumber::printConvertedTo(int targetBase) const {
	char out[Constants::MAX_LEN + 1];
	fromDecimal(toDecimal(), targetBase, out);
	std::cout << out << "(" << targetBase << ")" << std::endl;
}

void KBaseNumber::saveToFile(const char* filename) const {
	std::ofstream file(filename);
	if (!file) {
		std::cout << "Cannot open file for writing" << std::endl;
		return;
	}
	file << base << "\n";
	file << number << "\n";
}

void KBaseNumber::readFromFile(const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Cannot open file for reading" << std::endl;
		return;
	}
	file >> base;
	file >> number;
}