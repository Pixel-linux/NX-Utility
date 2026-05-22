#include "NX Utility.h"
#include <iostream>
#include <string>

using namespace std;

// Code by NixxLTE -w-

int main(int argc, char* argv[]) {
	printf("Hello, World!\n");
	for (int i = 1; 1 < argc; i++) {
		std::string arg = argv[i];

		if (arg == "--help") {
			printf("Please start the utility using -- folowed by one of this arguments:\n");
		} 
		else if (arg == "--simple") {

		}
		else if (arg == "--iso") {
			if (i + 1 < argc) {
				std::string file = argv[i + 1];
				
				printf("Using NX custom mode.");
			} else {
				printf("Please use a iso file to enter NX custom mode.");
				return 1;
			}
	}
}
