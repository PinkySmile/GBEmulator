/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.cpp
*/


#include <iostream>
#include <sstream>
#include <iomanip>
#include "debugger.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"

namespace GBEmulator::Debugger
{
	Debugger::Debugger(GBEmulator::CPU &cpu, GBEmulator::Graphics::ILCD &window, GBEmulator::Input::JoypadEmulator &input) :
		_cpu(cpu),
		_window(window),
		_input(input),
		_debugWindow(sf::VideoMode{1400, 1000}, "Debug", sf::Style::Titlebar)
	{

		this->_memBeg = 0x0000;
		this->_memEnd = 0x660;

		this->_font.loadFromFile("../courier.ttf");

		this->_memory.setFont(this->_font);
		this->_memory.setCharacterSize(14);
		this->_memory.setFillColor(sf::Color::White);
		this->_memory.setPosition(500, 10);

		this->_registers.setFont(this->_font);
		this->_registers.setCharacterSize(24);
		this->_registers.setFillColor(sf::Color::White);
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

			while ((this->_cpu._registers.pc <= address || this->_cpu._registers.pc > address + 3) && !this->checkBreakPoints()) {
				this->_cpu.update();
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
			this->_displayCurrentLine();
		} else if (args[0] == "continue") {
			this->_cpu.update();
			return true;
		} else
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
			this->_debugWindow.clear(sf::Color::Blue);
			try {
				if (dbg)
					this->_checkCommands(dbg);

				if (!dbg && this->checkBreakPoints()) {
					auto it = std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc);

					std::cout << "Hit breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << std::endl;
					this->_displayCurrentLine();
					dbg = true;
				}

				this->_drawInstruction();
				this->_drawMemory();
				this->_drawRegisters();

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
			this->_debugWindow.display();
		}
		return 0;
	}

	void Debugger::_drawInstruction()
	{
		sf::Text text;
		std::stringstream ss;

		text.setFont(this->_font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setPosition(10, 400);

		this->_displayCurrentLine(ss);
		text.setString(ss.str());

		this->_texts.push_back(text);

		if (this->_texts.size() >= 23) {
			this->_texts.erase(this->_texts.begin());
		}

		for (int i = 0; i < this->_texts.size(); i++) {
			this->_texts[i].setPosition(10, 400 + i * 25);
			this->_debugWindow.draw(this->_texts[i]);
		}
	}

	void Debugger::_drawMemory()
	{
		std::stringstream ss;

		size_t beg = this->_memBeg;
		size_t end = this->_memEnd;

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

		sf::Event event;
		while (this->_debugWindow.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				switch (event.key.code) {
				case sf::Keyboard::Up:
					if (this->_memBeg > 0x0000) {
						this->_memBeg -= 0x20;
						this->_memEnd -= 0x20;
					}
					break;
				case sf::Keyboard::Down:
					if (this->_memEnd + 0x20 <= 0xFFFF) {
						this->_memBeg += 0x20;
						this->_memEnd += 0x20;
					}
					break;
				case sf::Keyboard::PageUp:
					if (this->_memBeg > 0x0000) {
						this->_memBeg -= 0x0660;
						this->_memEnd -= 0x0660;
					}
					break;
				case sf::Keyboard::PageDown:
					if (this->_memEnd + 0x0660 <= 0xFFFF) {
						this->_memBeg += 0x0660;
						this->_memEnd += 0x0660;
					}
					break;
				case sf::Keyboard::Num0:
					this->_memBeg = 0x0000;
					this->_memEnd = 0x0660;
					break;
				case sf::Keyboard::Num1:
					this->_memBeg = 0x1000;
					this->_memEnd = 0x1660;
					break;
				case sf::Keyboard::Num2:
					this->_memBeg = 0x2000;
					this->_memEnd = 0x2660;
					break;
				case sf::Keyboard::Num3:
					this->_memBeg = 0x3000;
					this->_memEnd = 0x3660;
					break;
				case sf::Keyboard::Quote:
					this->_memBeg = 0x4000;
					this->_memEnd = 0x4660;
					break;
				case sf::Keyboard::Num5:
					this->_memBeg = 0x5000;
					this->_memEnd = 0x5660;
					break;
				case sf::Keyboard::Dash:
					this->_memBeg = 0x6000;
					this->_memEnd = 0x6660;
					break;
				case sf::Keyboard::Num7:
					this->_memBeg = 0x7000;
					this->_memEnd = 0x7660;
					break;
				case sf::Keyboard::Num8:
					this->_memBeg = 0x8000;
					this->_memEnd = 0x8660;
					break;
				case sf::Keyboard::Num9:
					this->_memBeg = 0x9000;
					this->_memEnd = 0x9660;
					break;
				case sf::Keyboard::A:
					this->_memBeg = 0xA000;
					this->_memEnd = 0xA660;
					break;
				case sf::Keyboard::B:
					this->_memBeg = 0xB000;
					this->_memEnd = 0xB660;
					break;
				case sf::Keyboard::C:
					this->_memBeg = 0xC000;
					this->_memEnd = 0xC660;
					break;
				case sf::Keyboard::D:
					this->_memBeg = 0xD000;
					this->_memEnd = 0xD660;
					break;
				case sf::Keyboard::E:
					this->_memBeg = 0xE000;
					this->_memEnd = 0xE660;
					break;
				case sf::Keyboard::F:
					this->_memBeg = 0xF000;
					this->_memEnd = 0xF660;
					break;
				default:
					break;
				}
		}
		this->_debugWindow.draw(this->_memory);
	}

	void Debugger::_drawRegisters()
	{
		std::stringstream ss;

		ss << std::hex << std::uppercase;
		ss << "af: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.af;
		ss << " (a: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.a);
		ss << ", f: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.f) << ")" << "     ";

		ss << "bc: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.bc;
		ss << " (b: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.b);
		ss << ", c: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.c) << ")" << std::endl;

		ss << "de: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.de;
		ss << " (d: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.d);
		ss << ", e: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.e) << ")" << "     ";

		ss << "hl: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.hl;
		ss << " (h: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.h);
		ss << ", l: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_cpu._registers.l) << ")" << std::endl;

		ss << "sp: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.sp << "     ";
		ss << "pc: " << std::setw(4) << std::setfill('0') << this->_cpu._registers.pc << std::endl << std::endl;

		ss << "Flags:" << std::endl;
		ss << "z: " << (this->_cpu._registers.fz ? "set" : "unset") << "     ";
		ss << "c: " << (this->_cpu._registers.fc ? "set" : "unset") << "     ";
		ss << "h: " << (this->_cpu._registers.fh ? "set" : "unset") << "     ";
		ss << "n: " << (this->_cpu._registers.fn ? "set" : "unset") << std::endl << std::endl;

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

		this->_registers.setString(ss.str());
		this->_debugWindow.draw(this->_registers);
	}
}