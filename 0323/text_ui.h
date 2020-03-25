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
		int cmd;
		LogicSimulator *ls = new LogicSimulator;

		while (true)
		{
			displayMenu();

			std::cin >> cmd;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.get();
				continue;
			}
			else {
				if (cmd == 1) {

					std::cout << "Please key in a file path: ";

					std::string path;

					std::cin >> path;

					if (ls->load(path)) {
						std::cout << "Circuit: 3 input pins, 1 output pins and 3 gates" << std::endl;
					}
					else {
						std::cout << "File not found or file format error!!" << std::endl;
					}
				}
				else if (cmd == 2) {

				}
				else if (cmd == 3) {

				}
				else if (cmd == 4) {
					std::cout << "Goodbye, thanks for using LS. ";
					break;
				}
			}
		}
	}
};
