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
#include "debugger.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"
#include "../ProcessingUnits/Instructions/Strings.hpp"

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

	Debugger::Debugger(const standard::string &, GBEmulator::CPU &cpu, GBEmulator::Graphics::ILCD &window, GBEmulator::Input::JoypadEmulator &input) :
		_cpu(cpu),
		_window(window),
		_input(input)
	{
		this->_memBeg = 0x0000;
		this->_oldpcs.resize(64, 00);
		this->_jumpList.resize(64, 00);
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
			std::cout << "Showing the " << this->_jumpList.size()
				  << " latest jumps" << standard::endl;
			for (auto pc : this->_jumpList)
				this->_displayCurrentLine(pc);
		} else if (args[0] == "cpuState") {std::cout << std::hex << std::uppercase;
			std::cout << "af: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.af;
			std::cout << " (a: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.a);
			std::cout << ", f: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.f) << ")" << std::endl;

			std::cout << "bc: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.bc;
			std::cout << " (b: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.b);
			std::cout << ", c: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.c) << ")" << std::endl;

			std::cout << "de: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.de;
			std::cout << " (d: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.d);
			std::cout << ", e: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.e) << ")" << std::endl;

			std::cout << "hl: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.hl;
			std::cout << " (h: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.h);
			std::cout << ", l: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.l) << ")" << std::endl;

			std::cout << "sp: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.sp << std::endl;
			std::cout << "pc: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.pc << std::endl;
			std::cout << "z: " << (this->_cpu._registers.fz ? "set" : "unset") << std::endl;
			std::cout << "c: " << (this->_cpu._registers.fc ? "set" : "unset") << std::endl;
			std::cout << "h: " << (this->_cpu._registers.fh ? "set" : "unset") << std::endl;
			std::cout << "n: " << (this->_cpu._registers.fn ? "set" : "unset") << std::endl;

			std::cout << "lcdc: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCD_CONTROL)) << std::endl;
			std::cout << "stat: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCDC_STAT)) << std::endl;
			std::cout << "ly: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::LCDC_Y_COORD)) << std::endl;
			std::cout << "ie: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::INTERRUPT_ENABLED)) << std::endl;
			std::cout << "if: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu.read(0xFF00 + CPU::INTERRUPT_REQUESTS)) << std::endl;
			std::cout << "rom: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._rom.getRomBank()) << std::endl;

			if (this->_cpu._halted)
				std::cout << "Waiting for interrupt..." << std::endl;
			std::cout << "Interrupts " << (this->_cpu._interruptMasterEnableFlag ? "enabled" : "disabled") << std::endl;
			std::cout << "Next instruction: " << Instructions::_instructionsString[this->_cpu.read(this->_cpu._registers.pc)](this->_cpu, this->_cpu._registers.pc + 1);
			std::cout << " (" << static_cast<int>(this->_cpu.read(this->_cpu._registers.pc)) << ")" << std::endl;
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

				if (!found)
					this->_window.render();
				else {
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
				this->_window.render();
				if (this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
					std::cout << "Manual break" << std::endl;
					dbg = true;
					this->_displayCurrentLine();
					std::cout << "gbdb> ";
					std::cout.flush();
				}
			}
		}
		return 0;
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
