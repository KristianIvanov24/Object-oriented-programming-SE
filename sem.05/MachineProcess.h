#pragma once

class MachineProcess
{
	int pid;
	char* name;
	int memory;
	static size_t count;

	void free();
	void copyFrom(const MachineProcess& other);
	bool isValidMemory(int memory) const;

public:

	MachineProcess();
	MachineProcess(int pid, const char* name, int memory);
	MachineProcess(const MachineProcess& other);
	MachineProcess& operator=(const MachineProcess& other);
	~MachineProcess();

	void setMemory(int memory);
	void print() const;
	static size_t getProcessesCount();
	bool hasMoreMemoryThan(const MachineProcess& other) const;

};