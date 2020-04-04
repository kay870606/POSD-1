#pragma once

#include <vector>

class Device
{
public:
	void addInputPin(Device *device) {
		iPins.push_back(device);
	}

	virtual int getOutput() {
		return 0;
	};

	virtual void setValue(int number) {
		value = number;
	};

protected:
	std::vector<Device *> iPins;

private:
	int value;
};