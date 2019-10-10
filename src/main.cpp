#include <iostream>
#include "ProcessingUnits/CPU.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " rom.gb" << std::endl;
		return EXIT_FAILURE;
	}

	GBEmulator::CPU cpu(argv[1]);

	while (cpu.executeNextInstruction());
	return EXIT_SUCCESS;
}
