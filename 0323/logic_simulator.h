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
		int pow2 = 1;
		for (int i = 1; i <= 10; i++)
			pow2 *= 2;


		for (int i = 1, j = 1; i < pow2; i++, j = i) {
			for (int k = pow2; k >= 1; k /= 2) {
				std::cout << j / k;
				j %= k;
			}
			std::cout << std::endl;
		}
		return "";
	}
	bool load(std::string path) {

		std::fstream  file;

		file.open(path);
		if (file) {
			std::string line;
			int iPinsNumber, gatesNumber;

			std::getline(file, line);
			iPinsNumber = stoi(line);

			std::getline(file, line);
			gatesNumber = stoi(line);

			for (int i = 0; i < gatesNumber; i++) {
				std::getline(file, line);
				std::stringstream ss(line);
				std::string token;

				getline(ss, token, ' ');
				stoi(token);

				while (1)
				{
					getline(ss, token, ' ');
					if (stoi(token) > 0) {
					}
					else if (stoi(token) < 0) {
					}
					else break;

					std::cout << token << std::endl;
				}
			}

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