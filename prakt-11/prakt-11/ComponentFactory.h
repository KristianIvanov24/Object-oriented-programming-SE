#pragma once
#include "Component.h"
#include "Memory.h"
#include "CPU.h"

class ComponentFactory
{
public:
	static Component* create_Component();
private:
	static CPU* createCPU();
	static Memory* createMemory();
};

