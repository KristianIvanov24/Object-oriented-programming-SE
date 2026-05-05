#include "ShipClass.h"

const char* shipClassToString(ShipClass shipClass)
{
	switch (shipClass) {
		case ShipClass::bb: return "bb";
		case ShipClass::bc: return "bc";
		default: return "Unknown";
	}
}
