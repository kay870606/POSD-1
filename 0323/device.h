#ifndef DEVICE_H
#define DEVICE_H

#include <vector>

class Device
{
public:
	virtual void addInputPin(Device *) = 0;
protected:
	std::vector<Device *> iPins;
};
#endif