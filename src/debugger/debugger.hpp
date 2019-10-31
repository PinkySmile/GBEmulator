/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.hpp
*/

#ifndef GBEMULATOR_DEBUGGER_HPP
#define GBEMULATOR_DEBUGGER_HPP

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
		unsigned _timer;
		Graphics::ILCD &_window;
		Input::JoypadEmulator &_input;
		std::string _lastCmd;
		std::vector<unsigned short> _breakPoints;

		static std::vector<std::string> _splitCommand(const std::string& line);

	public:
		Debugger(CPU &cpu, Graphics::ILCD &window, Input::JoypadEmulator &input);

		bool processCommandLine(const std::string& line);
		bool checkBreakPoints();
		int startDebugSession();
	};
}

#endif //GBEMULATOR_DEBUGGER_HPP
