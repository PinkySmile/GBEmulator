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
		sf::Text _registers;
		std::thread _displayThread;

		static const std::vector<unsigned char> _instrSize;

		//! Affiche le registre donné sur l'entrée standard
		void _dispVar(const std::string &name);
		//! Change la valeur de force de la variable donnée dans le CPU
		void _setVar(const std::string &name, unsigned short value);
		//! Verifie si la commande est valide puis appelle processCommandLine
		void _checkCommands(bool &dbg, std::istream &stream = std::cin);
		//! Affiche l'instruction en cours d'éxecution
		void _displayCurrentLine(std::ostream &stream = std::cout);
		//! Affiche l'instruction en cours d'éxecution
		void _displayCurrentLine(unsigned short address, std::ostream &stream = std::cout);
		//! Sépare la ligne de commande en respectant les quotes (comme un shell)
		static std::vector<std::string> _splitCommand(const std::string& line);
		//! Affiche l'instruction sur la fenetre du débugger
		void _drawInstruction(sf::RenderWindow &_debugWindow);
		//! Affiche l'état de la mémoire sur la fenetre du débugger
		void _drawMemory(sf::RenderWindow &_debugWindow);
		//! Affiche l'état des registres sur la fenetre du débugger
		void _drawRegisters(sf::RenderWindow &_debugWindow);
		//! Petmet d'utiliser les commandes en raccourcis de clavier sur le débugger
		void _handleWindowCommands(sf::RenderWindow &_debugWindow);
		//! Affiche le contenu de la Vram sur la fenetre du débugger
		void _drawVram(sf::RenderWindow &_debugWindow);
		//! Affiche l'état des palette sur la fenetre du débugger
		void _displayPalette(sf::RenderWindow &_debugWindow, float x, float y, const std::vector<GBEmulator::Graphics::RGBColor> &palette, bool transparent);
		//! Affiche la VRAM en utilisant la palette.
		void _displayVRAMContent(sf::RenderWindow &_debugWindow, float x, float y, const std::vector<GBEmulator::Graphics::RGBColor> &palette, bool transparent);
		//! Affiche l'état de la window sur la fenetre du débugger.
		void _displayWindow(sf::RenderWindow &_debugWindow, float x, float y);
		//! Affiche l'état du background sur la fenetre du débugger.
		void _displayBackground(sf::RenderWindow &_debugWindow, float x, float y);

	public:
		//! Constructeur du debugger
		Debugger(CPU &cpu, Graphics::ILCD &window, Input::JoypadEmulator &input);
		//! Destructeur du debugger
		~Debugger();

		//! Lance la commande donnée en paramètre
		bool processCommandLine(const std::string& line);
		//! Renvoie true ou false si un breakpoint a été set
		bool checkBreakPoints();
		//! Lance la session de débuggage
		int startDebugSession();
	};
}

#endif //GBEMULATOR_DEBUGGER_HPP
