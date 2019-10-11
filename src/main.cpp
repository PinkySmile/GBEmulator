#include <iostream>
#include <chrono>
#include <thread>
#include "ProcessingUnits/CPU.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " rom.gb" << std::endl;
		return EXIT_FAILURE;
	}

	GBEmulator::CPU cpu(argv[1]);

	try {
		size_t value = 0;

		while (cpu.executeNextInstruction()) {
			if (value++ % 256 == 0) {
				cpu.dumpRegisters();
				std::cout << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	} catch (std::exception &e) {
		cpu.dump();
		std::cerr << "Fatal error: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
