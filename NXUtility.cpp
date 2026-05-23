#include "NXUtility.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#ifdef _WIN32
	#include <Windows.h>
#endif

using namespace std;

// Code by NixxLTE -w-

std::string GetTypeWin(std::string letter) {
	UINT type = GetDriveTypeA(letter.c_str());
	if (type == DRIVE_REMOVABLE) return " [REMOVABLE] ";
	if (type == DRIVE_FIXED)     return " [DISK] ";
	return " [UNKNOWN] ";
}
std::string GetTypeLinux(std::string Diskname) {
	std::ifstream file("/sys/block" + Diskname + "/removable");
	int removable;
	file >> removable;
	return (removable == 1) ? " [REMOVABLE] " : " [DISK] ";
}	

std::vector<std::string> simpleISOs = { "ubuntu", "linux mint" };
std::vector<std::string> advancedISOs;

std::string selected;
std::string prefix = "--";
std::string target;
std::string file;
int mode;
int os; // 1 = Windows, 2 = Linux

bool isIsoValid(std::string path) {
	std::ifstream file (path, std::ios::binary);
	if (!file) return false;

	char buffer[5];
	file.seekg(32769);
	file.read(buffer, 5);

	std::string signature(buffer, 5);
	return (signature == "CD001");
}

void Write() {
	#ifdef __linux__
		system(("dd if=" + file + "of=" + selected + "bs=4M status=progress conv=fsync").c_str());
	#elif _WIN32
		
	#endif
}

void selectDrive() {
	// show avaiable drives
	printf("\nDrives:\n");
	#ifdef __linux__
		for (const auto& entry : std::filesystem::directory_iterator("/sys/block/")) {
			std::string name = entry.path().filename().string();
			std::string info = GetTypeLinux(name);
			if (name.find("sd") == 0 || name.find("nvme") == 0) {
				std::cout << "/dev/" << name << info << std::endl;
			}
    	}
	#elif _WIN32
		char drives[256];
		DWORD size = GetLogicalDriveStringsA(sizeof(drives), drives);

		for (int i = 0; i < size; i += 4) {
			if (drives[i] != '\0') {
				std::string info = GetTypeWin(&drives[i]);
				std::cout << &drives[i] << info << std::endl;
			}
		}
	#endif
	printf("Select a drive to burn the ISO $\033[3m ");
	std::getline(std::cin, selected);
	printf("\033[0m");
	target = selected;

	printf("Are you sure? [Y/N] ");
	std::getline(std::cin, selected);
	if (selected == "y" || selected == "Y") {
		Write();
	}
	else if (selected == "n" || selected == "N") {
		printf("trying again...");
		selectDrive();
	}
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
			printf("Selected system is valid.\n");
			exists = true;
			valid = true;
		}
	}
	for (std::string i : advancedISOs) {
		if (selected == i && mode == 2) {
			printf("Selected system is valid,\n");
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
		// std::cout << "System: WINDOWS";
	#elif __linux__
		os = 2;
		// std::cout << "System: LINUX";
	#endif
	for (int i = 1; 1 < argc; i++) {
		std::string arg = argv[i];

		if (arg == (prefix + "help") || arg == "help") {
			std::cout << "Please start the utility using " << prefix << " followed by one of these arguments:" << endl;
		} 
		else if (arg == (prefix + "simple")) {
			printf("Selected mode: \033[3mSIMPLE\033[0m\n\n");
			mode = 1;
			selectISO();
		}
		else if (arg == (prefix + "advanced")) {
			printf("Selected mode: \033[3mADVANCED\033[0m\n\n");
			mode = 2;
			selectISO();
		}
		else if (arg == (prefix + "iso")) {
			if (i + 1 < argc) {
				file = argv[i + 1];
				
				printf("Using NX \033[3mcustom\033[0m mode.\n");
				if (isIsoValid(file)) {
					printf("\nSelected ISO is valid!\n");
					selectDrive();
				} else {
					printf("\nSelected ISO is NOT valid");
					exit(1);
				}
			} else {
				printf("Please use a iso file to enter NX custom mode.");
				return 1;
			}
		}
	}
}
