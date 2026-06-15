#pragma once
#include <iostream>
#include "Validations.h"

class MachineProcess {
private:
    int pid;
    char* processName;
    int memory;
    static int processesCount;

public:
    MachineProcess();
    MachineProcess(int p, const char* pN, int m);
    MachineProcess(const MachineProcess& other);
    MachineProcess& operator=(const MachineProcess& other);
    ~MachineProcess();

    static int getProcessesCount();
    void setMemory(int memory);
    void print() const;
    bool hasMoreMemoryThan(const MachineProcess& other) const;
};
