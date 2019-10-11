#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "ProcessingUnits/CPU.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " rom.gb" << std::endl;
		return EXIT_FAILURE;
	}

	sf::RenderWindow screen(sf::VideoMode(800, 600), "GameNonBinaire");
	sf::Event event;
	bool cpuHalted = false;
	std::string lastError;
	std::unique_ptr<GBEmulator::CPU> cpu{new GBEmulator::CPU(argv[1], screen)};

	while (screen.isOpen())
	{
		while (screen.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				screen.close();
			if (event.type == sf::Event::KeyPressed && cpuHalted) {
				cpu.reset(new GBEmulator::CPU(argv[1], screen));
				cpuHalted = false;
			}
		}

		if (cpuHalted) {
			screen.clear(sf::Color::Black);
			screen.display();
		} else {
			try {
				cpuHalted = !cpu->executeNextInstruction();
			} catch (std::exception &e) {
				cpu->dump();
				std::cerr << "Fatal error: " << e.what() << std::endl;
				lastError = e.what();
			}
		}
	}

	return EXIT_SUCCESS;
}
