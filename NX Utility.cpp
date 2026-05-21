#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	printf("Hello, World!\n");
	for (int i = 1; 1 < argc; i++) {
		std::string arg = argv[i];
		
		if (arg == "--help") {
			printf("Avaiable arguments:\n");
		}
		if (arg == "--iso" && i + 1 < argc) {
			std::string file = argv[i + 1];
		}
	}
}