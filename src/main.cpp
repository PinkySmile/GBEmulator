#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include "ProcessingUnits/CPU.hpp"
#include "CreateInferfaceImpl.hpp"

#ifdef ARDUINO
#include <sys/stat.h>
#endif

#if DEBUGGER == 1
#include "debugger/GUIdebugger.hpp"
#elif DEBUGGER == 2
#include "debugger/debugger.hpp"
#endif

#ifdef __GNUG__
#include <cxxabi.h>
#include <getopt.h>
#endif

#ifdef _WIN32
#include <windows.h>
#elif SFML_IMPL
#include <X11/Xlib.h>
#endif

using namespace GBEmulator;

standard::string getLastExceptionName()
{
#ifdef __GNUG__
	int status;
	char *value;
	standard::string name;

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

bool parseArguments(int argc, char **argv, Args &args)
{
#ifdef __GNUG__
	struct option long_options[] = {
	#if DEBUGGER
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
		{"mode",      required_argument, nullptr, 'g'},
		{nullptr,     no_argument,       nullptr, 0}
	};

	while (true) {
		int c = getopt_long(argc, argv, "l:c:dnpmbag:r", long_options, nullptr);

		if (c == -1)
			break;

		switch (c) {
		case 'd':
			args.debug = true;
			break;
		case 'g':
			if (strcmp(optarg, "auto") == 0)
				args.mode = MODE_AUTO;
			else if (strcmp(optarg, "dmg") == 0)
				args.mode = MODE_DMG;
			else if (strcmp(optarg, "gbc") == 0)
				args.mode = MODE_GBC;
			else
			#ifdef __cpp_exceptions
				throw standard::invalid_argument("Invalid mode: valid modes are 'dmg', 'gbc' or 'auto'");
			#else
				return false;
			#endif
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
		#ifdef __cpp_exceptions
			throw standard::invalid_argument("Invalid argument");
		#else
			return false;
		#endif
		}
	}
	if (optind != argc - 1)
	#ifdef __cpp_exceptions
		throw standard::invalid_argument("Too many or no ROM given");
	#else
		return false;
	#endif
	args.fileName = argv[optind];
#else
	//TODO: Redo a proper getopt implem for MSVC
	if (argc != 2)
		throw standard::invalid_argument("Too many or no ROM given");
	args.fileName = argv[1];
#endif
	return true;
}

void printUsage(char *program)
{
	std::cout << "Usage: " << program << " rom.gb [-";
#if DEBUGGER
	std::cout << "d";
#endif
	std::cout << "nrmba] [-l <port>] [-c <ip:port>] [-g auto|dmg|gbc]" << std::endl;
}

int main(int argc, char **argv)
{
	Args args;

	if (argc == 1) {
		printUsage(argv[0]);
		return EXIT_SUCCESS;
	}

#ifdef __cpp_exceptions
	try {
		parseArguments(argc, argv, args);
	} catch (standard::exception &e) {
		std::cerr << e.what() << standard::endl;
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}
#else
	if (!parseArguments(argc, argv, args)) {
		std::cerr << "Argument parsing failed" << std::endl;
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}
#endif

	srand(time(nullptr));

#if !defined(_WIN32) && SFML_IMPL
	XInitThreads();
#endif

	standard::string path = argv[0];
	Components components = buildComponents(args);
	GBEmulator::CPU cpu(*components.sound, *components.window, *components.joypad, *components.network, args.error);
#if DEBUGGER
#ifdef _WIN32
	size_t occurence = path.find_last_of('\\');
#else
	size_t occurence = path.find_last_of('/');
#endif
	GBEmulator::Debugger::Debugger debugger{occurence == path.size() ? "." : path.substr(0, occurence), cpu, *components.window, *components.joypad};
#endif

	cpu.setGBMode(args.mode);
	cpu.ignoreBootRom(args.noBootRom);
	cpu.goMaxSpeed(args.maxSpeed);
#ifdef __cpp_exceptions
	try {
#endif

#ifdef ARDUINO
		struct stat stats;

		if (stat(path.c_str(), &stats) == -1)
			return EXIT_FAILURE;

		FILE *stream = fopen(args.fileName.c_str(), "rb");
		unsigned char *mem;

		if (!stream)
			return EXIT_FAILURE;

		mem = new unsigned char[stats.st_size];
		memset(mem, 0, stats.st_size);
		fread(mem, 1, stats.st_size, stream);
		fclose(stream);

		cpu.getCartridgeEmulator().loadROM(mem, stats.st_size, true);
#else
		cpu.getCartridgeEmulator().loadROM(args.fileName);
#endif

#ifdef __cpp_exceptions
	} catch (standard::exception &e) {
		std::cerr << e.what() << standard::endl;
		return EXIT_FAILURE;
	}
#endif

	cpu.init();
#if DEBUGGER
	if (args.debug) {
		int result = debugger.startDebugSession();

		cpu.getCartridgeEmulator().saveRAM();
		return result;
	}
#endif

#ifndef ARDUINO
	cpu.setProfiling(args.profiler);
#endif

	bool end = false;
	std::thread thread{
		[&cpu, &end]{
			bool crashed = false;

			while (!end) {
				if (!crashed) {
				#ifdef __cpp_exceptions
					try {
						cpu.update();
					} catch (standard::exception &e)
				#else
					if (cpu.update() == -2)
				#endif
					{
						crashed = true;
					#ifdef __cpp_exceptions
						const char *errorStr = e.what();
					#else
						const char *errorStr = "Updating CPU failed";
					#endif
					#ifdef _WIN32
						MessageBox(nullptr, errorStr, getLastExceptionName().c_str(), MB_ICONERROR);
					#else
						std::cerr << "Fatal error: " << getLastExceptionName() << ": " << errorStr << standard::endl;
					#endif
					}
				} else
					crashed = cpu.update(0) != -1;
			}
		}
	};

	while (!end) {
		components.window->render();
		end = components.window->isClosed();
	}

	thread.join();
	cpu.getCartridgeEmulator().saveRAM();
#ifndef ARDUINO
	if (args.profiler)
		cpu.dumpProfiler();
#endif

	return EXIT_SUCCESS;
}
