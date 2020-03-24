#pragma once

#include "logic_simulator.h"
#include <iostream>

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

	}
};