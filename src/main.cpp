#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include "ProcessingUnits/CPU.hpp"
#include "CreateInferfaceImpl.hpp"

#if !NODEBUGGER
#include "debugger/debugger.hpp"
#endif

#ifdef __GNUG__
#include <cxxabi.h>
#include <getopt.h>
#endif

#ifdef _WIN32
#include <windows.h>
#elif !defined(__serenity__)
#include <X11/Xlib.h>
#endif

using namespace GBEmulator;

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
	#if !NODEBUGGER
		{"debug",     no_argument,       nullptr, 'd'},
	#endif
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
		std::cout << "Usage: " << argv[0] << " rom.gb [-";
#if !NODEBUGGER
		std::cout << "d";
#endif
		std::cout << "nrmba] [-l <port>] [-c <ip:port>]" << std::endl;
		return EXIT_SUCCESS;
	}

	try {
		args = parseArguments(argc, argv);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "Usage: " << argv[0] << " rom.gb [-";
#if !NODEBUGGER
		std::cout << "d";
#endif
		std::cout << "nrmba] [-l <port>] [-c <ip:port>]" << std::endl;
		return EXIT_FAILURE;
	}

	srand(time(nullptr));

#if !defined(_WIN32) && !defined(__serenity__)
	XInitThreads();
#endif

	std::string path = argv[0];
#ifdef _WIN32
	size_t occurence = path.find_last_of('\\');
#else
	size_t occurence = path.find_last_of('/');
#endif
	Components components = buildComponents(args);
	GBEmulator::CPU cpu(*components.channel1, *components.channel2, *components.channel3, *components.channel4, *components.window, *components.joypad, *components.network, args.error);
#if !NODEBUGGER
	GBEmulator::Debugger::Debugger debugger{occurence == path.size() ? "." : path.substr(0, occurence), cpu, *components.window, *components.joypad};
#endif

	cpu.ignoreBootRom(args.noBootRom);
	cpu.goMaxSpeed(args.maxSpeed);
	try {
		cpu.getCartridgeEmulator().loadROM(args.fileName);
		cpu.init();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

#if !NODEBUGGER
	if (args.debug) {
		int result = debugger.startDebugSession();

		cpu.getCartridgeEmulator().saveRAM();
		return result;
	}
#endif

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
				else
					crashed = cpu.update(0) >= 0;
			}
		}
	};

	while (!end) {
		components.window->render();
		end = components.window->isClosed();
	}

	thread.join();
	cpu.getCartridgeEmulator().saveRAM();
	if (args.profiler)
		cpu.dumpProfiler();

	return EXIT_SUCCESS;
}
