#define _CRT_SECURE_NO_WARNINGS
#include "MachineProcess.h"
#include <iostream>
#include <cstring>

void MachineProcess::free()
{
	delete[] name;
	name = nullptr;
}

void MachineProcess::copyFrom(const MachineProcess& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	pid = other.pid;
	mgb = other.mgb;
}

MachineProcess::MachineProcess() :name(nullptr)
{
	setName("Unknown");
	setPid(0);
	setMemory(0);
	count++;
}

MachineProcess::MachineProcess(int pid, const char* name, int mgb) :name(nullptr)
{
	setName(name);
	setPid(pid);
	setMemory(mgb);
	count++;
}

MachineProcess::MachineProcess(const MachineProcess& other) :name(nullptr)
{
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
	count--;
}

void MachineProcess::print() const
{
	std::cout << name << '(' << pid << ')' << ' ' << mgb << std::endl;
}

void MachineProcess::setName(const char* name)
{
	free();
	if (name[0] == '\0')
	{
		this->name = new char[strlen("Unknown") + 1];
		strcpy(this->name, "Unknown");
		return;
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void MachineProcess::setPid(int pid)
{
	if (pid < 0)
	{
		pid = 0;
	}
	this->pid = pid;

}

void MachineProcess::setMemory(int mgb)
{
	if (mgb < 0)
	{
		mgb = 0;
	}
	this->mgb = mgb;
}

size_t MachineProcess::getProcessesCount()
{
	return count;
}

bool MachineProcess::hasMoreMemoryThan(const MachineProcess& other) const
{
	return this->mgb <= other.mgb;
}

size_t MachineProcess::count = 0;