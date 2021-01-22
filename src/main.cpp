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
#else
#include <windows.h>
#endif

struct Args
{
	std::string fileName;
	std::string listenPort;
	std::string connectIp;
	bool debug = false;
	bool noDisplay = false;
	bool maxSpeed = false;
	bool noAudio = false;
	bool noBootRom = false;
	bool error = true;
	bool profiler = false;
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
	Args args;
#ifdef __GNUG__
	struct option long_options[] = {
		{"debug",     no_argument,       nullptr, 'd'},
		{"listen",    required_argument, nullptr, 'l'},
		{"connect",   required_argument, nullptr, 'c'},
		{"no-error",  no_argument,       nullptr, 'n'},
		{"profiling", no_argument,       nullptr, 'p'},
		{"max-speed", no_argument,       nullptr, 'm'},
		{"no-display",no_argument,       nullptr, 'b'},
		{"no-audio",  no_argument,       nullptr, 'a'},
		{"no-bootrom",no_argument,       nullptr, 'r'},
		{nullptr,     no_argument,       nullptr, 0}
	};

	while (true) {
		int c = getopt_long(argc, argv, "l:c:dnpmbar", long_options, nullptr);

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
		case 'n':
			args.error = false;
			break;
		case 'p':
			args.profiler = true;
			break;
		case 'b':
			args.noDisplay = true;
			break;
		case 'r':
			args.noBootRom = true;
			break;
		case 'a':
			args.noAudio = true;
			break;
		case 'm':
			args.maxSpeed = true;
			break;
		default:
			throw std::invalid_argument("Invalid argument");
		}
	}
	if (optind != argc - 1)
		throw std::invalid_argument("Too many or no ROM given");
	args.fileName = argv[optind];
#else
	//TODO: Redo a proper getopt implem for MSVC
	if (argc != 2)
		throw std::invalid_argument("Too many or no ROM given");
	args.fileName = argv[1];
#endif
	return args;
}

int main(int argc, char **argv)
{
	Args args;

	if (argc == 1) {
		std::cout << "Usage: " << argv[0] << " rom.gb [-dn] [-l <port>] [-c <ip:port>]" << std::endl;
		return EXIT_SUCCESS;
	}

	try {
		args = parseArguments(argc, argv);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "Usage: " << argv[0] << " rom.gb [-dn] [-l <port>] [-c <ip:port>]" << std::endl;
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
		{GBEmulator::Input::RESET, sf::Keyboard::R},
		{GBEmulator::Input::JOYPAD_A, sf::Keyboard::X},
		{GBEmulator::Input::JOYPAD_B, sf::Keyboard::C},
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
	GBEmulator::CPU cpu(channel1, channel2, channel3, channel4, window, joypad, network, args.error);
	GBEmulator::Debugger::Debugger debugger{occurence == path.size() ? "." : path.substr(0, occurence), cpu, window, joypad};
	sf::View view{sf::FloatRect{0, 0, 160, 144}};

	window.setFramerateLimit(60);
	window.setView(view);

	cpu.ignoreBootRom(args.noBootRom);
	cpu.goMaxSpeed(args.maxSpeed);
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

	if (args.debug) {
		int result = debugger.startDebugSession();

		cpu.getCartridgeEmulator().saveRAM();
		return result;
	}

	cpu.setProfiling(args.profiler);

	bool end = false;
	std::thread thread{
		[&cpu, &end]{
			bool crashed = false;

			while (!end) {
				if (!crashed)
					try {
						cpu.update();
					} catch (std::exception &e) {
						crashed = true;
#ifdef _WIN32
						MessageBox(nullptr, e.what(), getLastExceptionName().c_str(), MB_ICONERROR);
#else
						std::cerr << "Fatal error: " << getLastExceptionName() << ": " << e.what() << std::endl;
#endif
					}
				else {
					cpu.update(0);
					crashed = cpu.getRegisters().pc != 0x0000;
				}
			}
		}
	};

	while (!end) {
		window.render();
		end = window.isClosed();
	}

	thread.join();
	cpu.getCartridgeEmulator().saveRAM();
	if (args.profiler)
		cpu.dumpProfiler();

	return EXIT_SUCCESS;
}
