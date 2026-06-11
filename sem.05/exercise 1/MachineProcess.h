#pragma once

class MachineProcess
{
	int pid;
	char* name;
	int memory;
	static size_t processesCount;

	void setPid(int pid);
	void setName(const char* name);
	void copyFrom(const MachineProcess& other);
	void free();

public:
	void setMemory(int memory);
	MachineProcess();
	MachineProcess(int pid, const char* name, int memory);
	MachineProcess(const MachineProcess& other);
	MachineProcess& operator=(const MachineProcess& other);
	int getPid() const;
	const char* getName() const;
	int getMemory() const;
	static size_t getProcessesCount();
	void print() const;
	bool hasMoreMemoryThan(const MachineProcess& other) const;
	~MachineProcess();
};
