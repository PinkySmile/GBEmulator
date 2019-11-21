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
		_instructionsWindow(sf::VideoMode{600, 900}, "Instructions", sf::Style::Titlebar),
		_memoryWindow(sf::VideoMode{1000, 1000}, "Memory", sf::Style::Titlebar)
	{
		if (!_font.loadFromFile("../courier.ttf"))
			throw std::exception();

		this->_memory.setFont(this->_font);
		this->_memory.setCharacterSize(14);
		this->_memory.setFillColor(sf::Color::White);
		this->_memory.setPosition(10, 10);
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
			this->_instructionsWindow.clear(sf::Color::Blue);
			this->_memoryWindow.clear(sf::Color::Blue);
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
			this->_instructionsWindow.display();
			this->_memoryWindow.display();
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
		text.setPosition(10, 10);

		this->_displayCurrentLine(ss);
		text.setString(ss.str());

		this->_texts.push_back(text);

		if (this->_texts.size() >= 36) {
			this->_texts.erase(this->_texts.begin());
		}

		for (int i = 0; i < this->_texts.size(); i++) {
			this->_texts[i].setPosition(10, 10 + i * 25);
			this->_instructionsWindow.draw(this->_texts[i]);
		}
	}

	void Debugger::_drawMemory()
	{
		std::stringstream ss;
		size_t i = 0x0000;
		size_t end = 0xFFFF;

		i -= i % 0x20;
		end += 0x20 - end % 0x20;
		for (; i < end; i += 0x20) {
			ss << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << i << ":  ";
			for (unsigned j = 0; j < 0x20 && j + i < end; j++)
				ss << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(this->_cpu.read(j + i)) << " ";
			for (int j = 0; j < static_cast<int>(i - end + 0x20); j++)
				ss << "   ";
			ss << " ";
			for (unsigned j = 0; j < 0x20 && j + i < end; j++)
				ss << static_cast<char>(std::isprint(this->_cpu.read(j + i)) ? this->_cpu.read(j + i) : '.');
			for (int j = 0; j < static_cast<int>(i - end + 0x20); j++)
				ss << " ";
			ss << std::endl;
		}

		this->_memory.setString(ss.str());

		sf::Event event;
		while (this->_memoryWindow.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				switch (event.key.code) {
				case sf::Keyboard::Up:
					this->_memory.move(0, 12);
					break;
				case sf::Keyboard::Down:
					this->_memory.move(0, -12);
					break;
				case sf::Keyboard::Num0:
					this->_memory.setPosition(10, 0);
					break;
				case sf::Keyboard::Num1:
					this->_memory.setPosition(10, -(0x1000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num2:
					this->_memory.setPosition(10, -(0x2000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num3:
					this->_memory.setPosition(10, -(0x3000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num4:
					this->_memory.setPosition(10, -(0x4000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num5:
					this->_memory.setPosition(10, -(0x5000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num6:
					this->_memory.setPosition(10, -(0x6000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num7:
					this->_memory.setPosition(10, -(0x7000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num8:
					this->_memory.setPosition(10, -(0x8000 / 0x20) * 19);
					break;
				case sf::Keyboard::Num9:
					this->_memory.setPosition(10, -(0x9000 / 0x20) * 19);
					break;
				case sf::Keyboard::A:
					this->_memory.setPosition(10, -(0xA000 / 0x20) * 19);
					break;
				case sf::Keyboard::B:
					this->_memory.setPosition(10, -(0xB000 / 0x20) * 19);
					break;
				case sf::Keyboard::C:
					this->_memory.setPosition(10, -(0xC000 / 0x20) * 19);
					break;
				case sf::Keyboard::D:
					this->_memory.setPosition(10, -(0xD000 / 0x20) * 19);
					break;
				case sf::Keyboard::E:
					this->_memory.setPosition(10, -(0xE000 / 0x20) * 19);
					break;
				case sf::Keyboard::F:
					this->_memory.setPosition(10, -(0xF000 / 0x20) * 19);
					break;
				default:
					this->_memory.setPosition(10, 0);
				}
		}
		this->_memoryWindow.draw(this->_memory);
	}
}