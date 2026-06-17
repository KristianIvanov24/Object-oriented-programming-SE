#pragma once
class MachineProcess {
private:
    char* name;
    int pid;
    int mgb;
    static size_t count;

    void free();
    void copyFrom(const MachineProcess& other);

public:
    MachineProcess();
    MachineProcess(int pid, const char* name, int mgb);
    MachineProcess(const MachineProcess& other); 
    MachineProcess& operator=(const MachineProcess& other);
    ~MachineProcess();

    void setName(const char* name);
    void setPid(int pid);
    void setMemory(int mgb);

    void print() const;
    bool hasMoreMemoryThan(const MachineProcess& other) const;

    static size_t getProcessesCount();
};

