#pragma once

#include <iostream>

class MachineProcess
{
    int pid;
    char *name;
    unsigned memory;
    static size_t processesCount;

    void copyFrom(const MachineProcess &other);
    void free();

public:
    MachineProcess(int pid, const char *name, unsigned memory);
    MachineProcess(const MachineProcess &other);
    MachineProcess &operator=(const MachineProcess &other);
    ~MachineProcess();

    void setPID(int pid);
    void setName(const char *name);
    void setMemory(unsigned memory);
    int getPID() const;
    char *getName() const;
    unsigned getMemory() const;

    static size_t getProcessesCount();
    void print() const;
    int hasMoreMemoryThan(const MachineProcess &other) const;
};