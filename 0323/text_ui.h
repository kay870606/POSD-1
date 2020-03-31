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

					if (ls->load(path)) {

					}
					else {
						std::cout << "File not found or file format error!!" << std::endl;
					}
				}
				else if (cmd == 2) {

				}
				else if (cmd == 3) {
					std::cout << ls->getTruthTable() << std::endl;
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
