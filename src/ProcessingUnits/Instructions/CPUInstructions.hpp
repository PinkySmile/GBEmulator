/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.hpp
*/

#ifndef GBEMULATOR_CPUINSTRUCTIONS_HPP
#define GBEMULATOR_CPUINSTRUCTIONS_HPP

#ifdef ARDUINO
#include <stdint.h>
#else
#include <cstdint>
#endif
#include "../CPU.hpp"

#define ERRORED_DURATION 255
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

#ifdef __cpp_exceptions
	//! @brief L'instruction STOP donnée est mal formée.
	class InvalidSTOPException : public CPU::InvalidOpcodeException {
	private:
		standard::string _msg;

	public:
		InvalidSTOPException(const standard::string &msg, uint16_t address, uint8_t arg) :
			CPU::InvalidOpcodeException(0x1000U | arg, address),
			_msg(msg)
		{};

		const char *what() const noexcept override
		{
			return (InvalidOpcodeException::what() + ("(" + this->_msg + ")")).c_str();
		}
	};
#endif
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
	uint8_t JR(CPU::Registers &reg, bool cond, char off);
	/*!
	 * Change la valeur de pc à address si cond est true.
	 * @param reg Registres CPU
	 * @param cond La condition de saut
	 * @param address Nouvelle valeur de pc
	 * @return Nombre de cycles écoulés
	 */
	uint8_t JP(CPU::Registers &reg, bool cond, uint16_t address);
	/*!
	 * Récupère la valeur d'un bit dans value
	 * @param reg Registres CPU
	 * @param value Valeur à récuperer le bit
	 * @param bit Numéro du bit (entre 0 et 7)
	 * @return Nombre de cycles écoulés
	 */
	uint8_t BIT(CPU::Registers &reg, uint8_t value, uint8_t bit);
	/*!
	 * Effectue un XOR entre le registre a et value et stock le resultat dans a
	 * @param reg Registres CPU.
	 * @param value Valeur à XOR avec a
	 * @return Nombre de cycles écoulés
	 */
	uint8_t XOR(CPU::Registers &reg, uint8_t value);
	/*!
	 * Met la value2 dans value1 avec des valeurs de 8 bits
	 * @param value1 Valeur à remplacer
	 * @param value2 Nouvelle valeur
	 * @return Nombre de cycles écoulés
	 */
	uint8_t LD8(uint8_t &value1, uint8_t value2);
	/*!
	 * Met la value2 dans value1 avec des valeurs de 16 bits
	 * @param value1 Valeur à remplacer
	 * @param value2 Nouvelle valeur
	 * @return Nombre de cycles écoulés
	 */
	uint8_t LD16(uint16_t &value1, uint16_t value2);
	/*!
	 * Effectue un ET binaire entre value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t AND8(CPU::Registers &reg, uint8_t &value1, uint8_t value2);
	/*!
	 * Effectue un OU binaire entre value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t OR8(CPU::Registers &reg, uint8_t &value1, uint8_t value2);
	/*!
	 * Additionne value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t ADD8(CPU::Registers &reg, uint8_t &value1, uint8_t value2, bool carry);
	/*!
	 * Soustrait value2 à value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SUB8(CPU::Registers &reg, uint8_t &value1, uint8_t value2, bool carry);
	/*!
	 * Additionne value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t ADD16(CPU::Registers &reg, uint16_t &value1, uint16_t value2);
	/*!
	 * Soustrait value2 à value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SUB16(CPU::Registers &reg, uint16_t &value1, uint16_t value2);
	/*!
	 * Incrémente value
	 * @param reg Registres CPU
	 * @param value Valeur incrémentée
	 * @return Nombre de cycles écoulés
	 */
	uint8_t INC8(CPU::Registers &reg, uint8_t &value);
	/*!
	 * Décrémente value
	 * @param reg Registres CPU
	 * @param value Valeur décrémentée
	 * @return Nombre de cycles écoulés
	 */
	uint8_t DEC8(CPU::Registers &reg, uint8_t &value);
	/*!
	 * Incrémente value
	 * @param value Valeur incrémentée
	 * @return Nombre de cycles écoulés
	 */
	uint8_t INC16(uint16_t &value);
	/*!
	 * Décrémente value
	 * @param value Valeur Décrémentée
	 * @return Nombre de cycles écoulés
	 */
	uint8_t DEC16(uint16_t &value);
	/*!
	 * Incrémente la valeur pointée par address
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la valeur à incrementer
	 * @return Nombre de cycles écoulés
	 */
	uint8_t INCPTR(CPU &cpu, CPU::Registers &reg, uint16_t address);
	/*!
	 * Décrémente la valeur pointée par address
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la valeur à décrementer
	 * @return Nombre de cycles écoulés
	 */
	uint8_t DECPTR(CPU &cpu, CPU::Registers &reg, uint16_t address);
	/*!
	 * Écris value à address
	 * @param cpu CPU
	 * @param address Adresse à écrire
	 * @param value Value à écrire
	 * @return Nombre de cycles écoulés
	 */
	uint8_t LD8toPTR(CPU &cpu, uint16_t address, uint8_t value);
	/*!
	 * Lis la valeur à address et la place dans value
	 * @param cpu CPU
	 * @param value Valeur à remplacer
	 * @param address Adresse à lire
	 * @return Nombre de cycles écoulés
	 */
	uint8_t LD8fromPTR(CPU &cpu, uint8_t &value, uint16_t address);
	/*!
	 * Écris value à address
	 * @param cpu CPU
	 * @param address Adresse à écrire
	 * @param value Value à écrire
	 * @return Nombre de cycles écoulés
	 */
	uint8_t LD16toPTR(CPU &cpu, uint16_t address, uint16_t value);
	/*!
	 * Lis la valeur à address et la place dans value
	 * @param cpu CPU
	 * @param value Valeur à remplacer
	 * @param address Adresse à lire
	 * @return Nombre de cycles écoulés
	 */
	uint8_t LD16fromPTR(CPU &cpu, uint16_t &value, uint16_t address);
	/*!
	 * Affectue un appel à la fonction pointé par address.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la fonction
	 * @return Nombre de cycles écoulés
	 */
	uint8_t CALL(CPU &cpu, CPU::Registers &reg, uint16_t address);
	/*!
	 * Affectue un appel à la fonction pointé par address si cond est true.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param cond Condition de saut.
	 * @param address Adresse de la fonction
	 * @return Nombre de cycles écoulés
	 */
	uint8_t CALLC(CPU &cpu, CPU::Registers &reg, bool cond, uint16_t address);
	/*!
	 * Pousse value dans la pile.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param value Valeur à pousser.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t PUSH(CPU &cpu, CPU::Registers &reg, uint16_t value);
	/*!
	 * Retire value de la pile.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param value Valeur rétirée.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t POP(CPU &cpu, CPU::Registers &reg, uint16_t &value);
	/*!
	 * Compare a et value
	 * @param reg Registres CPU
	 * @param value Valeur à comparer.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t CP(CPU::Registers &reg, uint8_t value);
	/*!
	 * Reset le bit 'bit' de val
	 * @param val Valeur à changer
	 * @param bit Bit à reset
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RES(uint8_t &val, uint8_t bit);
	/*!
	 * Set le bit 'bit' de val.
	 * @param val Valeur à changer
	 * @param bit Bit à changer
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SETB(uint8_t &val, uint8_t bit);
	/*!
	 * Retourne de l'appel d'une fonction si cond est true.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param cond Condition de retour.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RET(CPU &cpu, CPU::Registers &reg, bool cond);
	/*!
	 * Pivote les bits de a à gauche. Le bit 7 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RLCA(CPU::Registers &re);
	/*!
	 * Pivote les bits de a à droite. Le bit 0 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RRCA(CPU::Registers &re);
	/*!
	 * Pivote les bits de a à gauche. Le flag c est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RLA(CPU::Registers &re);
	/*!
	 * Pivote les bits de a à droite. Le flag c est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RRA(CPU::Registers &re);
	/*!
	 * Pivote les bits de value à gauche. Le bit 7 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RLC(CPU::Registers &re, uint8_t &val);
	/*!
	 * Pivote les bits de value à droite. Le bit 0 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RRC(CPU::Registers &re, uint8_t &val);
	/*!
	 * Pivote les bits de value à gauche. Le flag c est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RL(CPU::Registers &re, uint8_t &val);
	/*!
	 * Pivote les bits de value à droite. Le flag c est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t RR(CPU::Registers &re, uint8_t &val);
	/*!
	 * Pivote les bits de val à gauche. value est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 0
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SL(CPU::Registers &re, uint8_t &val, bool value);
	/*!
	 * Pivote les bits de val à gauche. value est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 7
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SR(CPU::Registers &re, uint8_t &val, bool value);
	/*!
	 * Pivote les bits de a à gauche. 0 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 0
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SLA(CPU::Registers &re, uint8_t &val);
	/*!
	 * Pivote les bits de a à droite. 1 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SRA(CPU::Registers &re, uint8_t &val);
	/*!
	 * Échange les 4 premiers bits et les 4 derniers bits de val.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SWAP(CPU::Registers &re, uint8_t &val);
	/*!
	 * Pivote les bits de a à gauche. 1 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SRL(CPU::Registers &re, uint8_t &val);
	/*!
	 * Stop le CPU.
	 * @param cpu CPU
	 * @return Nombre de cycles écoulés
	 * @throw InvalidSTOPException
	 */
	uint8_t STOP(CPU &cpu);
	/*!
	 * Ajuste a pour les addition et soustractions en BCD.
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	uint8_t DAA(CPU::Registers &reg, uint8_t &val);
	/*!
	 * Inverse les bits de a.
	 * @param reg Registres CPU.
	 * @return Nombre de cycles écoulés
	 */
	uint8_t CPL(CPU::Registers &reg);
	/*!
	 * Effectue une addition sur un nombre 16 bit non signé et un nombre 8 bit signé et stock le résultat dans value1.
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	uint8_t SPECIAL_ADD(CPU::Registers &reg, uint16_t &value1, char value2);
	/*!
	 * Execute une fonction sur la valeur pointé par address
	 * @param cpu CPU
	 * @param address Adresse sur laquelle executer fct
	 * @param fct Fonction à executer
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	uint8_t executeOnPtr(CPU &cpu, uint16_t address, uint8_t (&fct)(CPU::Registers &, uint8_t &), CPU::Registers &reg);

	template <typename ...args>
	/*!
	 * Execute une fonction sur la valeur pointé par address
	 * @param cpu CPU
	 * @param address Adresse sur laquelle executer fct
	 * @param fct Fonction à executer
	 * @param arguments Arguments de fct
	 * @return Nombre de cycles écoulés
	 */
	uint8_t executeOnPtr(CPU &cpu, uint16_t address, uint8_t (&fct)(uint8_t &, args...), args... arguments)
	{
		uint8_t value = cpu.read(address);
		uint8_t time = fct(value, arguments...);

		cpu.write(address, value);
		return time + INDIRECTION_CYCLE_DURATION * 2;
	}
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
