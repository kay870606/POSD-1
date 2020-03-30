#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include "device.h"
#include "i_pin.h"
#include "o_pin.h"
#include "gate_not.h"
#include "gate_and.h"
#include "gate_or.h"

class LogicSimulator
{
public:
	std::string getSimulationResult(std::vector<Device *> DeviceVector) {
		return "";
	}
	std::string getTruthTable() {
		/*int pow2 = 1;
		for (int i = 1; i <= 10; i++)
			pow2 *= 2;


		for (int i = 1, j = 1; i < pow2; i++, j = i) {
			for (int k = pow2; k >= 1; k /= 2) {
				std::cout << j / k;
				j %= k;
			}
			std::cout << std::endl;
		}*/
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

			for (int i = 0; i < iPinsNumber; i++) {//ªì©l¤Æ
				iPins.push_back(new IPin);
			}
			oPins.push_back(new OPin);

			for (int i = 0; i < gatesNumber; i++) {
				std::getline(file, line);
				std::stringstream ss(line);
				std::string token;

				getline(ss, token, ' ');
				int gateType = stoi(token);

				if (gateType == 1)circuit.push_back(new GateAND);
				else if (gateType == 2)circuit.push_back(new GateOR);
				else if (gateType == 3)circuit.push_back(new GateNOT);

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

	int powInt(int base, int exp) {
		int result = 1;

		while (exp--)
		{
			result *= base;
		}
		return result;
	}
};