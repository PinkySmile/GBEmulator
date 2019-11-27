/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.hpp
*/

#ifndef GBEMULATOR_DEBUGGER_HPP
#define GBEMULATOR_DEBUGGER_HPP

#include <thread>
#include "../ProcessingUnits/CPU.hpp"

namespace GBEmulator::Debugger
{
	class Exception : public std::exception {
	private:
		std::string _msg;

	public:
		Exception(const std::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	class CommandNotFoundException : public Exception {
	public:
		CommandNotFoundException(const std::string &msg) : Exception(msg) {};
	};

	class Debugger {
	private:
		CPU &_cpu;
		int _timer = 0;
		int _baseTimer = 0;
		Graphics::ILCD &_window;
		Input::JoypadEmulator &_input;
		std::string _lastCmd;
		std::vector<unsigned short> _breakPoints;
		sf::Font _font;
		std::vector<sf::Text> _texts;
		sf::Text _memory;
		unsigned short _memBeg;
		unsigned short _memEnd;
		sf::Text _registers;
		std::thread _displayThread;

		static const std::vector<unsigned char> _instrSize;

		void _dispVar(const std::string &name);
		void _setVar(const std::string &name, unsigned short value);
		void _checkCommands(bool &dbg, std::istream &stream = std::cin);
		void _displayCurrentLine(std::ostream &stream = std::cout);
		void _displayCurrentLine(unsigned short address, std::ostream &stream = std::cout);
		static std::vector<std::string> _splitCommand(const std::string& line);
		void _drawInstruction(sf::RenderWindow &_debugWindow);
		void _drawMemory(sf::RenderWindow &_debugWindow);
		void _drawRegisters(sf::RenderWindow &_debugWindow);
		void _handleWindowCommands(sf::RenderWindow &_debugWindow);
		void _drawVram(sf::RenderWindow &_debugWindow);
		char _getInstructionByLen(const std::string &str);

	public:
		Debugger(CPU &cpu, Graphics::ILCD &window, Input::JoypadEmulator &input);
		~Debugger();

		bool processCommandLine(const std::string& line);
		bool checkBreakPoints();
		int startDebugSession();
	};
}

#endif //GBEMULATOR_DEBUGGER_HPP
