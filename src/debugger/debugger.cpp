/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.cpp
*/


#include <iostream>
#include <sstream>
#include "debugger.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"

namespace GBEmulator::Debugger
{
	Debugger::Debugger(GBEmulator::CPU &cpu, GBEmulator::Graphics::ILCD &window, GBEmulator::Input::JoypadEmulator &input) :
		_cpu(cpu),
		_window(window),
		_input(input)
	{
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
		else if (args[0] == "print")
			this->_dispVar(args.at(1));
		else if (args[0] == "set") {
			this->_setVar(args.at(1), std::stoul(args.at(2), nullptr, 16));
			this->_dispVar(args.at(1));
		} else if (args[0] == "ram") {
			if (args.size() == 1)
				return this->_cpu.dumpMemory(), false;
			for (size_t i = std::stoul(args.at(1), nullptr, 16), end = std::stoul(args.at(2), nullptr, 16); i < end; i++)
				std::cout << "$" << Instructions::intToHex(i, 4) << ": " << Instructions::intToHex(this->_cpu.read(i)) << std::endl;
		} else if (args[0] == "jump") {
			this->_cpu._registers.pc = std::stoul(args.at(1), nullptr, 16);
			this->_displayCurrentLine();
		} else if (args[0] == "next") {
			unsigned short address = this->_cpu._registers.pc;

			while ((this->_cpu._registers.pc <= address || this->_cpu._registers.pc > address + 3) && !this->checkBreakPoints())
				this->_cpu.update();
			this->_displayCurrentLine();
		} else if (args[0] == "step") {
			this->_cpu.update();
			this->_displayCurrentLine();
		} else if (args[0] == "continue")
			return true;
		else
			throw CommandNotFoundException("Cannot find the command '" + args[0] + "'");
		return false;
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

		while (true)
			try {
				std::cout << "gdbgb> ";
				std::getline(inputStream, line);
				if (std::cin.eof() || this->processCommandLine(line))
					dbg = false;
				return;
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

		this->_displayCurrentLine();
		while (!this->_window.isClosed()) {
			try {
				if (dbg)
					this->_checkCommands(dbg);

				if (this->checkBreakPoints()) {
					auto it = std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc);

					std::cout << "Hit breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << std::endl;
					this->_displayCurrentLine();
					dbg = true;
				}

				if (!dbg) {
					this->_cpu.update();
					if (this->_timer++ == 30)
						this->_timer = 0;
					if (this->_timer == 0 && this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
						dbg = true;
						this->_displayCurrentLine();
					}
				}
			} catch (CPU::InvalidOpcodeException &e) {
				dbg = true;
				std::cout << e.what() << std::endl;
				this->_displayCurrentLine();
			}
		}
		return 0;
	}
}