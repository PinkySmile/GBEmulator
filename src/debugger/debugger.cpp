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

	bool Debugger::processCommandLine(const std::string &line)
	{
		std::vector<std::string> args = _splitCommand(line);

		if (line.empty())
			args = {this->_lastCmd};
		this->_lastCmd = args.at(0);
		if (args.at(0) == "break") {
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
		} else if (args.at(0) == "help") {
			std::cout << "help" << std::endl;
			std::cout << "jump <addr>" << std::endl;
			std::cout << "next" << std::endl;
			std::cout << "step" << std::endl;
			std::cout << "continue" << std::endl;
			std::cout << "ram" << std::endl;
			std::cout << "registers" << std::endl;
			std::cout << "break <addr>" << std::endl;
		} else if (args.at(0) == "registers") {
			this->_cpu.dumpRegisters();
		} else if (args.at(0) == "ram") {
			this->_cpu.dumpMemory();
		} else if (args.at(0) == "jump") {

		} else if (args.at(0) == "next") {
			unsigned short address = this->_cpu.getRegisters().pc;

			while (this->_cpu.getRegisters().pc <= address || this->_cpu.getRegisters().pc > address + 3)
				this->_cpu.update();
			std::cout << "$" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << ": ";
			std::cout << Instructions::_instructionsString[this->_cpu.read(this->_cpu.getRegisters().pc)](this->_cpu, this->_cpu.getRegisters().pc + 1) << std::endl;
		} else if (args.at(0) == "step") {
			this->_cpu.update();
			std::cout << "$" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << ": ";
			std::cout << Instructions::_instructionsString[this->_cpu.read(this->_cpu.getRegisters().pc)](this->_cpu, this->_cpu.getRegisters().pc + 1) << std::endl;
		} else if (args.at(0) == "continue") {
			return true;
		} else
			throw CommandNotFoundException("Cannot find the command '" + args.at(0) + "'");
		return false;
	}

	bool Debugger::checkBreakPoints()
	{
		return std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu.getRegisters().pc) != this->_breakPoints.end();
	}

	int Debugger::startDebugSession()
	{
		bool dbg = true;

		std::cout << "$" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << ": ";
		std::cout << Instructions::_instructionsString[this->_cpu.read(this->_cpu.getRegisters().pc)](this->_cpu, this->_cpu.getRegisters().pc + 1) << std::endl;
		while (!this->_window.isClosed()) {
			try {
				if (dbg) {
					this->_timer = 0;
					std::string line;

					while (true)
						try {
							std::cout << "gdbgb> ";
							std::getline(std::cin, line);
							if (std::cin.eof() || this->processCommandLine(line))
								dbg = false;
							break;
						} catch (CommandNotFoundException &e) {
							std::cout << e.what() << std::endl;
						} catch (std::out_of_range &e) {
							std::cout << "Not enough arguments" << std::endl;
						} catch (std::exception &e) {
							std::cout << "Error running command: " << e.what() << std::endl;
						}
				} else {
					dbg = this->checkBreakPoints();
					if (dbg) {
						auto it = std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu.getRegisters().pc);

						std::cout << "Hit breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << std::endl;
						std::cout << "$" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << ": ";
						std::cout << Instructions::_instructionsString[this->_cpu.read(this->_cpu.getRegisters().pc)](this->_cpu, this->_cpu.getRegisters().pc + 1) << std::endl;
					}
				}

				if (!dbg) {
					this->_cpu.update();
					if (this->_timer++ == 30)
						this->_timer = 0;
					if (this->_timer == 0 && this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
						dbg = true;
						std::cout << "$" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << ": ";
						std::cout << Instructions::_instructionsString[this->_cpu.read(this->_cpu.getRegisters().pc)](this->_cpu, this->_cpu.getRegisters().pc + 1) << std::endl;
					}
				}
			} catch (CPU::InvalidOpcodeException &e) {
				dbg = true;
				std::cout << "Invalid opcode at address  at $" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << std::endl;
				std::cout << "$" << Instructions::intToHex(this->_cpu.getRegisters().pc, 4) << ": ";
				std::cout << Instructions::_instructionsString[this->_cpu.read(this->_cpu.getRegisters().pc)](this->_cpu, this->_cpu.getRegisters().pc + 1) << std::endl;
			}
		}
		return 0;
	}
}