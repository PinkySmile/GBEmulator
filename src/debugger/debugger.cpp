/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.cpp
*/

#ifndef _WIN32
#	include <sys/select.h>
typedef fd_set FD_SET;
#else
#	include <windows.h>
#endif

#include <iostream>
#include <iomanip>
#include "debugger.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"
#include "../LCD/LCDSFML.hpp"

namespace GBEmulator::Debugger
{
	const std::vector<unsigned char> Debugger::_instrSize = {
		1, 3, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 2, 1,
		2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
		2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
		2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 3, 2, 3, 3, 2, 1,
		1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 1, 2, 1,
		2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 3, 1, 1, 1, 2, 1,
		2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 3, 1, 1, 1, 2, 1
	};

	Debugger::Debugger(const std::string &programPath, GBEmulator::CPU &cpu, GBEmulator::Graphics::ILCD &window, GBEmulator::Input::JoypadEmulator &input) :
		_cpu(cpu),
		_window(window),
		_input(input)
	{
		this->_memBeg = 0x0000;
		this->_oldpcs.resize(64, 00);

		this->_font.loadFromFile(programPath + "/courier.ttf");

		this->_memory.setFont(this->_font);
		this->_memory.setCharacterSize(14);
		this->_memory.setFillColor(sf::Color::Black);
		this->_memory.setPosition(300, 10);

		this->_registers.setFont(this->_font);
		this->_registers.setCharacterSize(14);
		this->_registers.setFillColor(sf::Color::Black);
		this->_registers.setPosition(10, 10);
	}


	std::vector<std::string> Debugger::_splitCommand(const std::string &line)
	{
		std::vector<std::string> result;
		std::stringstream stream;
		char quote = 0;

		for (auto c : line) {
			if (c == quote)
				quote = 0;
			else if (c == '"')
				quote = '"';
			else if (c == '\'')
				quote = '\'';
			else if (quote == 0 && c == ' ') {
				result.push_back(stream.str());
				stream.str("");
			} else
				stream << c;
		}

		result.push_back(stream.str());
		return result;
	}

	void Debugger::_setVar(const std::string &name, unsigned short value)
	{
		if (name == "a")
			 this->_cpu._registers.a = value;
		else if (name == "b")
			 this->_cpu._registers.b = value;
		else if (name == "c")
			 this->_cpu._registers.c = value;
		else if (name == "d")
			 this->_cpu._registers.d = value;
		else if (name == "e")
			 this->_cpu._registers.e = value;
		else if (name == "h")
			 this->_cpu._registers.h = value;
		else if (name == "l")
			 this->_cpu._registers.l = value;
		else if (name == "f")
			 this->_cpu._registers.f = value;
		else if (name == "af")
			 this->_cpu._registers.af = value;
		else if (name == "bc")
			 this->_cpu._registers.bc = value;
		else if (name == "de")
			 this->_cpu._registers.de = value;
		else if (name == "hl")
			 this->_cpu._registers.hl = value;
		else if (name == "pc")
			this->_displayCurrentLine();
		else if (name == "sp")
			 this->_cpu._registers.sp = value;
		else {
			size_t address = std::stoul(name, nullptr, 16);

			if (address > UINT16_MAX)
				throw std::invalid_argument("stoul");
			this->_cpu.write(address, value);
		}
	}

	void Debugger::_dispVar(const std::string &name)
	{
		if (name == "a")
			std::cout << "a: " << Instructions::intToHex(this->_cpu._registers.a) << std::endl;
		else if (name == "b")
			std::cout << "b: " << Instructions::intToHex(this->_cpu._registers.b) << std::endl;
		else if (name == "c")
			std::cout << "c: " << Instructions::intToHex(this->_cpu._registers.c) << std::endl;
		else if (name == "d")
			std::cout << "d: " << Instructions::intToHex(this->_cpu._registers.d) << std::endl;
		else if (name == "e")
			std::cout << "e: " << Instructions::intToHex(this->_cpu._registers.e) << std::endl;
		else if (name == "h")
			std::cout << "h: " << Instructions::intToHex(this->_cpu._registers.h) << std::endl;
		else if (name == "l")
			std::cout << "l: " << Instructions::intToHex(this->_cpu._registers.l) << std::endl;
		else if (name == "f")
			std::cout << "f: " << Instructions::intToHex(this->_cpu._registers.f) << std::endl;
		else if (name == "af")
			std::cout << "af: " << Instructions::intToHex(this->_cpu._registers.af, 4) << std::endl;
		else if (name == "bc")
			std::cout << "bc: " << Instructions::intToHex(this->_cpu._registers.bc, 4) << std::endl;
		else if (name == "de")
			std::cout << "de: " << Instructions::intToHex(this->_cpu._registers.de, 4) << std::endl;
		else if (name == "hl")
			std::cout << "hl: " << Instructions::intToHex(this->_cpu._registers.hl, 4) << std::endl;
		else if (name == "pc")
			this->_displayCurrentLine();
		else if (name == "sp")
			std::cout << "sp: " << Instructions::intToHex(this->_cpu._registers.sp, 4) << std::endl;
		else {
			size_t address = std::stoul(name, nullptr, 16);

			if (address > UINT16_MAX)
				throw std::invalid_argument("stoul");
			std::cout << "$" << Instructions::intToHex(address, 4) << ": " << Instructions::intToHex(this->_cpu.read(address)) << std::endl;
			this->_displayCurrentLine(address);
		}
	}

	bool Debugger::processCommandLine(const std::string &line)
	{
		std::vector<std::string> args = _splitCommand(line);

		if (line.empty())
			args = {this->_lastCmd};
		this->_lastCmd = args[0];
		if (args[0] == "break") {
			if (args.size() == 1) {
				std::cout << "There are " << this->_breakPoints.size() << " breakpoint(s)" << std::endl;
				for (unsigned i = 0; i < this->_breakPoints.size(); i++)
					std::cout << "Breakpoint #" << i << " at $" << Instructions::intToHex(this->_breakPoints[i], 4) << std::endl;
				return false;
			}
			auto add = std::stoul(args.at(1), nullptr, 16);
			auto it = std::find(this->_breakPoints.begin(), this->_breakPoints.end(), add);

			if (it != this->_breakPoints.end()) {
				std::cout << "Breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << " removed" << std::endl;
				this->_breakPoints.erase(it);
			} else {
				std::cout << "Added breakpoint #" << this->_breakPoints.size() << " at $" << Instructions::intToHex(add, 4) << std::endl;
				this->_breakPoints.push_back(add);
			}
		} else if (args[0] == "cbreak") {
			if (args.size() == 1) {
				std::cout << "There are " << this->_condBreakPoints.size() << " conditional breakpoint(s)" << std::endl;
				for (unsigned i = 0; i < this->_condBreakPoints.size(); i++)
					std::cout << "Conditional breakpoint #" << i << " when (" << this->_condBreakPoints[i]->tostring() << ") != 0" << std::endl;
				return false;
			}

			if (args[1] == "remove") {
				if (args.size() != 3) {
					std::cout << "Expected 2 arguments" << std::endl;
					return false;
				}

				auto add = std::stoul(args.at(2), nullptr, 16);

				if (add >= this->_condBreakPoints.size()) {
					std::cout << "Invalid conditional breakpoints id." << std::endl;
					std::cout << add << " is greater than the number of conditional breakpoints (" << add << " >= " << this->_condBreakPoints.size() << ")" << std::endl;
					return false;
				}

				auto it = this->_condBreakPoints.begin() + add;

				std::cout << "Removed conditional breakpoint #" << (it - this->_condBreakPoints.begin()) << " when (" << (*it)->tostring() << ") != 0" << std::endl;
				this->_condBreakPoints.erase(it);
				return false;
			}

			std::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << "Added breakpoint #" << this->_breakPoints.size() << " when (" << op->tostring() << ") != 0" << std::endl;
				this->_condBreakPoints.push_back(op);
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		} else if (args[0] == "help") {
			std::cout << "help" << std::endl;
			std::cout << "jump <addr>" << std::endl;
			std::cout << "next" << std::endl;
			std::cout << "step" << std::endl;
			std::cout << "continue" << std::endl;
			std::cout << "ram [<border1> <border2>]" << std::endl;
			std::cout << "print <value>" << std::endl;
			std::cout << "registers" << std::endl;
			std::cout << "break <addr>" << std::endl;
		} else if (args[0] == "registers")
			this->_cpu.dumpRegisters();
		else if (args[0] == "oldpc") {
			for (auto pc : this->_oldpcs)
				std::cout << "$" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << pc << std::endl;
		} else if (args[0] == "print") {
			std::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << std::dec << op->getValue(this->_cpu) << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		} else if (args[0] == "printx") {
			std::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << "$" << std::hex << static_cast<unsigned>(op->getValue(this->_cpu)) << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		} else if (args[0] == "printo") {
			std::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << "&" << std::oct << static_cast<unsigned>(op->getValue(this->_cpu)) << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		} else if (args[0] == "printb") {
			std::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);
				auto val = static_cast<unsigned>(op->getValue(this->_cpu));
				std::stringstream s;

				std::cout << "%";
				do {
					s << (val & 1U);
					val >>= 1U;
				} while (val);

				auto str = s.str();

				for (int i = str.length()-1; i>=0; i--)
					std::cout << str[i];
				std::cout << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		} else if (args[0] == "set") {
			this->_setVar(args.at(1), std::stoul(args.at(2), nullptr, 16));
			this->_dispVar(args.at(1));
		} else if (args[0] == "slow") {
			this->_cpu.update();
			this->_oldpcs.erase(this->_oldpcs.begin());
			this->_oldpcs.push_back(this->_cpu._registers.pc);
			this->_rate = 0.001;
			return true;
		} else if (args[0] == "ram") {
			if (args.size() == 1)
				return this->_cpu.dumpMemory(), false;

			size_t i = std::stoul(args.at(1), nullptr, 16);
			size_t end = std::stoul(args.at(2), nullptr, 16);

			i -= i % 0x10;
			end += 0x10 - end % 0x10;
			for (; i < end; i += 0x10) {
				std::cout << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << i << ":  ";
				for (unsigned j = 0; j < 0x10 && j + i < end; j++)
					std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(this->_cpu.read(j + i)) << " ";
				for (int j = 0; j < static_cast<int>(i - end + 0x10); j++)
					std::cout << "   ";
				std::cout << " ";
				for (unsigned j = 0; j < 0x10 && j + i < end; j++)
					std::cout << static_cast<char>(std::isprint(this->_cpu.read(j + i)) ? this->_cpu.read(j + i) : '.');
				for (int j = 0; j < static_cast<int>(i - end + 0x10); j++)
					std::cout << " ";
				std::cout << std::endl;
			}
		} else if (args[0] == "jump") {
			this->_cpu._registers.pc = std::stoul(args.at(1), nullptr, 16);
			this->_displayCurrentLine();
		} else if (args[0] == "next") {
			unsigned short address = this->_cpu._registers.pc;

			while ((this->_cpu._registers.pc <= address || this->_cpu._registers.pc > address + 3) && !this->checkBreakPoints() && !this->checkConditionalBreakPoints()) {
				this->_cpu.update();
				this->_oldpcs.erase(this->_oldpcs.begin());
				this->_oldpcs.push_back(this->_cpu._registers.pc);
				if (this->_timer++ == 30)
					this->_timer = 0;
				if (this->_timer == 0 && this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
					this->_displayCurrentLine();
					break;
				}
			}
			this->_displayCurrentLine();
		} else if (args[0] == "step") {
			this->_cpu.update();
			this->_oldpcs.erase(this->_oldpcs.begin());
			this->_oldpcs.push_back(this->_cpu._registers.pc);
			this->_displayCurrentLine();
		} else if (args[0] == "continue") {
			this->_cpu.update();
			this->_oldpcs.erase(this->_oldpcs.begin());
			this->_oldpcs.push_back(this->_cpu._registers.pc);
			return true;
		} else if (args[0] == "where")
			this->_displayCurrentLine();
		else
			throw CommandNotFoundException("Cannot find the command '" + args[0] + "'");
		return false;
	}

	Debugger::~Debugger()
	{
		this->_window.close();
		if (this->_cpuThread.joinable())
			this->_cpuThread.join();
	}

	bool Debugger::checkBreakPoints()
	{
		return std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc) != this->_breakPoints.end();
	}

	void Debugger::_displayCurrentLine(unsigned short address, std::ostream &stream)
	{
		stream << "$" << Instructions::intToHex(address, 4) << ": ";
		stream << Instructions::_instructionsString[this->_cpu.read(address)](this->_cpu, address + 1) << std::endl;
	}

	void Debugger::_displayCurrentLine(std::ostream &stream)
	{
		this->_displayCurrentLine(this->_cpu._registers.pc, stream);
	}

	void Debugger::_checkCommands(bool &dbg, std::istream &inputStream)
	{
		std::string line;

		if (std::cin.eof())
			return;

		try {
			std::getline(inputStream, line);
			if ((std::cin.eof() && line.empty()) || this->processCommandLine(line))
				dbg = false;
		} catch (CommandNotFoundException &e) {
			std::cout << e.what() << std::endl;
		} catch (std::out_of_range &e) {
			std::cout << "Not enough arguments" << std::endl;
		} catch (std::exception &e) {
			std::cout << "Error running command: " << e.what() << std::endl;
		}
	}

	int Debugger::startDebugSession()
	{
		bool dbg = true;
		sf::RenderWindow _debugWindow{sf::VideoMode{1920, 1000}, "Debug", sf::Style::Titlebar};

		this->_cpuThread = std::thread([&dbg, this]{
			while (!this->_window.isClosed()) {
				while (dbg)
					std::this_thread::sleep_for(std::chrono::milliseconds(1));

				if (this->_oldpcs.back() != this->_cpu._registers.pc) {
					this->_oldpcs.erase(this->_oldpcs.begin());
					this->_oldpcs.push_back(this->_cpu._registers.pc);
				}

				try {
					this->_cpu.update();
				} catch (CPU::InvalidOpcodeException &e) {
					dbg = true;
					std::cout << e.what() << std::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
				}

				if (this->checkBreakPoints()) {
					auto it = std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc);

					std::cout << "Hit breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << std::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
					dbg = true;
				}

				auto cb = this->checkConditionalBreakPoints();

				if (cb >= 0) {
					auto it = this->_condBreakPoints.begin() + cb;

					std::cout << "Hit conditional breakpoint #" << (it - this->_condBreakPoints.begin()) << std::endl;
					std::cout << "Expression " << (*it)->tostring() << " resolved to " << (*it)->getValue(this->_cpu) << std::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
					dbg = true;
				}
			}
		});

		this->_displayCurrentLine();
		std::cout << "gbdb> ";
		std::cout.flush();
		while (!this->_window.isClosed()) {
			if (dbg) {
				FD_SET	set;
				timeval time = {0, 0};

				FD_ZERO(&set);
				FD_SET(0, &set);

				//TODO: Check WSAEventSelect and WaitForMultipleObjectsEx for Windows
				int found = select(FD_SETSIZE, &set, nullptr, nullptr, &time);

				if (!found) {
					_debugWindow.clear(sf::Color::White);
					this->_drawInstruction(_debugWindow);
					this->_drawMemory(_debugWindow);
					this->_drawRegisters(_debugWindow);
					this->_drawVram(_debugWindow);
					_debugWindow.display();
					this->_window.render();
					this->_handleWindowCommands(_debugWindow);
				} else {
					this->_checkCommands(dbg);

					if (std::cin.eof())
						return 0;

					if (dbg) {
						std::cout << "gbdb> ";
						std::cout.flush();
					}
				}
			}

			if (!dbg) {
				_debugWindow.clear(sf::Color::White);
				this->_drawInstruction(_debugWindow);
				this->_drawMemory(_debugWindow);
				this->_drawRegisters(_debugWindow);
				this->_drawVram(_debugWindow);
				_debugWindow.display();
				this->_window.render();
				this->_handleWindowCommands(_debugWindow);
				if (this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
					dbg = true;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
				}
			}
		}
		return 0;
	}

	void Debugger::_drawInstruction(sf::RenderWindow &_debugWindow)
	{
		sf::Text text;
		int shift = 0;
		int start = this->_cpu._registers.pc - 5;

		if (start < 0)
			start = 0;

		text.setFont(this->_font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setPosition(10, 570);

		for (int i = 0; i < 15; i++) {
			std::stringstream ss;
			auto address = start + i + shift;
			if (address < 0)
				continue;
			this->_displayCurrentLine(address, ss);
			shift += this->_instrSize[this->_cpu.read(address)] - 1;
			text.setString(ss.str());
			text.move(0, 25);
			if (this->_cpu._registers.pc == address)
				text.setFillColor(sf::Color::Red);
			else
				text.setFillColor(sf::Color::Black);
			_debugWindow.draw(text);
		}
	}

	void Debugger::_drawMemory(sf::RenderWindow &_debugWindow)
	{
		std::stringstream ss;

		size_t beg = this->_memBeg;
		size_t end = this->_memBeg + 0x660;

		beg -= beg % 0x20;
		end += 0x20 - end % 0x20;
		for (; beg < end; beg += 0x20) {
			ss << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << beg << ":  ";
			for (unsigned j = 0; j < 0x20 && j + beg < end; j++)
				ss << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(this->_cpu.read(j + beg)) << " ";
			for (int j = 0; j < static_cast<int>(beg - end + 0x20); j++)
				ss << "   ";
			ss << " ";
			for (unsigned j = 0; j < 0x20 && j + beg < end; j++)
				ss << static_cast<char>(std::isprint(this->_cpu.read(j + beg)) ? this->_cpu.read(j + beg) : '.');
			for (int j = 0; j < static_cast<int>(beg - end + 0x20); j++)
				ss << " ";
			ss << std::endl;
		}

		this->_memory.setString(ss.str());
		_debugWindow.draw(this->_memory);
	}

	void Debugger::_handleWindowCommands(sf::RenderWindow &_debugWindow)
	{
		sf::Event event{};

		while (_debugWindow.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
				switch (event.key.code) {
				case sf::Keyboard::Up:
					if (this->_memBeg > 0x0000)
						this->_memBeg -= 0x20;
					break;
				case sf::Keyboard::Down:
					if (this->_memBeg + 0x680 >= 0xFFFF)
						this->_memBeg = 0x10000 - 0x680;
					else
						this->_memBeg += 0x20;
					break;
				case sf::Keyboard::PageUp:
					if (this->_memBeg < 0x660)
						this->_memBeg = 0;
					else
						this->_memBeg -= 0x0660;
					break;
				case sf::Keyboard::PageDown:
					if (this->_memBeg + 0x660 * 2 >= 0xFFFF)
						this->_memBeg = 0x10000 - 0x680;
					else
						this->_memBeg += 0x660;
					break;
				case sf::Keyboard::Num0:
					this->_memBeg = 0x0000;
					break;
				case sf::Keyboard::Num1:
					this->_memBeg = 0x1000;
					break;
				case sf::Keyboard::Num2:
					this->_memBeg = 0x2000;
					break;
				case sf::Keyboard::Num3:
					this->_memBeg = 0x3000;
					break;
				case sf::Keyboard::Quote:
					this->_memBeg = 0x4000;
					break;
				case sf::Keyboard::Num5:
					this->_memBeg = 0x5000;
					break;
				case sf::Keyboard::Dash:
					this->_memBeg = 0x6000;
					break;
				case sf::Keyboard::Num7:
					this->_memBeg = 0x7000;
					break;
				case sf::Keyboard::Num8:
					this->_memBeg = 0x8000;
					break;
				case sf::Keyboard::Num9:
					this->_memBeg = 0x9000;
					break;
				case sf::Keyboard::A:
					this->_memBeg = 0xA000;
					break;
				case sf::Keyboard::B:
					this->_memBeg = 0xB000;
					break;
				case sf::Keyboard::C:
					this->_memBeg = 0xC000;
					break;
				case sf::Keyboard::D:
					this->_memBeg = 0xD000;
					break;
				case sf::Keyboard::E:
					this->_memBeg = 0xE000;
					break;
				case sf::Keyboard::F:
					this->_memBeg = 0xF000;
					break;
				case sf::Keyboard::P:
					this->_rate *= 1.5;
					break;
				case sf::Keyboard::M:
					this->_rate /= 1.5;
					break;
				case sf::Keyboard::O:
					this->_rate *= 10;
					break;
				case sf::Keyboard::L:
					this->_rate /= 10;
					break;
				case sf::Keyboard::K:
					this->_rate = 0.001;
					break;
				case sf::Keyboard::I:
					this->_rate = 1;
					break;
				default:
					break;
				}
		}
		this->_cpu.setSpeed(this->_rate);
	}

	void Debugger::_drawRegisters(sf::RenderWindow &_debugWindow)
	{
		std::stringstream ss;

		ss << std::hex << std::uppercase;
		ss << "af: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.af << "    ";
		ss << "bc: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.bc << "    ";
		ss << "de: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.de << std::endl;
		ss << "hl: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.hl << "    ";
		ss << "sp: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.sp << "    ";
		ss << "pc: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.pc << std::endl;
		ss << "Flags:" << std::endl;
		ss << "z: " << (this->_cpu._registers.fz ? "set" : "unset") << "    ";
		ss << "c: " << (this->_cpu._registers.fc ? "set" : "unset") << "    ";
		ss << "h: " << (this->_cpu._registers.fh ? "set" : "unset") << "    ";
		ss << "n: " << (this->_cpu._registers.fn ? "set" : "unset") << std::endl;

		ss << "lcdc: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCD_CONTROL)) << "     ";
		ss << "stat: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCDC_STAT)) << "     ";
		ss << "ly: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCDC_Y_COORD)) << std::endl;
		ss << "ie: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(INTERRUPT_ENABLE_ADDRESS)) << "     ";
		ss << "if: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::INTERRUPT_REQUESTS)) << "     ";
		ss << "rom: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._rom.getRomBank()) << std::endl << std::endl;

		if (this->_cpu._halted)
			ss << "Waiting for interrupt..." << std::endl;
		ss << "Interrupts " << (this->_cpu._interruptMasterEnableFlag ? "enabled" : "disabled") << std::endl;
		ss << "Next instruction: " << Instructions::_instructionsString[this->_cpu.read(this->_cpu._registers.pc)](this->_cpu, this->_cpu._registers.pc + 1);
		ss << " (" << static_cast<int>(this->_cpu.read(this->_cpu._registers.pc)) << ")" << std::endl;
		ss << "Maximum CPU speed: " << this->_rate * 100 << "%";

		this->_registers.setString(ss.str());
		_debugWindow.draw(this->_registers);
	}

	void Debugger::_displayPalette(sf::RenderWindow &_debugWindow, float x, float y, const std::vector<GBEmulator::Graphics::RGBColor> &palette, bool transparent)
	{
		sf::RectangleShape square{sf::Vector2f{32, 16}};

		for (int i = 0; i < 4; i++) {
			square.setFillColor({
				palette[i].r,
				palette[i].g,
				palette[i].b,
				static_cast<unsigned char>(transparent && i == 0 ? 0 : 255)
			});
			square.setPosition(x + 32 * i, y);
			_debugWindow.draw(square);
		}
	}

	void Debugger::_displayVRAMContent(sf::RenderWindow &_debugWindow, float posx, float posy, const std::vector<GBEmulator::Graphics::RGBColor> &palette, bool transparent)
	{
		auto colors = new sf::Color[16 * 24 * 8 * 8];
		sf::Sprite sprite;
		sf::Texture texture;

		texture.create(16 * 8, 24 * 8);
		for (int xPos = 0; xPos < 16; xPos++) {
			for (int yPos = 0; yPos < 24; yPos++) {
				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						auto index = this->_cpu._gpu._tiles[this->_cpu._gpu._vramBankSwitch][x + y * 8 + xPos * 64 + yPos * 8 * 8 * 16];
						auto &color = palette[((index & 1U) << 1U) | (index >> 1U)];

						colors[x + xPos * 8 + yPos * 8 * 8 * 16 + y * 16 * 8] = {
							color.r,
							color.g,
							color.b,
							static_cast<unsigned char>(transparent && index == 0 ? 0 : 255)
						};
					}
				}
			}
		}
		texture.update(reinterpret_cast<sf::Uint8 *>(colors));
		sprite.setTexture(texture);
		sprite.setPosition(posx, posy);
		sprite.setScale(1.5, 1.5);
		_debugWindow.draw(sprite);
		delete[] colors;
	}

	void Debugger::_displayBackground(sf::RenderWindow &_debugWindow, float posx, float posy)
	{
		auto colors = new sf::Color[32 * 32 * 8 * 8];
		sf::Vector2u camPos = {this->_cpu._gpu._scrollX, this->_cpu._gpu._scrollY};
		sf::Sprite sprite;
		sf::Texture texture;
		sf::RectangleShape cam{sf::Vector2f{160, 144}};
		auto map = this->_cpu._gpu._getTileMap(0, this->_cpu._gpu._control.bgTileMapSelect);

		cam.setFillColor(sf::Color::Transparent);
		cam.setOutlineColor(!this->_cpu._gpu._control.enabled || !this->_cpu._gpu._control.bgDisplayEnabled ? sf::Color::Red : sf::Color::Green);
		cam.setOutlineThickness(4);

		texture.create(32 * 8, 32 * 8);
		for (int xPos = 0; xPos < 32; xPos++) {
			for (int yPos = 0; yPos < 32; yPos++) {
				auto id = this->_cpu._gpu._control.bgAndWindowTileDataSelect ? map[xPos + yPos * 32] : 0x100 + static_cast<char>(map[xPos + yPos * 32]);

				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						auto index = this->_cpu._gpu._tiles[this->_cpu._gpu._vramBankSwitch][id * 64 + x + y * 8];
						auto &color = this->_cpu._gpu._bgPalette[((index & 1U) << 1U) | (index >> 1U)];

						colors[x + xPos * 8 + yPos * 8 * 8 * 32 + y * 32 * 8] = {
							color.r,
							color.g,
							color.b,
							255
						};
					}
				}
			}
		}
		texture.update(reinterpret_cast<sf::Uint8 *>(colors));
		sprite.setTexture(texture);
		sprite.setPosition(posx, posy);
		_debugWindow.draw(sprite);

		cam.setPosition(camPos.x + posx, camPos.y + posy);
		if (camPos.x >= 96) {
			cam.setSize({
				cam.getSize().x - camPos.x + 96,
				cam.getSize().y
			});
		}
		if (camPos.y >= 112) {
			cam.setSize({
				cam.getSize().x,
				cam.getSize().y - camPos.y + 112
			});
		}
		_debugWindow.draw(cam);
		delete[] colors;
	}

	void Debugger::_displayWindow(sf::RenderWindow &_debugWindow, float posx, float posy)
	{
		auto colors = new sf::Color[20 * 18 * 8 * 8];
		sf::Sprite sprite;
		sf::Texture texture;
		sf::RectangleShape cam{sf::Vector2f{160, 144}};
		auto map = this->_cpu._gpu._getTileMap(0, this->_cpu._gpu._control.windowTileMapSelect);

		cam.setFillColor(sf::Color::Transparent);
		cam.setOutlineColor(!this->_cpu._gpu._control.enabled || !this->_cpu._gpu._control.windowEnabled ? sf::Color::Red : sf::Color::Green);
		cam.setOutlineThickness(4);

		texture.create(20 * 8, 18 * 8);
		for (int xPos = 0; xPos < 20; xPos++) {
			for (int yPos = 0; yPos < 18; yPos++) {
				auto id = this->_cpu._gpu._control.bgAndWindowTileDataSelect ? map[xPos + yPos * 32] : 0x100 + static_cast<char>(map[xPos + yPos * 32]);

				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						auto index = this->_cpu._gpu._tiles[this->_cpu._gpu._vramBankSwitch][id * 64 + x + y * 8];
						auto &color = this->_cpu._gpu._bgPalette[((index & 1U) << 1U) | (index >> 1U)];

						colors[x + xPos * 8 + yPos * 8 * 8 * 20 + y * 20 * 8] = {
							color.r,
							color.g,
							color.b,
							255
						};
					}
				}
			}
		}
		texture.update(reinterpret_cast<sf::Uint8 *>(colors));
		sprite.setTexture(texture);
		sprite.setPosition(posx + this->_cpu._gpu._windowX, posy + this->_cpu._gpu._windowY);
		_debugWindow.draw(sprite);

		cam.setPosition(posx, posy);
		_debugWindow.draw(cam);
		delete[] colors;
	}

	void Debugger::_drawVram(sf::RenderWindow &_debugWindow)
	{
		std::vector<Graphics::RGBColor> colors{
			{0, 0, 0},
			{0, 0, 255},
			{0, 255, 0},
			{255, 0, 0}
		};
		sf::RectangleShape square{sf::Vector2f{800, 1000}};

		square.setFillColor(sf::Color::Cyan);
		square.setPosition(1137, 0);
		_debugWindow.draw(square);

		square.setSize({32, 16});

		this->_displayVRAMContent(_debugWindow, 1722, 5, colors, false);
		this->_displayPalette(_debugWindow, 1722, 309, colors, false);

		this->_displayVRAMContent(_debugWindow, 1139, 5, this->_cpu._gpu._bgPalette, false);
		this->_displayPalette(_debugWindow, 1139, 309, this->_cpu._gpu._bgPalette, false);

		this->_displayVRAMContent(_debugWindow, 1333, 5, this->_cpu._gpu._objectPalette0, true);
		this->_displayPalette(_debugWindow, 1333, 309, this->_cpu._gpu._objectPalette0, true);

		this->_displayVRAMContent(_debugWindow, 1528, 5, this->_cpu._gpu._objectPalette1, true);
		this->_displayPalette(_debugWindow, 1528, 309, this->_cpu._gpu._objectPalette1, true);

		this->_displayBackground(_debugWindow, 1200, 340);
		this->_displayWindow(_debugWindow, 1500, 340);

		for (int j = 0; j < 8; j++) {
			std::vector<Graphics::RGBColor> colorBG;
			for (int i = 0; i < 4; i++) {
				colorBG.emplace_back(this->_cpu._gpu._bgpd[j * 4 + i]);
			}
			this->_displayPalette(_debugWindow, 1500, 600 + j * 20, colorBG, false);
		}
	}

	int Debugger::checkConditionalBreakPoints()
	{
		for (size_t i = 0; i < this->_condBreakPoints.size(); i++)
			if (this->_condBreakPoints[i]->getValue(this->_cpu) != 0)
				return i;
		return -1;
	}
}
