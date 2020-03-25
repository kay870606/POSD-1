#pragma once

#include <vector>
#include "device.h"
#include <fstream>
#include <sstream>

class LogicSimulator
{
public:
	std::string getSimulationResult(std::vector<Device *> vec) {

	}
	std::string getTruthTable() {

	}
	bool load(std::string path) {

		std::ifstream  file;

		file.open(path);
		if (file) {
			std::string line;
			std::stringstream ss;
			int iPinsNumber, gatesNumber;

			std::getline(file, line);
			
			ss << line;
			ss >> iPinsNumber;

			std::getline(file, line);
			ss << line;
			ss >> gatesNumber;

			std::cout << iPinsNumber << gatesNumber << "rrrrraa";

			return true;
		}
		else
			return false;
	}
private:
	std::vector<Device *> circuit;
	std::vector<Device *> iPins;
	std::vector<Device *> oPins;
};