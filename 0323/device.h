#ifndef DEVICE_H
#define DEVICE_H

#include <vector>

class Device
{
public:
	virtual void addInputPin(Device *device) {
		iPins.push_back(device);
	}
protected:
	std::vector<Device *> iPins;
};
#endif