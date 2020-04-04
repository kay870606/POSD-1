#pragma once

#include "device.h"

class GateNOT : public Device
{
public:
	int getOutput() {
		if (iPins[0]->getOutput() == 0)
			return 1;
		else
			return 0;
	}
};