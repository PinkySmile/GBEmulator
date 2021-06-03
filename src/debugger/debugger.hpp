/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** debugger.hpp
*/

#ifndef GBEMULATOR_DEBUGGER_HPP
#define GBEMULATOR_DEBUGGER_HPP

#include <stack>
#include <thread>
#include "../ProcessingUnits/CPU.hpp"
#include "CompiledCondition.hpp"

namespace GBEmulator::Debugger
{
	//! @brief Exception de base du Debugger.
	class Exception : public standard::exception {
	private:
		standard::string _msg;

	public:
		Exception(const standard::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	//! @brief La commande saisie n'a pas été reconnue.
	class CommandNotFoundException : public Exception {
	public:
		CommandNotFoundException(const standard::string &msg) : Exception(msg) {};
	};

	//! @brief Debugger de CPU.
	class Debugger {
	private:
		bool _checkForStackCorruption = false;
		standard::stack<unsigned short> _latest;
		standard::stack<unsigned short> _expectedPcAtRet;
		standard::vector<unsigned short> _jumpList;
		standard::vector<unsigned short> _ignoredCorruptedStackAddress;
		standard::vector<standard::shared_ptr<Operation>> _condBreakPoints;
		standard::vector<unsigned short> _oldpcs{64};
		//! @brief Le CPU à débugger.
		CPU &_cpu;
		//! @brief Utilisé pour ralentir la vitesse du CPU.
		float _rate = 1;
		//! @brief La fenêtre sur laquelle le GPU affiche.
		Graphics::ILCD &_window;
		//! @brief Le joypad utilisé par le CPU.
		Input::JoypadEmulator &_input;
		//! @brief La dernière commande éxecutée.
		standard::string _lastCmd;
		//! @brief Le point d'arrêts placés.
		standard::vector<unsigned short> _breakPoints;
		//! @brief Adresse de début de la mémoire affichée.
		unsigned short _memBeg;
		standard::thread _cpuThread;
		unsigned _timer = 0;

		//! @brief Taille en byte des opcodes.
		static const standard::vector<unsigned char> _instrSize;

		//! Affiche le registre donné sur l'entrée standard
		//! @param name Nom du registre à afficher.
		//! Les registres pouvant être affichés sont:
		//! a, b, c, d, e, f, h, l, af, bc, de, hl, sp, pc.
		//! Si la variable n'est pas dans cette liste, alors name est
		//! l'adresse en hexadécimal à déréferencer et afficher le contenu.
		void _dispVar(const standard::string &name);
		//! Change la valeur de force de la variable donnée dans le CPU
		//! @param name Nom du registre à afficher.
		//! Les registres pouvant être affichés sont:
		//! a, b, c, d, e, f, h, l, af, bc, de, hl, sp, pc.
		//! Si la variable n'est pas dans cette liste, alors name est
		//! l'adresse en hexadécimal à déréferencer et afficher le contenu.
		//! @param value La nouvelle valeur à assigner au registre.
		void _setVar(const standard::string &name, unsigned short value);
		//! Récupère la prochaine commande dans le flux et appelle processCommandLine
		//! @param dbg Réference vers le booléen à modifier si l'execution normal est reprise.
		//! @param stream Flux de donnée à utiliser pour recuperer la prochaine commande.
		void _checkCommands(bool &dbg, standard::istream &stream = standard::cin);
		//! Affiche l'instruction en cours d'éxecution ainsi que son adresse.
		void _displayCurrentLine(standard::ostream &stream = std::cout);
		//! Affiche l'instruction à l'adresse d'éxecution ainsi que son adresse.
		//! @param address Addresse de l'instruction à afficher.
		//! @param stream Flux à utiliser pour l'affichage.
		void _displayCurrentLine(uint16_t address, standard::ostream &stream = std::cout);
		//! Sépare la ligne de commande en respectant les quotes (comme un shell)
		//! @param line Ligne à séparer.
		//! @return Un tableau des élements une fois séparés.
		static standard::vector<standard::string> _splitCommand(const standard::string& line);

		bool _executeNextInstruction(bool resetClock);

	public:
		//! Constructeur du debugger
		Debugger(const standard::string &programPath, CPU &cpu, Graphics::ILCD &window, Input::JoypadEmulator &input);
		//! Destructeur du debugger
		~Debugger();

		//! Lance la commande donnée en paramètre
		//! @param line Commande à executer.
		//! @throw CommandNotFoundException
		bool processCommandLine(const standard::string& line);
		//! @brief Vérifie si un point d'arrêt a été atteint
		//! @return true si un point d'arrêt a été atteint. Sinon, false.
		bool checkBreakPoints();
		//! @brief Vérifie si un point d'arrêt conditionel a été atteint
		//! @return L'index du point d'arrêt atteint. Si aucun point d'arrêt n'est atteint, -1.
		int checkConditionalBreakPoints();
		//! Lance la session de débuggage
		int startDebugSession();
	};
}

#endif //GBEMULATOR_DEBUGGER_HPP
