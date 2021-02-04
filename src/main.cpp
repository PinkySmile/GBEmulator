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

struct Components {
	std::unique_ptr<GBEmulator::Network::CableInterface> network;
	std::unique_ptr<GBEmulator::ISound> channel1;
	std::unique_ptr<GBEmulator::ISound> channel2;
	std::unique_ptr<GBEmulator::ISound> channel3;
	std::unique_ptr<GBEmulator::ISound> channel4;
	std::unique_ptr<GBEmulator::Graphics::ILCD> window;
	std::unique_ptr<GBEmulator::Input::JoypadEmulator> joypad;
};

class DummyLCD : public GBEmulator::Graphics::ILCD {
private:
	bool _closed = false;

public:
	void setMaxSize(unsigned int, unsigned int) override
	{}

	void setPixel(unsigned int, unsigned int, const GBEmulator::Graphics::RGBColor &) override
	{}

	void display() override
	{}

	void clear() override
	{}

	bool isClosed() const override
	{
		return this->_closed;
	}

	void close() override
	{
		this->_closed = false;
	}

	void render() override
	{}
};

class DummyJoypadInput : public GBEmulator::Input::JoypadEmulator {
public:
	bool isButtonPressed(GBEmulator::Input::Keys) const noexcept override
	{
		return false;
	}
};

class DummySoundPlayer : public GBEmulator::ISound {
public:
	void setDisabled(bool) override
	{}

	void setPitch(float) override
	{}

	void setWave(std::vector<unsigned char>, unsigned int) override
	{}

	void setVolume(float) override
	{}

	void setSO1Volume(float) override
	{}

	void setSO2Volume(float) override
	{}
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

Components prepareComponents(const Args &args)
{
	Components components;
	auto network = new GBEmulator::Network::BGBProtocolCableInterface();

	components.network.reset(network);
	if (!args.connectIp.empty() && !args.listenPort.empty())
		throw std::invalid_argument("Cannot connect and listen at the same time");
	else if (!args.connectIp.empty())
		network->connect(
			args.connectIp.substr(0, args.connectIp.find(':')),
			std::stoi(args.connectIp.substr(args.connectIp.find(':') + 1))
		);
	else if (!args.listenPort.empty())
		network->host(std::stoi(args.listenPort));

	if (args.noDisplay) {
		components.window = std::make_unique<DummyLCD>();
		components.joypad = std::make_unique<DummyJoypadInput>();
	} else {
		auto window = new GBEmulator::Graphics::LCDSFML{sf::VideoMode{640, 576}, "GBEmulator"};

		components.window.reset(window);
		components.joypad = std::make_unique<GBEmulator::Input::SFMLKeyboardJoypadEmulator>(
			*window,
			std::map<GBEmulator::Input::Keys, sf::Keyboard::Key>{
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
			}
		);
		window->setFramerateLimit(60);
	}

	if (args.noAudio) {
		components.channel1 = std::make_unique<DummySoundPlayer>();
		components.channel2 = std::make_unique<DummySoundPlayer>();
		components.channel3 = std::make_unique<DummySoundPlayer>();
		components.channel4 = std::make_unique<DummySoundPlayer>();
	} else {
		components.channel1 = std::make_unique<GBEmulator::SoundPlayer>();
		components.channel2 = std::make_unique<GBEmulator::SoundPlayer>();
		components.channel3 = std::make_unique<GBEmulator::SoundPlayer>();
		components.channel4 = std::make_unique<GBEmulator::SoundPlayer>();
	}
	return components;
}

int main(int argc, char **argv)
{
	Args args;

	if (argc == 1) {
		std::cout << "Usage: " << argv[0] << " rom.gb [-dnrmba] [-l <port>] [-c <ip:port>]" << std::endl;
		return EXIT_SUCCESS;
	}

	try {
		args = parseArguments(argc, argv);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "Usage: " << argv[0] << " rom.gb [-dnrmba] [-l <port>] [-c <ip:port>]" << std::endl;
		return EXIT_FAILURE;
	}

	srand(time(nullptr));

#ifndef _WIN32
	XInitThreads();
#endif

	std::string path = argv[0];
#ifdef _WIN32
	size_t occurence = path.find_last_of('\\');
#else
	size_t occurence = path.find_last_of('/');
#endif
	Components components = prepareComponents(args);
	GBEmulator::CPU cpu(*components.channel1, *components.channel2, *components.channel3, *components.channel4, *components.window, *components.joypad, *components.network, args.error);
	GBEmulator::Debugger::Debugger debugger{occurence == path.size() ? "." : path.substr(0, occurence), cpu, *components.window, *components.joypad};

	cpu.ignoreBootRom(args.noBootRom);
	cpu.goMaxSpeed(args.maxSpeed);
	try {
		cpu.getCartridgeEmulator().loadROM(args.fileName);
		cpu.init();
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
