#include "MachineProcess.h"
#include <iostream>
#include "constants.h"
#pragma warning(disable : 4996)

size_t MachineProcess::count = 0;

void MachineProcess::free()
{
    delete[] name;
    name = nullptr;
    pid = 0;
    memory = 0;
    count--;
}

void MachineProcess::copyFrom(const MachineProcess& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    pid = other.pid;
    setMemory(memory);
}

bool MachineProcess::isValidMemory(int memory) const
{
    return memory > 0;
}

MachineProcess::MachineProcess(): pid(0), memory(0)
{
    name = new char[constants::defLength];
    strcpy(name, constants::defName);
    count++;
}

MachineProcess::MachineProcess(int pid, const char* name, int memory)
{
    this->pid = pid;
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    setMemory(memory);
    count++;
}

MachineProcess::MachineProcess(const MachineProcess& other)
{
    free();
    copyFrom(other);
    count++;
}

MachineProcess& MachineProcess::operator=(const MachineProcess& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

MachineProcess::~MachineProcess()
{
    free();
}

void MachineProcess::setMemory(int memory)
{
    if (isValidMemory(memory))
        this->memory = memory;
    else
        this->memory = 0;
}

void MachineProcess::print() const
{
    std::cout << "Process: " << pid << " Name: " << name << " Uses: " << memory << "MB" << std::endl;
}

size_t MachineProcess::getProcessesCount()
{
    return count;
}

bool MachineProcess::hasMoreMemoryThan(const MachineProcess& other) const
{
    return this->memory>other.memory;
}
