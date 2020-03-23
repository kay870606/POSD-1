#include "pch.h"
#include <vector>
#include "device.h"

class LogicSimulator
{
public:
	std::string getSimulationResult(std::vector<Device *> vec) {

	}
	std::string getTruthTable() {

	}
	bool load(std::string str) {

	}
private:
	std::vector<Device *> circuit;
	std::vector<Device *> iPins;
	std::vector<Device *> oPins;
};