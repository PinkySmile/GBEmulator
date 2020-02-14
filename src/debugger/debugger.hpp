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
	//! @brief Exception de base du Debugger.
	class Exception : public std::exception {
	private:
		std::string _msg;

	public:
		Exception(const std::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	//! @brief La commande saisie n'a pas été reconnue.
	class CommandNotFoundException : public Exception {
	public:
		CommandNotFoundException(const std::string &msg) : Exception(msg) {};
	};

	//! @brief Debugger de CPU.
	class Debugger {
	private:
		//! @brief Le CPU à débugger.
		CPU &_cpu;
		//! @brief Utilisé pour ralentir la vitesse du CPU.
		int _timer = 0;
		//! @brief La vitesse actuelle d'execution.
		int _baseTimer = 0;
		//! @brief La fenêtre sur laquelle le GPU affiche.
		Graphics::ILCD &_window;
		//! @brief Le joypad utilisé par le CPU.
		Input::JoypadEmulator &_input;
		//! @brief La dernière commande éxecutée.
		std::string _lastCmd;
		//! @brief Le point d'arrêts placés.
		std::vector<unsigned short> _breakPoints;
		//! @brief La police d'écriture chargée.
		sf::Font _font;
		//! @brief Contenu de la mémoire sous forme de text.
		sf::Text _memory;
		//! @brief Adresse de début de la mémoire affichée.
		unsigned short _memBeg;
		//! @brief Registres du CPU transformé en text.
		sf::Text _registers;

		//! @brief Taille en byte des opcodes.
		static const std::vector<unsigned char> _instrSize;

		//! Affiche le registre donné sur l'entrée standard
		//! @param name Nom du registre à afficher.
		//! Les registres pouvant être affichés sont:
		//! a, b, c, d, e, f, h, l, af, bc, de, hl, sp, pc.
		//! Si la variable n'est pas dans cette liste, alors name est
		//! l'adresse en hexadécimal à déréferencer et afficher le contenu.
		void _dispVar(const std::string &name);
		//! Change la valeur de force de la variable donnée dans le CPU
		//! @param name Nom du registre à afficher.
		//! Les registres pouvant être affichés sont:
		//! a, b, c, d, e, f, h, l, af, bc, de, hl, sp, pc.
		//! Si la variable n'est pas dans cette liste, alors name est
		//! l'adresse en hexadécimal à déréferencer et afficher le contenu.
		//! @param value La nouvelle valeur à assigner au registre.
		void _setVar(const std::string &name, unsigned short value);
		//! Récupère la prochaine commande dans le flux et appelle processCommandLine
		//! @param dbg Réference vers le booléen à modifier si l'execution normal est reprise.
		//! @param stream Flux de donnée à utiliser pour recuperer la prochaine commande.
		void _checkCommands(bool &dbg, std::istream &stream = std::cin);
		//! Affiche l'instruction en cours d'éxecution ainsi que son adresse.
		void _displayCurrentLine(std::ostream &stream = std::cout);
		//! Affiche l'instruction à l'adresse d'éxecution ainsi que son adresse.
		//! @param address Addresse de l'instruction à afficher.
		//! @param stream Flux à utiliser pour l'affichage.
		void _displayCurrentLine(unsigned short address, std::ostream &stream = std::cout);
		//! Sépare la ligne de commande en respectant les quotes (comme un shell)
		//! @param line Ligne à séparer.
		//! @return Un tableau des élements une fois séparés.
		static std::vector<std::string> _splitCommand(const std::string& line);
		//! Affiche l'instruction sur la fenetre du débugger
		//! @param _debugWindow Fenêtre sur laquelle afficher.
		void _drawInstruction(sf::RenderWindow &_debugWindow);
		//! Affiche l'état de la mémoire sur la fenetre du débugger
		//! @param _debugWindow Fenêtre sur laquelle afficher.
		void _drawMemory(sf::RenderWindow &_debugWindow);
		//! Affiche l'état des registres sur la fenetre du débugger
		//! @param _debugWindow Fenêtre sur laquelle afficher.
		void _drawRegisters(sf::RenderWindow &_debugWindow);
		//! Petmet d'utiliser les commandes en raccourcis de clavier sur le débugger
		//! @param _debugWindow Fenêtre sur laquelle récuperer les entrées.
		void _handleWindowCommands(sf::RenderWindow &_debugWindow);
		//! Affiche le contenu de la Vram sur la fenetre du débugger
		//! @param _debugWindow Fenêtre sur laquelle afficher.
		void _drawVram(sf::RenderWindow &_debugWindow);
		/*!
		 * Affiche l'état d'une palette sur la fenetre du débugger
		 * @param _debugWindow Fenêtre sur laquelle afficher
		 * @param x Position de la boîte en abcisses.
		 * @param y Position de la boîte en ordonnées
		 * @param palette Pallette de couleur à afficher.
		 * @param transparent Est-ce que la première couleur est transparente ?
		 */
		void _displayPalette(sf::RenderWindow &_debugWindow, float x, float y, const std::vector<GBEmulator::Graphics::RGBColor> &palette, bool transparent);
		/*!
		 * Affiche la VRAM en utilisant la palette.
		 * @param _debugWindow
		 * @param posx Position de la boîte en abcisses.
		 * @param posy Position de la boîte en ordonnées
		 * @param palette Pallette de couleur à afficher.
		 * @param transparent Est-ce que la première couleur est transparente ?
		 */
		void _displayVRAMContent(sf::RenderWindow &_debugWindow, float posx, float posy, const std::vector<GBEmulator::Graphics::RGBColor> &palette, bool transparent);
		//! Affiche l'état de la window sur la fenetre du débugger.
		//! @param _debugWindow Fenêtre sur laquelle afficher.
		//! @param posx Position de la boîte en abcisses.
		//! @param posy Position de la boîte en ordonnées
		void _displayWindow(sf::RenderWindow &_debugWindow, float posx, float posy);
		//! Affiche l'état du background sur la fenetre du débugger.
		//! @param _debugWindow Fenêtre sur laquelle afficher.
		//! @param posx Position de la boîte en abcisses.
		//! @param posy Position de la boîte en ordonnées
		void _displayBackground(sf::RenderWindow &_debugWindow, float posx, float posy);

	public:
		//! Constructeur du debugger
		Debugger(const std::string &programPath, CPU &cpu, Graphics::ILCD &window, Input::JoypadEmulator &input);
		//! Destructeur du debugger
		~Debugger();

		//! Lance la commande donnée en paramètre
		//! @param line Commande à executer.
		//! @throw CommandNotFoundException
		bool processCommandLine(const std::string& line);
		//! @brief Vérifie si un point d'arrêt a été atteint
		//! @return true si un point d'arrêt a été atteint. Sinon, false.
		bool checkBreakPoints();
		//! Lance la session de débuggage
		int startDebugSession();
	};
}

#endif //GBEMULATOR_DEBUGGER_HPP
