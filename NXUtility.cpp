#include "NXUtility.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Code by NixxLTE -w-

std::vector<std::string> simpleISOs;
std::vector<std::string> advancedISOs;

std::string selected;
std::string prefix = "--";
int mode;
int os; // 1 = Windows, 2 = Linux

void selectDrive() {

}

void selectISO() {
	bool exists = false;
	bool valid = false;
	printf("pre-avaiable isos:\n");
	if (mode == 1) { // simple mode
		for (std::string i : simpleISOs) {
			std::cout << i << endl;
		}
	}
	else if (mode == 2) { // advanced mode
		for (std::string i : simpleISOs) {
			std::cout << i << endl;
		}
		for (std::string i : advancedISOs) {
			std::cout << i << endl;
		}
	}
	printf("$\033[3m ");
	std::getline(std::cin, selected);
	printf("\033[0m");
	// check if the selected operating system is valid
	for (std::string i : simpleISOs) {
		if (selected == i) {
			printf("Selected system is valid.");
			exists = true;
			valid = true;
		}
	}
	for (std::string i : advancedISOs) {
		if (selected == i && mode == 2) {
			printf("Selected system is valid.");
			valid = true;
			exists = true;
		} else if (selected == i && mode != 2) {
			printf("Selected system is only avaiable on ADVANCED mode!");
			valid = false;
			exists = true;
			exit(1);
		}
	}
	if (!exists) { // checks if the system doesnt exists in the array
		printf("Selected system does NOT exist.");
		valid = false;
		exit(1);
	} else {
		selectDrive();
	}
}

int main(int argc, char* argv[]) {
	printf("Hello, World!\n");
	#ifdef _WIN32
		os = 1;
		std::cout << "System: WINDOWS";
	#elif __linux__
		os = 2;
		std::cout <<"System: LINUX";
	#endif
	for (int i = 1; 1 < argc; i++) {
		std::string arg = argv[i];

		if (arg == (prefix + "help") || arg == "help") {
			std::cout << "Please start the utility using " << prefix << " followed by one of these arguments:" << endl;
		} 
		else if (arg == (prefix + "simple")) {
			printf("Selected mode: \033[3mSIMPLE\033[0m\n");
			mode = 1;
			selectISO();
		}
		else if (arg == (prefix + "advanced")) {
			printf("Selected mode: \033[3mADVANCED\033[0m\n");
			mode = 2;
			selectISO();
		}
		else if (arg == (prefix + "iso")) {
			if (i + 1 < argc) {
				std::string file = argv[i + 1];
				
				printf("Using NX \033[3mcustom\033[0m mode.");
			} else {
				printf("Please use a iso file to enter NX custom mode.");
				return 1;
			}
		}
	}
}
