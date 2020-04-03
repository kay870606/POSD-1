#pragma once

#include "device.h"

class IPin : public Device
{
public:
	void setValue(int number) {
		value = number;
	}

	int getOutput() {
		return value;
	}
private:
	int value;
};