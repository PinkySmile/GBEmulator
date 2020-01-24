/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.hpp
*/

#ifndef GBEMULATOR_CPUINSTRUCTIONS_HPP
#define GBEMULATOR_CPUINSTRUCTIONS_HPP


#include <map>
#include <functional>
#include "../CPU.hpp"

#define LD_CYCLE_DURATION 4
#define NOP_CYCLE_DURATION 4
#define JUMP_CYCLE_DURATION 4
#define POP_CYCLE_DURATION 12
#define PUSH_CYCLE_DURATION 16
#define INDIRECTION_CYCLE_DURATION 4
#define FETCH_ARGUMENT8_CYLCE_DURATION 4
#define FETCH_ARGUMENT16_CYLCE_DURATION 8
#define BASIC_BIT_OPERATION_CYCLE_DURATION 4
#define ARITHMETIC_OPERATION_CYCLE_DURATION 4
#define COMPLEX_BIT_OPERATION_CYCLE_DURATION 8

namespace GBEmulator::Instructions
{
	//! @brief Valeur de changement pour un flag
	enum FlagValue {
		UNSET,
		SET,
		UNCHANGED
	};

	//! @brief L'instruction STOP donnée est mal formée.
	class InvalidSTOPException : public CPU::InvalidOpcodeException {
	private:
		std::string _msg;

	public:
		InvalidSTOPException(const std::string &msg, unsigned short address, unsigned char arg) :
			CPU::InvalidOpcodeException(0x1000U | arg, address),
			_msg(msg)
		{};

		const char *what() const noexcept override
		{
			return (InvalidOpcodeException::what() + ("(" + this->_msg + ")")).c_str();
		}
	};

	//! @brief Transforme un entier dans sa représentation hexadécimal.
	//! @param i Entier à convertir.
	//! @param size Nombre de chiffre minimum.
	//! @return La représentation hexadécimale de i.
	std::string intToHex(unsigned i, unsigned size = 2);
	/*!
	 * Change la valeur des flags dans le registre du CPU
	 * @param reg Registres du CPU
	 * @param z Nouvelle valeur pour z
	 * @param n Nouvelle valeur pour n
	 * @param h Nouvelle valeur pour h
	 * @param c Nouvelle valeur pour c
	 */
	void setFlags(CPU::Registers &reg, FlagValue z, FlagValue n, FlagValue h, FlagValue c);
	/*!
	 * Ajoute off à pc si cond est true.
	 * @param reg Registres CPU
	 * @param cond La condition de saut
	 * @param off Offset à ajouter à PC
	 * @return Nombre de cycles écoulés
	 */
	unsigned char JR(CPU::Registers &reg, bool cond, char off);
	/*!
	 * Change la valeur de pc à address si cond est true.
	 * @param reg Registres CPU
	 * @param cond La condition de saut
	 * @param address Nouvelle valeur de pc
	 * @return Nombre de cycles écoulés
	 */
	unsigned char JP(CPU::Registers &reg, bool cond, unsigned short address);
	/*!
	 * Récupère la valeur d'un bit dans value
	 * @param reg Registres CPU
	 * @param value Valeur à récuperer le bit
	 * @param bit Numéro du bit (entre 0 et 7)
	 * @return Nombre de cycles écoulés
	 */
	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit);
	/*!
	 * Effectue un XOR entre le registre a et value et stock le resultat dans a
	 * @param reg Registres CPU.
	 * @param value Valeur à XOR avec a
	 * @return Nombre de cycles écoulés
	 */
	unsigned char XOR(CPU::Registers &reg, unsigned char value);
	/*!
	 * Met la value2 dans value1 avec des valeurs de 8 bits
	 * @param value1 Valeur à remplacer
	 * @param value2 Nouvelle valeur
	 * @return Nombre de cycles écoulés
	 */
	unsigned char LD8(unsigned char &value1, unsigned char value2);
	/*!
	 * Met la value2 dans value1 avec des valeurs de 16 bits
	 * @param value1 Valeur à remplacer
	 * @param value2 Nouvelle valeur
	 * @return Nombre de cycles écoulés
	 */
	unsigned char LD16(unsigned short &value1, unsigned short value2);
	/*!
	 * Effectue un ET binaire entre value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char AND8(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	/*!
	 * Effectue un OU binaire entre value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char OR8(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	/*!
	 * Additionne value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char ADD8(CPU::Registers &reg, unsigned char &value1, unsigned char value2, bool carry);
	/*!
	 * Soustrait value2 à value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SUB8(CPU::Registers &reg, unsigned char &value1, unsigned char value2, bool carry);
	/*!
	 * Additionne value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char ADD16(CPU::Registers &reg, unsigned short &value1, unsigned short value2);
	/*!
	 * Soustrait value2 à value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SUB16(CPU::Registers &reg, unsigned short &value1, unsigned short value2);
	/*!
	 * Incrémente value
	 * @param reg Registres CPU
	 * @param value Valeur incrémentée
	 * @return Nombre de cycles écoulés
	 */
	unsigned char INC8(CPU::Registers &reg, unsigned char &value);
	/*!
	 * Décrémente value
	 * @param reg Registres CPU
	 * @param value Valeur décrémentée
	 * @return Nombre de cycles écoulés
	 */
	unsigned char DEC8(CPU::Registers &reg, unsigned char &value);
	/*!
	 * Incrémente value
	 * @param value Valeur incrémentée
	 * @return Nombre de cycles écoulés
	 */
	unsigned char INC16(unsigned short &value);
	/*!
	 * Décrémente value
	 * @param value Valeur Décrémentée
	 * @return Nombre de cycles écoulés
	 */
	unsigned char DEC16(unsigned short &value);
	/*!
	 * Incrémente la valeur pointée par address
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la valeur à incrementer
	 * @return Nombre de cycles écoulés
	 */
	unsigned char INCPTR(CPU &cpu, CPU::Registers &reg, unsigned short address);
	/*!
	 * Décrémente la valeur pointée par address
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la valeur à décrementer
	 * @return Nombre de cycles écoulés
	 */
	unsigned char DECPTR(CPU &cpu, CPU::Registers &reg, unsigned short address);
	/*!
	 * Écris value à address
	 * @param cpu CPU
	 * @param address Adresse à écrire
	 * @param value Value à écrire
	 * @return Nombre de cycles écoulés
	 */
	unsigned char LD8toPTR(CPU &cpu, unsigned short address, unsigned char value);
	/*!
	 * Lis la valeur à address et la place dans value
	 * @param cpu CPU
	 * @param value Valeur à remplacer
	 * @param address Adresse à lire
	 * @return Nombre de cycles écoulés
	 */
	unsigned char LD8fromPTR(CPU &cpu, unsigned char &value, unsigned short address);
	/*!
	 * Écris value à address
	 * @param cpu CPU
	 * @param address Adresse à écrire
	 * @param value Value à écrire
	 * @return Nombre de cycles écoulés
	 */
	unsigned char LD16toPTR(CPU &cpu, unsigned short address, unsigned short value);
	/*!
	 * Lis la valeur à address et la place dans value
	 * @param cpu CPU
	 * @param value Valeur à remplacer
	 * @param address Adresse à lire
	 * @return Nombre de cycles écoulés
	 */
	unsigned char LD16fromPTR(CPU &cpu, unsigned short &value, unsigned short address);
	/*!
	 * Affectue un appel à la fonction pointé par address.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la fonction
	 * @return Nombre de cycles écoulés
	 */
	unsigned char CALL(CPU &cpu, CPU::Registers &reg, unsigned short address);
	/*!
	 * Affectue un appel à la fonction pointé par address si cond est true.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param cond Condition de saut.
	 * @param address Adresse de la fonction
	 * @return Nombre de cycles écoulés
	 */
	unsigned char CALLC(CPU &cpu, CPU::Registers &reg, bool cond, unsigned short address);
	/*!
	 * Pousse value dans la pile.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param value Valeur à pousser.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char PUSH(CPU &cpu, CPU::Registers &reg, unsigned short value);
	/*!
	 * Retire value de la pile.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param value Valeur rétirée.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char POP(CPU &cpu, CPU::Registers &reg, unsigned short &value);
	/*!
	 * Compare a et value
	 * @param reg Registres CPU
	 * @param value Valeur à comparer.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char CP(CPU::Registers &reg, unsigned char value);
	/*!
	 * Reset le bit 'bit' de val
	 * @param val Valeur à changer
	 * @param bit Bit à reset
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RES(unsigned char &val, unsigned char bit);
	/*!
	 * Set le bit 'bit' de val.
	 * @param val Valeur à changer
	 * @param bit Bit à changer
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SETB(unsigned char &val, unsigned char bit);
	/*!
	 * Retourne de l'appel d'une fonction si cond est true.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param cond Condition de retour.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RET(CPU &cpu, CPU::Registers &reg, bool cond);
	/*!
	 * Pivote les bits de a à gauche. Le bit 7 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RLCA(CPU::Registers &re);
	/*!
	 * Pivote les bits de a à droite. Le bit 0 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RRCA(CPU::Registers &re);
	/*!
	 * Pivote les bits de a à gauche. Le flag c est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RLA(CPU::Registers &re);
	/*!
	 * Pivote les bits de a à droite. Le flag c est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RRA(CPU::Registers &re);
	/*!
	 * Pivote les bits de value à gauche. Le bit 7 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RLC(CPU::Registers &re, unsigned char &val);
	/*!
	 * Pivote les bits de value à droite. Le bit 0 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RRC(CPU::Registers &re, unsigned char &val);
	/*!
	 * Pivote les bits de value à gauche. Le flag c est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RL(CPU::Registers &re, unsigned char &val);
	/*!
	 * Pivote les bits de value à droite. Le flag c est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char RR(CPU::Registers &re, unsigned char &val);
	/*!
	 * Pivote les bits de val à gauche. value est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 0
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SL(CPU::Registers &re, unsigned char &val, bool value);
	/*!
	 * Pivote les bits de val à gauche. value est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 7
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SR(CPU::Registers &re, unsigned char &val, bool value);
	/*!
	 * Pivote les bits de a à gauche. 0 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 0
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SLA(CPU::Registers &re, unsigned char &val);
	/*!
	 * Pivote les bits de a à droite. 1 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SRA(CPU::Registers &re, unsigned char &val);
	/*!
	 * Échange les 4 premiers bits et les 4 derniers bits de val.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SWAP(CPU::Registers &re, unsigned char &val);
	/*!
	 * Pivote les bits de a à gauche. 1 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SRL(CPU::Registers &re, unsigned char &val);
	/*!
	 * Stop le CPU.
	 * @param cpu CPU
	 * @return Nombre de cycles écoulés
	 * @throw InvalidSTOPException
	 */
	unsigned char STOP(CPU &cpu);
	/*!
	 * Ajuste a pour les addition et soustractions en BCD.
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	unsigned char DAA(CPU::Registers &reg, unsigned char &val);
	/*!
	 * Inverse les bits de a.
	 * @param reg Registres CPU.
	 * @return Nombre de cycles écoulés
	 */
	unsigned char CPL(CPU::Registers &reg);
	/*!
	 * Effectue une addition sur un nombre 16 bit non signé et un nombre 8 bit signé et stock le résultat dans value1.
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	unsigned char SPECIAL_ADD(CPU::Registers &reg, unsigned short &value1, char value2);
	/*!
	 * Execute une fonction sur la valeur pointé par address
	 * @param cpu CPU
	 * @param address Adresse sur laquelle executer fct
	 * @param fct Fonction à executer
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	unsigned char executeOnPtr(CPU &cpu, unsigned short address, unsigned char (&fct)(CPU::Registers &, unsigned char &), CPU::Registers &reg);

	template <typename ...args>
	/*!
	 * Execute une fonction sur la valeur pointé par address
	 * @param cpu CPU
	 * @param address Adresse sur laquelle executer fct
	 * @param fct Fonction à executer
	 * @param arguments Arguments de fct
	 * @return Nombre de cycles écoulés
	 */
	unsigned char executeOnPtr(CPU &cpu, unsigned short address, unsigned char (&fct)(unsigned char &, args...), args... arguments)
	{
		unsigned char value = cpu.read(address);
		unsigned char time = fct(value, arguments...);

		cpu.write(address, value);
		return time + INDIRECTION_CYCLE_DURATION * 2;
	}

	extern const std::function<std::string (const CPU &, unsigned short address)> _instructionsString[256];
	extern const std::function<std::string (const CPU &, unsigned short address)> _bitLevelInstructionsString[256];
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
