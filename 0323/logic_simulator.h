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
			str += std::to_string(inputVector[i]) + " ";
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
		if (!file) return false;
		else {
			if (iPins.size() != 0) {
				clearVector();
			}
			std::vector<std::vector<double>> vector = getDoubleVector(file);
			std::vector<int> searchOutput(circuit.size(), 1);

			for (int i = 0; i < circuit.size(); i++) {
				int j = 0;
				while (1) {
					double value = vector[i][j++];
					if (value == 0) {
						break;
					}
					else if (value < 0) {
						int index = (int)abs(value) - 1;
						circuit[i]->addInputPin(iPins[index]);
					}
					else {
						int index = (int)floor(value) - 1;
						circuit[i]->addInputPin(circuit[index]);
						searchOutput[index] = 0;
					}
				}
			}
			for (int i = 0; i < circuit.size(); i++) {
				if (searchOutput[i] == 1) {
					oPins.push_back(circuit[i]);
					break;
				}
			}
			return true;
		}
	}

	int getCircuitSize() {
		return (int)circuit.size();
	}

	int getIPinsSize() {
		return (int)iPins.size();
	}

	int getOPinsSize() {
		return (int)oPins.size();
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

	void clearVector() {
		iPins.clear();
		oPins.clear();
		circuit.clear();
	}

	std::vector<std::vector<double>> getDoubleVector(std::fstream&  file) {
		std::string line;
		int iPinsNumber, gatesNumber;

		std::getline(file, line);
		iPinsNumber = stoi(line);
		for (int i = 0; i < iPinsNumber; i++) {
			iPins.push_back(new IPin);
		}

		std::getline(file, line);
		gatesNumber = stoi(line);

		std::vector<std::vector<double>> vector(gatesNumber);

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
				double value = stof(token);
				vector[i].push_back(value);
				if (value == 0)break;
			}
		}
		return vector;
	}
};
