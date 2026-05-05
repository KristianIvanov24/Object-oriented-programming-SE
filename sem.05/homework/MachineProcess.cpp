#include "MachineProcess.h"
#include "constants.h"

using namespace constants;

size_t MachineProcess::processesCount = 0;

MachineProcess::MachineProcess(int pid, const char *name, unsigned memory)
    : pid(ERROR_PID), name(nullptr), memory(MIN_MEMORY)
{
    setPID(pid);
    setName(name);
    setMemory(memory);
    processesCount++;
}

MachineProcess::MachineProcess(const MachineProcess &other)
    : pid(ERROR_PID), name(nullptr), memory(MIN_MEMORY)
{
    copyFrom(other);
    processesCount++;
}

MachineProcess &MachineProcess::operator=(const MachineProcess &other)
{
    if (&other != this)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

MachineProcess::~MachineProcess()
{
    free();
    processesCount--;
}

void MachineProcess::setPID(int pid)
{
    if (pid < MIN_PID)
    {
        this->pid = ERROR_PID;
        return;
    }
    this->pid = pid;
}

void MachineProcess::setName(const char *name)
{
    delete[] this->name;
    if (!name || strlen(name) > MAX_NAME_LENGTH)
    {
        this->name = new char[strlen(ERROR_NAME) + 1];
        strcpy(this->name, ERROR_NAME);
        return;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void MachineProcess::setMemory(unsigned memory)
{
    if (memory > MAX_MEMORY)
    {
        this->memory = MIN_MEMORY;
        return;
    }
    this->memory = memory;
}

int MachineProcess::getPID() const
{
    return pid;
}

char *MachineProcess::getName() const
{
    return name;
}

unsigned MachineProcess::getMemory() const
{
    return memory;
}

void MachineProcess::copyFrom(const MachineProcess &other)
{
    setPID(other.pid);
    setName(other.name);
    setMemory(other.memory);
}

void MachineProcess::free()
{
    delete[] this->name;
    name = nullptr;
    memory = MIN_MEMORY;
    pid = ERROR_PID;
}

size_t MachineProcess::getProcessesCount()
{
    return processesCount;
}

void MachineProcess::print() const
{
    std::cout << "PID: " << pid << " Name: " << name << " Memory: " << memory << std::endl;
}

int MachineProcess::hasMoreMemoryThan(const MachineProcess &other) const
{
    return (memory > other.memory) - (memory < other.memory);
}