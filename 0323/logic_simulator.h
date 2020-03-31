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
		if (iPins.size() == 0)return "Please load an lcf file, before using this operation. ";
		else {
			std::string str = "Truth table:\n";
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

			/*for (int i = 0; i < powInt(2, iPins.size); i++) {
				for (int j = 0, k = i, l = size - 1; j < size; j++) {
					int m = (k / mypow(l)) % 2;
					iPins[j]->setValue(m);
					truthtable = truthtable + to_string(m) + " ";
					l--;
				}
				int m = oPins[0]->getOutput();
				str += "| " + m + "\n";
			}*/
			return str;
		}
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

			std::cout << "Circuit: " << iPins.size() << " input pins, " << oPins.size() << " output pins and " << circuit.size() << " gates" << std::endl << std::endl;

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