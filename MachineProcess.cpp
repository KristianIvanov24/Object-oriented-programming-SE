#include "MachineProcess.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

int MachineProcess::processesCount = 0;

MachineProcess::MachineProcess() {
    this->pid = 0;
    this->processName = new char[8];
    strcpy(this->processName, "unnamed");
    this->memory = 0;
    processesCount++;
}

MachineProcess::MachineProcess(int p, const char* pN, int m) {
    this->pid = p;

    const char* safeName = Validations::validateName(pN);
    this->processName = new char[strlen(safeName) + 1];
    strcpy(this->processName, safeName);

    this->memory = Validations::validateMemory(m);

    processesCount++;
}

MachineProcess::MachineProcess(const MachineProcess& other) {
    this->pid = other.pid;
    this->processName = new char[strlen(other.processName) + 1];
    strcpy(this->processName, other.processName);
    this->memory = other.memory;
    processesCount++;
}

MachineProcess& MachineProcess::operator=(const MachineProcess& other) {
    if (this != &other) {
        this->pid = other.pid;

        delete[] this->processName;
        this->processName = new char[strlen(other.processName) + 1];
        strcpy(this->processName, other.processName);

        this->memory = other.memory;
    }
    return *this;
}

MachineProcess::~MachineProcess() {
    delete[] processName;
    processesCount--;
}

int MachineProcess::getProcessesCount() {
    return processesCount;
}

void MachineProcess::setMemory(int memory) {
    if (memory >= 0)
        this->memory = memory;
}

void MachineProcess::print() const {
    std::cout << "PID: " << pid
        << " | Name: " << processName
        << " | Memory: " << memory << " MB\n";
}

bool MachineProcess::hasMoreMemoryThan(const MachineProcess& other) const {
    return this->memory > other.memory;
}