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
#include <fstream>
#include <sstream>
#include <functional>
#include "GUIdebugger.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"
#include "../ProcessingUnits/Instructions/Strings.hpp"
#include "../LCD/LCDSFML.hpp"

namespace GBEmulator::Debugger
{
	const standard::vector<unsigned char> Debugger::_instrSize = {
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

	Debugger::Debugger(const standard::string &programPath, GBEmulator::CPU &cpu, GBEmulator::Graphics::ILCD &window, GBEmulator::Input::JoypadEmulator &input) :
		_cpu(cpu),
		_window(window),
		_input(input)
	{
		this->_memBeg = 0x0000;
		this->_oldpcs.resize(64, 00);
		this->_jumpList.resize(64, 00);

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


	standard::vector<standard::string> Debugger::_splitCommand(const standard::string &line)
	{
		standard::vector<standard::string> result;
		standard::stringstream stream;
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

	void Debugger::_setVar(const standard::string &name, unsigned short value)
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
			size_t address = standard::stoul(name, nullptr, 16);

			if (address > UINT16_MAX)
				throw standard::invalid_argument("stoul");
			this->_cpu.write(address, value);
		}
	}

	void Debugger::_dispVar(const standard::string &name)
	{
		if (name == "a")
			std::cout << "a: " << Instructions::intToHex(this->_cpu._registers.a) << standard::endl;
		else if (name == "b")
			std::cout << "b: " << Instructions::intToHex(this->_cpu._registers.b) << standard::endl;
		else if (name == "c")
			std::cout << "c: " << Instructions::intToHex(this->_cpu._registers.c) << standard::endl;
		else if (name == "d")
			std::cout << "d: " << Instructions::intToHex(this->_cpu._registers.d) << standard::endl;
		else if (name == "e")
			std::cout << "e: " << Instructions::intToHex(this->_cpu._registers.e) << standard::endl;
		else if (name == "h")
			std::cout << "h: " << Instructions::intToHex(this->_cpu._registers.h) << standard::endl;
		else if (name == "l")
			std::cout << "l: " << Instructions::intToHex(this->_cpu._registers.l) << standard::endl;
		else if (name == "f")
			std::cout << "f: " << Instructions::intToHex(this->_cpu._registers.f) << standard::endl;
		else if (name == "af")
			std::cout << "af: " << Instructions::intToHex(this->_cpu._registers.af, 4) << standard::endl;
		else if (name == "bc")
			std::cout << "bc: " << Instructions::intToHex(this->_cpu._registers.bc, 4) << standard::endl;
		else if (name == "de")
			std::cout << "de: " << Instructions::intToHex(this->_cpu._registers.de, 4) << standard::endl;
		else if (name == "hl")
			std::cout << "hl: " << Instructions::intToHex(this->_cpu._registers.hl, 4) << standard::endl;
		else if (name == "pc")
			this->_displayCurrentLine();
		else if (name == "sp")
			std::cout << "sp: " << Instructions::intToHex(this->_cpu._registers.sp, 4) << standard::endl;
		else {
			size_t address = standard::stoul(name, nullptr, 16);

			if (address > UINT16_MAX)
				throw standard::invalid_argument("stoul");
			std::cout << "$" << Instructions::intToHex(address, 4) << ": " << Instructions::intToHex(this->_cpu.read(address)) << standard::endl;
			this->_displayCurrentLine(address);
		}
	}

	bool Debugger::processCommandLine(const standard::string &line)
	{
		standard::vector<standard::string> args = _splitCommand(line);

		if (line.empty())
			args = {this->_lastCmd};
		this->_lastCmd = args[0];
		if (args[0] == "break") {
			if (args.size() == 1) {
				std::cout << "There are " << this->_breakPoints.size() << " breakpoint(s)" << standard::endl;
				for (unsigned i = 0; i < this->_breakPoints.size(); i++)
					std::cout << "Breakpoint #" << i << " at $" << Instructions::intToHex(this->_breakPoints[i], 4) << standard::endl;
				return false;
			}
			auto add = standard::stoul(args.at(1), nullptr, 16);
			auto it = standard::find(this->_breakPoints.begin(), this->_breakPoints.end(), add);

			if (it != this->_breakPoints.end()) {
				std::cout << "Breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << " removed" << standard::endl;
				this->_breakPoints.erase(it);
			} else {
				std::cout << "Added breakpoint #" << this->_breakPoints.size() << " at $" << Instructions::intToHex(add, 4) << standard::endl;
				this->_breakPoints.push_back(add);
			}
		} else if (args[0] == "cbreak") {
			if (args.size() == 1) {
				std::cout << "There are " << this->_condBreakPoints.size() << " conditional breakpoint(s)" << standard::endl;
				for (unsigned i = 0; i < this->_condBreakPoints.size(); i++)
					std::cout << "Conditional breakpoint #" << i << " when (" << this->_condBreakPoints[i]->tostring() << ") != 0" << standard::endl;
				return false;
			}

			if (args[1] == "remove") {
				if (args.size() != 3) {
					std::cout << "Expected 2 arguments" << standard::endl;
					return false;
				}

				auto add = standard::stoul(args.at(2), nullptr, 16);

				if (add >= this->_condBreakPoints.size()) {
					std::cout << "Invalid conditional breakpoints id." << standard::endl;
					std::cout << add << " is greater than the number of conditional breakpoints (" << add << " >= " << this->_condBreakPoints.size() << ")" << standard::endl;
					return false;
				}

				auto it = this->_condBreakPoints.begin() + add;

				std::cout << "Removed conditional breakpoint #" << (it - this->_condBreakPoints.begin()) << " when (" << (*it)->tostring() << ") != 0" << standard::endl;
				this->_condBreakPoints.erase(it);
				return false;
			}

			standard::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << "Added conditional breakpoint #" << this->_condBreakPoints.size() << " when (" << op->tostring() << ") != 0" << standard::endl;
				this->_condBreakPoints.push_back(op);
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "help") {
			std::cout << "help" << standard::endl;
			std::cout << "jump <addr>" << standard::endl;
			std::cout << "next" << standard::endl;
			std::cout << "step" << standard::endl;
			std::cout << "continue" << standard::endl;
			std::cout << "ram [<border1> <border2>]" << standard::endl;
			std::cout << "break <addr>" << standard::endl;
			std::cout << "cbreak <expression>" << standard::endl;
			std::cout << "print <expression>" << standard::endl;
			std::cout << "printi <expression>" << standard::endl;
			std::cout << "printx <expression>" << standard::endl;
			std::cout << "printo <expression>" << standard::endl;
			std::cout << "printb <expression>" << standard::endl;
			std::cout << "oldpcres <nb>" << standard::endl;
			std::cout << "oldpc" << standard::endl;
			std::cout << "jmplistres <nb>" << standard::endl;
			std::cout << "jmplist" << standard::endl;
		} else if (args[0] == "oldpc") {
			std::cout << "Showing the " << this->_oldpcs.size() << " latest pc values" << standard::endl;
			for (auto pc : this->_oldpcs)
				this->_displayCurrentLine(pc);
		} else if (args[0] == "oldpcres") {
			auto newSize = standard::stoul(args.at(1));

			if (newSize < this->_oldpcs.size())
				this->_oldpcs.erase(this->_oldpcs.begin(), this->_oldpcs.begin() + this->_oldpcs.size() - newSize);
			this->_oldpcs.resize(newSize);
			std::cout << "oldpc will now display " << this->_oldpcs.size() << " elements" << standard::endl;
		} else if (args[0] == "jmplistres") {
			auto newSize = standard::stoul(args.at(1));

			if (newSize < this->_jumpList.size())
				this->_jumpList.erase(this->_jumpList.begin(), this->_jumpList.begin() + this->_jumpList.size() - newSize);
			this->_jumpList.resize(newSize);
			std::cout << "jmplist will now display " << this->_jumpList.size() << " elements" << standard::endl;
		} else if (args[0] == "jmplist") {
			std::cout << "Showing the " << this->_jumpList.size() << " latest jumps" << standard::endl;
			for (auto pc : this->_jumpList)
				this->_displayCurrentLine(pc);
		} else if (args[0] == "print") {
			standard::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << standard::dec << op->getValue(this->_cpu) << standard::endl;
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "printx") {
			standard::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << "$" << standard::hex << static_cast<unsigned>(op->getValue(this->_cpu)) << standard::endl;
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "printi") {
			standard::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				this->_displayCurrentLine(static_cast<unsigned>(op->getValue(this->_cpu)));
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "printo") {
			standard::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);

				std::cout << "&" << standard::oct << static_cast<unsigned>(op->getValue(this->_cpu)) << standard::endl;
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "ignore") {
			standard::string cmd = line.substr(args[0].size());

			try {
				unsigned op = compileCondition(this->_cpu._registers, this->_cpu, cmd)->getValue(this->_cpu);
				auto it = standard::find(this->_ignoredCorruptedStackAddress.begin(), this->_ignoredCorruptedStackAddress.end(), op);

				if (it == this->_ignoredCorruptedStackAddress.end()) {
					this->_ignoredCorruptedStackAddress.push_back(op);
					std::cout << "Ignored address $" << standard::hex << op << " for stack corruption and source code break points" << standard::endl;
				} else {
					this->_ignoredCorruptedStackAddress.erase(it);
					std::cout << "Address $" << standard::hex << op << " is no longer ignored for stack corruption and source code break points" << standard::endl;
				}
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "printb") {
			standard::string cmd = line.substr(args[0].size());

			try {
				auto op = compileCondition(this->_cpu._registers, this->_cpu, cmd);
				auto val = static_cast<unsigned>(op->getValue(this->_cpu));
				standard::stringstream s;

				std::cout << "%";
				do {
					s << (val & 1U);
					val >>= 1U;
				} while (val);

				auto str = s.str();

				for (int i = str.length()-1; i>=0; i--)
					std::cout << str[i];
				std::cout << standard::endl;
			} catch (standard::exception &e) {
				std::cout << e.what() << standard::endl;
			}
		} else if (args[0] == "set") {
			this->_setVar(args.at(1), standard::stoul(args.at(2), nullptr, 16));
			this->_dispVar(args.at(1));
		} else if (args[0] == "slow") {
			this->_executeNextInstruction(true);
			this->_rate = 0.001;
			return true;
		} else if (args[0] == "ram") {
			size_t i = standard::stoul(args.at(1), nullptr, 16);
			size_t end = standard::stoul(args.at(2), nullptr, 16);

			i -= i % 0x10;
			end += 0x10 - end % 0x10;
			for (; i < end; i += 0x10) {
				std::cout << standard::hex << standard::uppercase << standard::setw(4) << standard::setfill('0') << i << ":  ";
				for (unsigned j = 0; j < 0x10 && j + i < end; j++)
					std::cout << standard::setw(2) << standard::setfill('0') << standard::hex << standard::uppercase << static_cast<int>(this->_cpu.read(j + i)) << " ";
				for (int j = 0; j < static_cast<int>(i - end + 0x10); j++)
					std::cout << "   ";
				std::cout << " ";
				for (unsigned j = 0; j < 0x10 && j + i < end; j++)
					std::cout << static_cast<char>(standard::isprint(this->_cpu.read(j + i)) ? this->_cpu.read(j + i) : '.');
				for (int j = 0; j < static_cast<int>(i - end + 0x10); j++)
					std::cout << " ";
				std::cout << standard::endl;
			}
		} else if (args[0] == "checkstack") {
			this->_checkForStackCorruption = !this->_checkForStackCorruption;
			std::cout << "Stack corruption check is " << (this->_checkForStackCorruption ? "en" : "dis") << "abled" << standard::endl;
		} else if (args[0] == "jump") {
			this->_cpu._registers.pc = standard::stoul(args.at(1), nullptr, 16);
			this->_displayCurrentLine();
		} else if (args[0] == "next") {
			uint16_t address = this->_cpu._registers.pc;
			auto bIt = standard::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc);
			auto cbNb = this->checkConditionalBreakPoints();

			this->_executeNextInstruction(true);
			do {
				this->_executeNextInstruction(false);
				if (this->_timer++ == 30)
					this->_timer = 0;
				if (this->_timer == 0 && this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
					this->_displayCurrentLine();
					break;
				}
			} while ((this->_cpu._registers.pc <= address || this->_cpu._registers.pc > address + 3) && bIt == this->_breakPoints.end() && cbNb == -1);
			if (cbNb != -1)
				std::cout << "Hit conditional breakpoint #" << cbNb << ": " << this->_condBreakPoints[cbNb]->tostring() << standard::endl;
			else if (bIt != this->_breakPoints.end())
				std::cout << "Hit breakpoint #" << bIt - this->_breakPoints.begin() << ": $" << standard::setw(4) << standard::setfill('0') << standard::hex << *bIt << standard::endl;
			this->_displayCurrentLine();
		} else if (args[0] == "step") {
			this->_executeNextInstruction(true);
			this->_displayCurrentLine();
		} else if (args[0] == "continue") {
			this->_executeNextInstruction(true);
			return true;
		} else if (args[0] == "where")
			this->_displayCurrentLine();
		else if (args[0] == "freeze") {
			unsigned addr = standard::stoul(args.at(1), nullptr, 16);
			unsigned val = args.size() >= 3 ? standard::stoul(args.at(2), nullptr, 16) : this->_cpu.read(addr);

			std::cout << "Address " << standard::hex << addr << " is ";
			if (this->_cpu.freezeAddress(addr, val))
				std::cout << "now frozen to value" << standard::hex << val << standard::endl;
			else
				std::cout << "no longer frozen" << val << standard::endl;
		} else
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
		return standard::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc) != this->_breakPoints.end();
	}

	void Debugger::_displayCurrentLine(uint16_t address, standard::ostream &stream)
	{
		stream << "$" << Instructions::intToHex(address, 4) << ": ";
		stream << Instructions::_instructionsString[this->_cpu.read(address)](this->_cpu, address + 1) << standard::endl;
	}

	void Debugger::_displayCurrentLine(standard::ostream &stream)
	{
		this->_displayCurrentLine(this->_cpu._registers.pc, stream);
	}

	void Debugger::_checkCommands(bool &dbg, standard::istream &inputStream)
	{
		standard::string line;

		if (standard::cin.eof())
			return;

		try {
			standard::getline(inputStream, line);
			if ((standard::cin.eof() && line.empty()) || this->processCommandLine(line))
				dbg = false;
		} catch (CommandNotFoundException &e) {
			std::cout << e.what() << standard::endl;
		} catch (standard::out_of_range &e) {
			std::cout << "Not enough arguments" << standard::endl;
		} catch (standard::exception &e) {
			std::cout << "Error running command: " << e.what() << standard::endl;
		}
	}

	int Debugger::startDebugSession()
	{
		bool dbg = true;
		sf::RenderWindow _debugWindow{sf::VideoMode{1920, 1000}, "Debug", sf::Style::Titlebar};

#ifdef _WIN32
		if (!GetConsoleWindow()) {
			FILE *_;

			AllocConsole();
			freopen_s(&_, "CONOUT$", "w", stdout);
			freopen_s(&_, "CONIN$", "r", stdin);
		}
#endif
		this->_cpuThread = standard::thread([&dbg, this]{
			while (!this->_window.isClosed()) {
				while (dbg)
					standard::this_thread::sleep_for(standard::chrono::milliseconds(1));

				try {
					this->_executeNextInstruction(false);
				} catch (CPU::InvalidOpcodeException &e) {
					dbg = true;
					std::cout << e.what() << standard::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
				}

				auto nextOpcode = this->_cpu.read(this->_cpu._registers.pc);

				if (
					this->_checkForStackCorruption &&
					(
						(this->_cpu._registers.sp <= 0xFF80 && this->_cpu._registers.sp > 0xE000) ||
						(this->_cpu._registers.sp <= 0xC000 && this->_cpu._registers.sp > 0x0000)
					)
				) {
					dbg = true;
					std::cout << "Probably corrupted stack after function return." << standard::endl;
					std::cout << "Stack is at an invalid location $" << this->_cpu._registers.sp << standard::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
				}

				if (
					nextOpcode == 0xC7 ||
					nextOpcode == 0xCF ||
					nextOpcode == 0xD7 ||
					nextOpcode == 0xDF ||
					nextOpcode == 0xE7 ||
					nextOpcode == 0xEF ||
					nextOpcode == 0xF7 ||
					nextOpcode == 0xFF ||
					nextOpcode == 0xC9 ||
					nextOpcode == 0xD9 ||
					nextOpcode == 0xC3 ||
					nextOpcode == 0x18 ||
					nextOpcode == 0xE9 ||
					(nextOpcode == 0xC2 && !this->_cpu._registers.fz) ||
					(nextOpcode == 0xC0 && !this->_cpu._registers.fz) ||
					(nextOpcode == 0x20 && !this->_cpu._registers.fz) ||
					(nextOpcode == 0xC8 && this->_cpu._registers.fz) ||
					(nextOpcode == 0xCA && this->_cpu._registers.fz) ||
					(nextOpcode == 0x28 && this->_cpu._registers.fz) ||
					(nextOpcode == 0xD0 && !this->_cpu._registers.fc) ||
					(nextOpcode == 0xD2 && !this->_cpu._registers.fc) ||
					(nextOpcode == 0x30 && !this->_cpu._registers.fc) ||
					(nextOpcode == 0x38 && this->_cpu._registers.fc) ||
					(nextOpcode == 0xD8 && this->_cpu._registers.fc) ||
					(nextOpcode == 0xDA && this->_cpu._registers.fc)
				) {
					this->_jumpList.erase(this->_jumpList.begin());
					this->_jumpList.push_back(this->_cpu._registers.pc);
				}

				if (
					standard::find(
						this->_ignoredCorruptedStackAddress.begin(),
						this->_ignoredCorruptedStackAddress.end(),
						this->_cpu._registers.pc
					) == this->_ignoredCorruptedStackAddress.end() &&
					nextOpcode == 0x40
				) {
					dbg = true;
					std::cout << "Hit source code breakpoint" << standard::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
				}

				if (
					nextOpcode == 0xC7 ||
					nextOpcode == 0xCF ||
					nextOpcode == 0xD7 ||
					nextOpcode == 0xDF ||
					nextOpcode == 0xE7 ||
					nextOpcode == 0xEF ||
					nextOpcode == 0xF7 ||
					nextOpcode == 0xFF ||
					nextOpcode == 0xC9 ||
					(nextOpcode == 0xC0 && !this->_cpu._registers.fz) ||
					(nextOpcode == 0xC8 && this->_cpu._registers.fz) ||
					//nextOpcode == 0xD9 ||
					(nextOpcode == 0xD0 && !this->_cpu._registers.fc) ||
					(nextOpcode == 0xD8 && this->_cpu._registers.fc)
				) {
					if (!this->_expectedPcAtRet.empty()) {
						auto expected = this->_expectedPcAtRet.top();

						if (this->_cpu._registers.sp == expected)
							this->_expectedPcAtRet.pop();
						else if (
							standard::find(
								this->_ignoredCorruptedStackAddress.begin(),
								this->_ignoredCorruptedStackAddress.end(),
								this->_cpu._registers.pc
							) == this->_ignoredCorruptedStackAddress.end() &&
							this->_checkForStackCorruption
						) {
							dbg = true;
							std::cout << "Probably corrupted stack after function return." << standard::endl;
							std::cout << "Stack is expected to be at $" << standard::hex << expected << " but is at $" << this->_cpu._registers.sp << standard::endl;
							this->_displayCurrentLine();
							std::cout << "gbdb> ";
							std::cout.flush();
						}
					} else if (
						standard::find(
							this->_ignoredCorruptedStackAddress.begin(),
							this->_ignoredCorruptedStackAddress.end(),
							this->_cpu._registers.pc
						) == this->_ignoredCorruptedStackAddress.end() &&
						this->_checkForStackCorruption
					){
						dbg = true;
						std::cout << "Probably corrupted stack after function return." << standard::endl;
						std::cout << "Stack is at $" << standard::hex << this->_cpu._registers.sp << " but the call stack is empty." << standard::endl;
						this->_displayCurrentLine();
						std::cout << "gbdb> ";
						std::cout.flush();
					}
				}

				if (
					nextOpcode == 0xCD ||
					(nextOpcode == 0xC4 && !this->_cpu._registers.fz) ||
					(nextOpcode == 0xCC && this->_cpu._registers.fz) ||
					(nextOpcode == 0xD4 && !this->_cpu._registers.fc) ||
					(nextOpcode == 0xDC && this->_cpu._registers.fc)
				)
					this->_expectedPcAtRet.push(this->_cpu._registers.sp - 2);

				if (this->checkBreakPoints()) {
					auto it = standard::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc);

					std::cout << "Hit breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << standard::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
					dbg = true;
				}

				auto cb = this->checkConditionalBreakPoints();

				if (cb >= 0) {
					auto it = this->_condBreakPoints.begin() + cb;

					std::cout << "Hit conditional breakpoint #" << (it - this->_condBreakPoints.begin()) << standard::endl;
					std::cout << "Expression " << (*it)->tostring() << " resolved to " << (*it)->getValue(this->_cpu) << standard::endl;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
					dbg = true;
				}
			}
		});

		standard::ifstream stream{".emudbgbrc"};
		int currentLine = 0;

		if (!stream.fail()) {
			standard::string line;

			std::cout << "Executing commands in .emudbgbrc." << standard::endl;
			while (standard::getline(stream, line)) {
				currentLine++;
				try {
					dbg &= !processCommandLine(line);
				} catch (standard::exception &e) {
					std::cout << "Error line " << currentLine << ": " << line << standard::endl;
					std::cout << e.what() << standard::endl;
				}
			}
		}
		if (dbg) {
			this->_displayCurrentLine();
			std::cout << "gbdb> ";
			std::cout.flush();
		}
		while (!this->_window.isClosed()) {
			if (dbg) {
#ifdef _WIN32
				this->_checkCommands(dbg);

				if (standard::cin.eof())
					return 0;

				if (dbg) {
					std::cout << "gbdb> ";
					std::cout.flush();
				}
#else
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

					if (standard::cin.eof())
						return 0;

					if (dbg) {
						std::cout << "gbdb> ";
						std::cout.flush();
					}
				}
#endif
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
			standard::stringstream ss;
			auto address = start + i + shift;
			if (address < 0)
				continue;
			this->_displayCurrentLine(address, ss);
			shift += this->_instrSize[this->_cpu.read(address)] - 1;
			text.setString(ss.str().c_str());
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
		standard::stringstream ss;

		size_t beg = this->_memBeg;
		size_t end = this->_memBeg + 0x660;

		beg -= beg % 0x20;
		end += 0x20 - end % 0x20;
		for (; beg < end; beg += 0x20) {
			ss << standard::hex << standard::uppercase << standard::setw(4) << standard::setfill('0') << beg << ":  ";
			for (unsigned j = 0; j < 0x20 && j + beg < end; j++)
				ss << standard::setw(2) << standard::setfill('0') << standard::hex << standard::uppercase << static_cast<int>(this->_cpu.read(j + beg)) << " ";
			for (int j = 0; j < static_cast<int>(beg - end + 0x20); j++)
				ss << "   ";
			ss << " ";
			for (unsigned j = 0; j < 0x20 && j + beg < end; j++)
				ss << static_cast<char>(standard::isprint(this->_cpu.read(j + beg)) ? this->_cpu.read(j + beg) : '.');
			for (int j = 0; j < static_cast<int>(beg - end + 0x20); j++)
				ss << " ";
			ss << standard::endl;
		}

		this->_memory.setString(ss.str().c_str());
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
				case sf::Keyboard::Num4:
				case sf::Keyboard::Quote:
					this->_memBeg = 0x4000;
					break;
				case sf::Keyboard::Num5:
					this->_memBeg = 0x5000;
					break;
				case sf::Keyboard::Num6:
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
		standard::stringstream ss;

		ss << standard::hex << standard::uppercase;
		ss << "af: " << standard::setw(4) << standard::setfill('0') << this->_cpu._registers.af << "    ";
		ss << "bc: " << standard::setw(4) << standard::setfill('0') << this->_cpu._registers.bc << "    ";
		ss << "de: " << standard::setw(4) << standard::setfill('0') << this->_cpu._registers.de << standard::endl;
		ss << "hl: " << standard::setw(4) << standard::setfill('0') << this->_cpu._registers.hl << "    ";
		ss << "sp: " << standard::setw(4) << standard::setfill('0') << this->_cpu._registers.sp << "    ";
		ss << "pc: " << standard::setw(4) << standard::setfill('0') << this->_cpu._registers.pc << standard::endl;
		ss << "Flags:" << standard::endl;
		ss << "z: " << (this->_cpu._registers.fz ? "set" : "unset") << "    ";
		ss << "c: " << (this->_cpu._registers.fc ? "set" : "unset") << "    ";
		ss << "h: " << (this->_cpu._registers.fh ? "set" : "unset") << "    ";
		ss << "n: " << (this->_cpu._registers.fn ? "set" : "unset") << standard::endl;

		ss << "lcdc: " << standard::setw(2) << standard::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCD_CONTROL)) << "     ";
		ss << "stat: " << standard::setw(2) << standard::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCDC_STAT)) << "     ";
		ss << "ly: " << standard::setw(2) << standard::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCDC_Y_COORD)) << standard::endl;
		ss << "ie: " << standard::setw(2) << standard::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::INTERRUPT_ENABLED)) << "     ";
		ss << "if: " << standard::setw(2) << standard::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::INTERRUPT_REQUESTS)) << "     ";
		ss << "rom: " << standard::setw(2) << standard::setfill('0') << static_cast<int>(this->_cpu._rom.getRomBank()) << standard::endl << standard::endl;

		if (this->_cpu._halted)
			ss << "Waiting for interrupt..." << standard::endl;
		ss << "Interrupts " << (this->_cpu._interruptMasterEnableFlag ? "enabled" : "disabled") << standard::endl;
		ss << "Next instruction: " << Instructions::_instructionsString[this->_cpu.read(this->_cpu._registers.pc)](this->_cpu, this->_cpu._registers.pc + 1);
		ss << " (" << static_cast<int>(this->_cpu.read(this->_cpu._registers.pc)) << ")" << standard::endl;
		ss << "Maximum CPU speed: " << this->_rate * 100 << "%";

		this->_registers.setString(ss.str().c_str());
		_debugWindow.draw(this->_registers);
	}

	void Debugger::_displayPalette(sf::RenderWindow &_debugWindow, float x, float y, const GBEmulator::Graphics::RGBColor (&palette)[4], bool transparent)
	{
		sf::RectangleShape square{sf::Vector2f{32, 16}};

		for (int i = 0; i < 4; i++) {
			square.setFillColor({
				palette[i].r,
				palette[i].g,
				palette[i].b,
				static_cast<uint8_t>(transparent && i == 0 ? 0 : 255)
			});
			square.setPosition(x + 32 * i, y);
			_debugWindow.draw(square);
		}
	}

	void Debugger::_displayVRAMContent(sf::RenderWindow &_debugWindow, float posx, float posy, const GBEmulator::Graphics::RGBColor (&palette)[4], bool transparent)
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
							static_cast<uint8_t>(transparent && index == 0 ? 0 : 255)
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
		Graphics::RGBColor colors[4] = {
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
			Graphics::RGBColor colorBG[4];

			for (int i = 0; i < 4; i++)
				colorBG[i] = this->_cpu._gpu._bgpd[j * 4 + i];
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

	void Debugger::_executeNextInstruction(bool resetClock)
	{
		if (this->_oldpcs.back() != this->_cpu._registers.pc) {
			this->_oldpcs.erase(this->_oldpcs.begin());
			this->_oldpcs.push_back(this->_cpu._registers.pc);
		}
		if (resetClock) {
			this->_cpu._clock.restart();
			this->_cpu._oldTime = -1;
		}

		this->_cpu.update(1);
	}
}
