#pragma once

#include "logic_simulator.h"
#include <iostream>
#include <string>

class TextUI
{
public:
	void displayMenu() {
		std::cout << "1. Load logic circuit file" << std::endl
			<< "2. Simulation" << std::endl
			<< "3. Display truth table" << std::endl
			<< "4. Exit" << std::endl
			<< "Command :";
	}

	void processCommand() {
		try
		{
			LogicSimulator *ls = new LogicSimulator;
			std::string str;
			int cmd;

			while (true) {
				displayMenu();

				std::cin >> str;
				cmd = std::stoi(str);

				if (cmd == 1) {

					std::cout << "Please key in a file path: ";

					std::string path;
					std::cin >> path;

					if (ls->load(path) == false) {
						std::cout << "File not found or file format error!!" << std::endl;
					}
					else {
						std::cout << "Circuit: " << ls->getIPinsSize() << " input pins, " << ls->getOPinsSize()
							<< " output pins and " << ls->getCircuitSize() << " gates" << std::endl << std::endl;
					}
				}
				else if (cmd == 2) {
					if (ls->getIPinsSize() == 0) {
						std::cout << "Please load an lcf file, before using this operation." << std::endl << std::endl;
					}
					else {
						std::vector<int> simulationInput;

						for (int i = 1; i <= ls->getIPinsSize(); i++) {
							std::cout << "Please key in the value of input pin " << i << ": ";

							std::string pinStr;
							std::cin >> pinStr;
							int pinValue;

							pinValue = std::stoi(pinStr);
							if (pinValue != 0 && pinValue != 1) {
								std::cout << "The value of input pin must be 0/1" << std::endl;
								i--;
								continue;
							}
							else {
								simulationInput.push_back(pinValue);
							}
						}
						std::cout << ls->getSimulationResult(simulationInput) << std::endl;
					}
				}
				else if (cmd == 3) {
					if (ls->getIPinsSize() == 0) {
						std::cout << "Please load an lcf file, before using this operation." << std::endl << std::endl;
					}
					else {
						std::cout << ls->getTruthTable() << std::endl;
					}
				}
				else if (cmd == 4) {
					std::cout << "Goodbye, thanks for using LS. ";
					break;
				}
			}
		}
		catch (const std::exception&)
		{
			std::cout << "Error." << std::endl;
		}
	}
};
