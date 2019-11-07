#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include "ProcessingUnits/CPU.hpp"
#include "LCD/LCDSFML.hpp"
#include "Joypad/SfmlKeyboardJoypadEmulator.hpp"
#include "Network/BgbProtocolNetworkInterface.hpp"
#include "debugger/debugger.hpp"

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3 || (argc == 3 && std::strcmp(argv[2], "-d") != 0)) {
		std::cout << "Usage: " << argv[0] << " rom.gb [-d]" << std::endl;
		return EXIT_FAILURE;
	}

	srand(time(nullptr));

	GBEmulator::SoundPlayer channel1;
	GBEmulator::SoundPlayer channel2;
	GBEmulator::SoundPlayer channel3;
	GBEmulator::SoundPlayer channel4;
	GBEmulator::Graphics::LCDSFML window{sf::VideoMode{640, 576}, "GBEmulator"};
	GBEmulator::Input::SFMLKeyboardJoypadEmulator joypad({
		{GBEmulator::Input::JOYPAD_A, sf::Keyboard::A},
		{GBEmulator::Input::JOYPAD_B, sf::Keyboard::Z},
		{GBEmulator::Input::JOYPAD_UP, sf::Keyboard::Up},
		{GBEmulator::Input::JOYPAD_DOWN, sf::Keyboard::Down},
		{GBEmulator::Input::JOYPAD_LEFT, sf::Keyboard::Left},
		{GBEmulator::Input::JOYPAD_RIGHT, sf::Keyboard::Right},
		{GBEmulator::Input::JOYPAD_START, sf::Keyboard::Return},
		{GBEmulator::Input::JOYPAD_SELECT, sf::Keyboard::BackSpace},
		{GBEmulator::Input::ENABLE_DEBUGGING, sf::Keyboard::V}
	});
	GBEmulator::Network::BGBProtocolCableInterface network;
	GBEmulator::CPU cpu(channel1, channel2, channel3, channel4, window, joypad, network);
	GBEmulator::Debugger::Debugger debugger{cpu, window, joypad};

	cpu.getCartridgeEmulator().loadROM(argv[1]);

	sf::View view{sf::FloatRect{0, 0, 160, 144}};

	window.setFramerateLimit(24);
	window.setView(view);

	if (argc == 3)
		return debugger.startDebugSession();

	try {
		while (!window.isClosed())
			cpu.update();
	} catch (std::exception &e) {
		cpu.dump();
		std::cerr << "Fatal error: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
