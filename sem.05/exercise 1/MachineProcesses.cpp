#include "MachineProcess.h"
#include <iostream>

int main()
{
    MachineProcess p1(1, "Chrome", 200);
    MachineProcess p2(2, "", -50);

    p1.print();
    p2.print();

    std::cout << "Processes: " << MachineProcess::getProcessesCount() << std::endl;

    p2.setMemory(300);

    if (p2.hasMoreMemoryThan(p1))
        std::cout << "p2 uses more memory\n";

    MachineProcess p3 = p1;

    std::cout << "Processes: " << MachineProcess::getProcessesCount() << std::endl;

    return 0;
}

