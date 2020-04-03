#pragma once

#include "device.h"

class GateNOT : public Device
{
	int getOutput() {
		return 1;
	}
};