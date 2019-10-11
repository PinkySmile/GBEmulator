#include <iostream>
#include <chrono>
#include <thread>
#include "ProcessingUnits/CPU.hpp"


#include "ProcessingUnits/GPU.hpp"

int main(int argc, char **argv)
{
	/*if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " rom.gb" << std::endl;
		return EXIT_FAILURE;
	}

	GBEmulator::CPU cpu(argv[1]);

	try {
		while (cpu.executeNextInstruction());
	} catch (std::exception &e) {
		cpu.dump();
		std::cerr << "Fatal error: " << e.what() << std::endl;
	}*/
	GBEmulator::GPU gpu;
	return EXIT_SUCCESS;
}
