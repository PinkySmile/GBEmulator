/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.cpp
*/

#ifndef _WIN32
#	include <sys/select.h>
#define closesocket(socket) close(socket)
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
		2, 1, 1, 1, 1, 1, 2, 1, 3, 1, 3, 1, 1, 1, 2, 1,
		2, 1, 1, 1, 1, 1, 2, 1, 3, 1, 3, 1, 1, 1, 2, 1
	};

	Debugger::Debugger(GBEmulator::CPU &cpu, GBEmulator::Graphics::ILCD &window, GBEmulator::Input::JoypadEmulator &input) :
		_cpu(cpu),
		_window(window),
		_input(input)
	{
		this->_memBeg = 0x0000;

		this->_font.loadFromFile("../courier.ttf");

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
		} else if (args[0] == "slow") {
			this->_cpu.update();
			this->_baseTimer = -1000;
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

	Debugger::~Debugger()
	{
		if (this->_displayThread.joinable())
			this->_displayThread.join();
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
			if (this->processCommandLine(line))
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

		this->_displayCurrentLine();
		std::cout << "gdbgb> ";
		std::cout.flush();
		while (!this->_window.isClosed()) {
			try {
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
						this->_handleWindowCommands(_debugWindow);
					} else {
						this->_checkCommands(dbg);
						if (dbg) {
							std::cout << "gdbgb> ";
							std::cout.flush();
						}
					}
				}

				if (!dbg && this->checkBreakPoints()) {
					auto it = std::find(this->_breakPoints.begin(), this->_breakPoints.end(), this->_cpu._registers.pc);

					std::cout << "Hit breakpoint #" << (it - this->_breakPoints.begin()) << " at $" << Instructions::intToHex(*it, 4) << std::endl;
					this->_displayCurrentLine();
					std::cout << "gdbgb> ";
					std::cout.flush();
					dbg = true;
				}

				if (!dbg) {
					this->_cpu.update();
					if (++this->_timer > this->_baseTimer) {
						for (int i = 0; i == 0 || i > this->_baseTimer; i--) {
							this->_timer = 0;

							_debugWindow.clear(sf::Color::White);
							this->_drawInstruction(_debugWindow);
							this->_drawMemory(_debugWindow);
							this->_drawRegisters(_debugWindow);
							this->_drawVram(_debugWindow);
							_debugWindow.display();
							this->_handleWindowCommands(_debugWindow);
							if (this->_input.isButtonPressed(Input::ENABLE_DEBUGGING)) {
								dbg = true;
								this->_displayCurrentLine();
								std::cout << "gdbgb> ";
								std::cout.flush();
							}
						}
					}
				}
			} catch (CPU::InvalidOpcodeException &e) {
				dbg = true;
				std::cout << e.what() << std::endl;
				this->_displayCurrentLine();
				std::cout << "gdbgb> ";
				std::cout.flush();
			}
		}

		if (this->_displayThread.joinable())
			this->_displayThread.join();
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
					this->_baseTimer += 1;
					break;
				case sf::Keyboard::M:
					this->_baseTimer -= 1;
					break;
				case sf::Keyboard::O:
					this->_baseTimer += 10;
					break;
				case sf::Keyboard::L:
					this->_baseTimer -= 10;
					break;
				case sf::Keyboard::K:
					this->_baseTimer = -1000;
					break;
				case sf::Keyboard::I:
					this->_baseTimer = 1500;
					break;
				default:
					break;
				}
		}
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

		this->_registers.setString(ss.str());
		_debugWindow.draw(this->_registers);
	}

	void Debugger::_drawVram(sf::RenderWindow &_debugWindow)
	{
		sf::Sprite sprite;
		sf::RectangleShape cam(sf::Vector2f(240, 216));
		sf::RectangleShape square(sf::Vector2f(800, 1000));
		int tileNbr = 0;

		square.setFillColor(sf::Color::Blue);
		square.setPosition(1200, 0);
		_debugWindow.draw(square);

		sprite.setScale(1.5, 1.5);
		sprite.setPosition(1465, 450);

		auto map = this->_cpu._gpu._getTileMap(this->_cpu._gpu._control & 0b00001000U);

		this->_cpu._gpu._updateTiles();
		for (int i = 0; i < 32 * 32; i++) {
			sprite.setTexture(
				reinterpret_cast<Graphics::LCDSFML&>(this->_cpu._gpu._screen)._BGTexture[
					!(this->_cpu._gpu._control & 0b00010000U) ?
					static_cast<char>(map[i]) + 0x100 :
					map[i]
				]
			);
			_debugWindow.draw(sprite);
			sprite.move(8 * 1.5, 0);
			tileNbr++;
			if (tileNbr == 32) {
				tileNbr = 0;
				sprite.setPosition(1465, sprite.getPosition().y);
				sprite.move(0, 8 * 1.5);
			}
		}
		cam.setFillColor(sf::Color::Transparent);
		cam.setOutlineColor(sf::Color::Red);
		cam.setOutlineThickness(4);
		for (int i = 0; i < 4; i++) {
			cam.setPosition(1465 + this->_cpu._gpu._scrollX * 1.5 - 384 * (i % 2), 450 + this->_cpu._gpu._scrollY * 1.5 - 384 * (i / 2));
			if (1465 + this->_cpu._gpu._scrollX * 1.5 - 384 * (i % 2) > 1200)
				_debugWindow.draw(cam);
		}

		square.setSize({1200, 446});
		_debugWindow.draw(square);

		square.setSize({261, 1000});
		_debugWindow.draw(square);

		square.setPosition(1200, 838);
		square.setSize({1200, 450});
		_debugWindow.draw(square);

		square.setPosition(1853, 0);
		square.setSize({1200, 1000});
		_debugWindow.draw(square);

		sprite.setPosition(1205, 5);
		sprite.setScale(2, 2);

		for (auto &e : reinterpret_cast<Graphics::LCDSFML&>(this->_cpu._gpu._screen)._palette0Texture) {
			sprite.setTexture(e);
			_debugWindow.draw(sprite);
			sprite.move(8 * 2, 0);
			tileNbr++;
			if (tileNbr == 16) {
				tileNbr = 0;
				sprite.setPosition(1205, sprite.getPosition().y);
				sprite.move(0, 8 * 2);
			}
		}

		sprite.setPosition(1463, 5);
		for (auto &e : reinterpret_cast<Graphics::LCDSFML&>(this->_cpu._gpu._screen)._palette1Texture) {
			sprite.setTexture(e);
			_debugWindow.draw(sprite);
			sprite.move(8 * 2, 0);
			tileNbr++;
			if (tileNbr == 16) {
				tileNbr = 0;
				sprite.setPosition(1463, sprite.getPosition().y);
				sprite.move(0, 8 * 2);
			}
		}

		sprite.setPosition(1205, 450);
		for (auto &e : reinterpret_cast<Graphics::LCDSFML&>(this->_cpu._gpu._screen)._BGTexture) {
			sprite.setTexture(e);
			_debugWindow.draw(sprite);
			sprite.move(8 * 2, 0);
			tileNbr++;
			if (tileNbr == 16) {
				tileNbr = 0;
				sprite.setPosition(1205, sprite.getPosition().y);
				sprite.move(0, 8 * 2);
			}
		}
	}
}