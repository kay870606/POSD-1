#pragma once

#include <vector>

class Device
{
public:
	void addInputPin(Device *device) {
		iPins.push_back(device);
	}

	virtual int getOutput() = 0;
protected:
	std::vector<Device *> iPins;
};