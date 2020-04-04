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
using namespace std;

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
		if (file) {
			std::string line;
			int iPinsNumber, gatesNumber;

			std::getline(file, line);
			iPinsNumber = stoi(line);
			std::getline(file, line);
			gatesNumber = stoi(line);

			for (int i = 0; i < iPinsNumber; i++) {//初始化
				iPins.push_back(new IPin);
			}
			oPins.resize(1);
			//circuit.resize(gatesNumber);

			double vector[100][1024];
			std::vector<int> isoPin(gatesNumber, 1);

			for (int i = 0; i < gatesNumber; i++) {
				std::getline(file, line);
				std::stringstream ss(line);
				std::string token;

				getline(ss, token, ' ');
				int gateType = stoi(token);

				if (gateType == 1)circuit.push_back(new GateAND);
				else if (gateType == 2)circuit.push_back(new GateOR);
				else if (gateType == 3)circuit.push_back(new GateNOT);

				int j = 0;
				while (1)
				{
					getline(ss, token, ' ');
					double value = stof(token);
					vector[i][j] = value;
					if (value == 0)break;
					j++;
				}
			}

			for (int i = 0; i < gatesNumber; i++) {
				int j = 0;
				while (1) {
					double gatePin = vector[i][j];
					if (gatePin == 0) {
						break;
					}
					else if (gatePin < 0) {
						int index = (int)abs(gatePin) - 1;
						circuit[i]->addInputPin(iPins[index]);
					}
					else {
						gatePin = floor(gatePin);
						int index = (int)gatePin - 1;
						isoPin[index] = 0;
						circuit[i]->addInputPin(circuit[index]);
					}
					j++;
				}
			}
			for (int i = 0; i < gatesNumber; i++) {
				if (isoPin[i] == 1) {
					oPins[0] = circuit[i];
					break;
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

	void processIPinsNumber(std::fstream file) {
		std::string line;

		std::getline(file, line);
		int iPinsNumber = stoi(line);
		for (int i = 0; i < iPinsNumber; i++) {
			iPins.push_back(new IPin);
		}
	}

	std::vector<std::vector<int>> fileContentToVector(std::fstream file) {
		std::string line;
		std::vector<std::vector<int>> vector;

		std::getline(file, line);
		int gatesNumber = stoi(line);

		for (int i = 0; i < gatesNumber; i++) {
			std::getline(file, line);
			std::stringstream ss(line);
			std::string token;

			while (1) {
				getline(ss, token, ' ');
				int value = stoi(token);
			}
		}
		return vector;
	}

	void splitStr2Vec(string s, vector<string>& buf, string st)
	{
		int current = 0; //最初由 0 的位置開始找
		int next;
		while (1)
		{
			next = s.find_first_of(st, current);
			if (next != current)
			{
				string tmp = s.substr(current, next - current);
				if (tmp.size() != 0) //忽略空字串
					buf.push_back(tmp);
			}
			if (next == string::npos) break;
			current = next + 1; //下次由 next + 1 的位置開始找起。
		}
	}
};
