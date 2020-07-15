#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include "ProcessingUnits/CPU.hpp"
#include "LCD/LCDSFML.hpp"
#include "Joypad/SfmlKeyboardJoypadEmulator.hpp"
#include "debugger/debugger.hpp"
#include "CableLink/BgbProtocolNetworkInterface.hpp"

#ifdef __GNUG__
#include <cxxabi.h>
#include <getopt.h>
#endif

#ifndef _WIN32
#include <X11/Xlib.h>
#endif

struct Args
{
	std::string fileName;
	std::string listenPort;
	std::string connectIp;
	bool debug = false;
};

std::string getLastExceptionName()
{
#ifdef __GNUG__
	int status;
	char *value;
	std::string name;

	auto val = abi::__cxa_current_exception_type();

	if (!val)
		return "No exception";

	value = abi::__cxa_demangle(val->name(), nullptr, nullptr, &status);
	name = value;
	free(value);
	return name;
#else
	return "Unknown exception";
#endif
}

Args parseArguments(int argc, char **argv)
{
	Args args{
		"",
		"",
		"",
		false
	};
	struct option long_options[] = {
		{"debug",   no_argument,       nullptr, 'd'},
		{"listen",  required_argument, nullptr, 'l'},
		{"connect", required_argument, nullptr, 'c'},
		{nullptr,   no_argument,       nullptr, 0}
	};

	while (true) {
		int c = getopt_long(argc, argv, "l:c:d", long_options, nullptr);

		if (c == -1)
			break;

		switch (c) {
		case 'd':
			args.debug = true;
			break;
		case 'c':
			args.connectIp = optarg;
			break;
		case 'l':
			args.listenPort = optarg;
			break;
		default:
			throw std::invalid_argument("Invalid argument");
		}
	}
	if (optind != argc - 1)
		throw std::invalid_argument("Too many or no ROM given");
	args.fileName = argv[optind];
	return args;
}

int main(int argc, char **argv)
{
	Args args;

	try {
		args = parseArguments(argc, argv);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "Usage: " << argv[0] << " rom.gb [-d] [-l <port>] [-c <ip:port>]" << std::endl;
		return EXIT_FAILURE;
	}

	srand(time(nullptr));

#ifndef _WIN32
	XInitThreads();
#endif

	GBEmulator::Network::BGBProtocolCableInterface network;
	GBEmulator::SoundPlayer channel1;
	GBEmulator::SoundPlayer channel2;
	GBEmulator::SoundPlayer channel3;
	GBEmulator::SoundPlayer channel4;
	GBEmulator::Graphics::LCDSFML window{sf::VideoMode{640, 576}, "GBEmulator"};
	GBEmulator::Input::SFMLKeyboardJoypadEmulator joypad(window, {
		{GBEmulator::Input::JOYPAD_A, sf::Keyboard::W},
		{GBEmulator::Input::JOYPAD_B, sf::Keyboard::X},
		{GBEmulator::Input::JOYPAD_UP, sf::Keyboard::Up},
		{GBEmulator::Input::JOYPAD_DOWN, sf::Keyboard::Down},
		{GBEmulator::Input::JOYPAD_LEFT, sf::Keyboard::Left},
		{GBEmulator::Input::JOYPAD_RIGHT, sf::Keyboard::Right},
		{GBEmulator::Input::JOYPAD_START, sf::Keyboard::Return},
		{GBEmulator::Input::JOYPAD_SELECT, sf::Keyboard::BackSpace},
		{GBEmulator::Input::ENABLE_DEBUGGING, sf::Keyboard::V}
	});
	std::string path = argv[0];
#ifdef _WIN32
	size_t occurence = path.find_last_of('\\');
#else
	size_t occurence = path.find_last_of('/');
#endif
	GBEmulator::CPU cpu(channel1, channel2, channel3, channel4, window, joypad, network);
	GBEmulator::Debugger::Debugger debugger{occurence == path.size() ? "." : path.substr(0, occurence), cpu, window, joypad};
	sf::View view{sf::FloatRect{0, 0, 160, 144}};

	window.setFramerateLimit(60);
	window.setView(view);

//	channel3.setDisabled(true);

	try {
		cpu.getCartridgeEmulator().loadROM(args.fileName);
		cpu.init();

		if (!args.connectIp.empty() && !args.listenPort.empty())
			throw std::invalid_argument("Cannot connect and listen at the same time");
		else if (!args.connectIp.empty())
			network.connect(
				args.connectIp.substr(0, args.connectIp.find(':')),
				std::stoi(args.connectIp.substr(args.connectIp.find(':') + 1))
			);
		else if (!args.listenPort.empty())
			network.host(std::stoi(args.listenPort));
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	if (args.debug)
		return debugger.startDebugSession();

	bool end = false;
	std::thread thread{
		[&cpu, &end]{
			while (!end)
				cpu.update();
		}
	};

	try {
		while (!end) {
			window.render();
			end = window.isClosed();
		}
	} catch (std::exception &e) {
		cpu.dump();
		std::cerr << "Fatal error: " << getLastExceptionName() << ": " << e.what() << std::endl;
	}

	thread.join();
	cpu.getCartridgeEmulator().saveRAM();

	return EXIT_SUCCESS;
}
