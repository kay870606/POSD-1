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
	std::string getSimulationResult(std::vector<int> inputVector) {
		std::string str = "Simulation Result:\n" + getTableTopString();

		for (int i = 0; i < iPins.size(); i++) {
			str = str + std::to_string(inputVector[i]) + " ";
			iPins[i]->setValue(inputVector[i]);
		}
		str += "| " + std::to_string(oPins[0]->getOutput()) + "\n";
		return str;
	}

	std::string getTruthTable() {
		std::string str = "Truth table:\n" + getTableTopString();

		for (int i = 0; i < (1 << iPins.size()); i++) {
			int k = 0;
			for (int j = (1 << (iPins.size() - 1)); j > 0; j /= 2) {
				int bit = (i & j ? 1 : 0);
				iPins[k++]->setValue(bit);
				str += std::to_string(bit) + " ";
			}
			str += "| " + std::to_string(oPins[0]->getOutput()) + "\n";
		}
		return str;
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
					int value = stoi(token);

					if (value > 0) {
						int index = value - 1;
						//circuit[i]->addInputPin(circuit[index]);
					}
					else if (value < 0) {
						int index = (int)abs(value) - 1;
						circuit[i]->addInputPin(iPins[index]);
					}
					else break;
				}
			}
			return true;
		}
		else
			return false;
	}

	int getCircuitSize() {
		return circuit.size();
	}

	int getIPinsSize() {
		return iPins.size();
	}

	int getOPinsSize() {
		return oPins.size();
	}
private:
	std::vector<Device *> circuit;
	std::vector<Device *> iPins;
	std::vector<Device *> oPins;

	std::string getTableTopString() {
		std::string str;

		for (int i = 0; i < iPins.size(); i++) {
			str += "i ";
		}
		str += "| o\n";
		for (int i = 1; i <= iPins.size(); i++) {
			str += std::to_string(i) + " ";
		}
		str += "| 1\n";
		for (int i = 0; i < iPins.size(); i++) {
			str += "--";
		}
		str += "+--\n";

		return str;
	}
};
