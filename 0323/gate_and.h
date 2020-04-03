#pragma once

#include "device.h"

class GateAND : public Device
{
public:
	int getOutput() {
		for (int i = 0; i < iPins.size(); i++) {
			if (iPins[i]->getOutput() == 0)
				return 0;
		}
		return 1;
	}
};