#include <iostream>
#include "MachineProcess.h"
#pragma warning(disable: 4996)

size_t MachineProcess::processesCount = 0;

void MachineProcess::setPid(int pid)
{
	this->pid = pid;
}

void MachineProcess::setName(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
void MachineProcess::setMemory(int memory)
{
	this->memory = memory;
}

int MachineProcess::getPid() const
{
	return pid;
}

const char* MachineProcess::getName() const
{
	return name;
}

int MachineProcess::getMemory() const
{
	return memory;
}

size_t MachineProcess::getProcessesCount()
{
	return processesCount;
}

void MachineProcess::copyFrom(const MachineProcess& other)
{
	setPid(other.pid);
	setName(other.name);
	setMemory(other.memory);
}

void MachineProcess::free()
{
	setPid(0);
	delete[] name;
	name = nullptr;
	setMemory(0);
}

MachineProcess::MachineProcess()
{
	setPid(0);
	setName("Unknown");
	setMemory(0);
	processesCount++;
}

MachineProcess::MachineProcess(int pid, const char* name, int memory)
{
	setPid(pid);
	setName(name);
	setMemory(memory);
	processesCount++;
}

MachineProcess::MachineProcess(const MachineProcess& other)
{
	copyFrom(other);
	processesCount++;
	std::cout << "copy ctor()\n";
}

MachineProcess& MachineProcess::operator=(const MachineProcess& other)
{
	if (this == &other)
	{
		return *this;
	}

	free();
	copyFrom(other);
	return *this;
}

MachineProcess::~MachineProcess()
{
	free();
	processesCount--;
}

void MachineProcess::print() const
{
	std::cout << "PID: " << pid << ", Name: " << name << ", Memory: " << memory << "MB\n";
}

bool MachineProcess::hasMoreMemoryThan(const MachineProcess& other) const
{
	return memory > other.memory;
}

