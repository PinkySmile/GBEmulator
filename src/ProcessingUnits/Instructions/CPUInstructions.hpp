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
	inline void setFlags(CPU::Registers &reg, FlagValue z, FlagValue n, FlagValue h, FlagValue c)
	{
		reg._ = 0;
		if (z != UNCHANGED)
			reg.fz = z;
		if (n != UNCHANGED)
			reg.fn = n;
		if (h != UNCHANGED)
			reg.fh = h;
		if (c != UNCHANGED)
			reg.fc = c;
	}
	/*!
	 * Ajoute off à pc si cond est true.
	 * @param reg Registres CPU
	 * @param cond La condition de saut
	 * @param off Offset à ajouter à PC
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t JR(CPU::Registers &reg, bool cond, int8_t off)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc += off;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}
	/*!
	 * Change la valeur de pc à address si cond est true.
	 * @param reg Registres CPU
	 * @param cond La condition de saut
	 * @param address Nouvelle valeur de pc
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t JP(CPU::Registers &reg, bool cond, uint16_t address)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc = address;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}
	/*!
	 * Récupère la valeur d'un bit dans value
	 * @param reg Registres CPU
	 * @param value Valeur à récuperer le bit
	 * @param bit Numéro du bit (entre 0 et 7)
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t BIT(CPU::Registers &reg, uint8_t value, uint8_t bit)
	{
		setFlags(reg, ((1U << bit) & value) == 0 ? SET : UNSET, UNSET, SET, UNCHANGED);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Effectue un XOR entre le registre a et value et stock le resultat dans a
	 * @param reg Registres CPU.
	 * @param value Valeur à XOR avec a
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t XOR(CPU::Registers &reg, uint8_t value)
	{
		reg.a ^= value;
		setFlags(reg, reg.a == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Met la value2 dans value1 avec des valeurs de 8 bits
	 * @param register_ Valeur à remplacer
	 * @param value Nouvelle valeur
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t LD8(uint8_t &register_, uint8_t value)
	{
		register_ = value;
		return LD_CYCLE_DURATION;
	}
	/*!
	 * Met la value2 dans value1 avec des valeurs de 16 bits
	 * @param register_ Valeur à remplacer
	 * @param value2 Nouvelle valeur
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t LD16(uint16_t &register_, uint16_t value)
	{
		register_ = value;
		return LD_CYCLE_DURATION;
	}
	/*!
	 * Effectue un ET binaire entre value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t AND8(CPU::Registers &reg, uint8_t &value1, uint8_t value2)
	{
		value1 &= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, SET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Effectue un OU binaire entre value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t OR8(CPU::Registers &reg, uint8_t &value1, uint8_t value2)
	{
		value1 |= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Additionne value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t ADD8(CPU::Registers &reg, uint8_t &value1, uint8_t value2, bool carry)
	{
		bool halfCarry = (((value1 & 0xFU) + (value2 & 0xFU) + carry) & 0x10U) == 0x10U;

		setFlags(
			reg,
			(value1 + value2 + carry) % 0x100 == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 + value2 + carry > 0xFF ? SET : UNSET
		);
		value1 += value2 + carry;
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Soustrait value2 à value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SUB8(CPU::Registers &reg, uint8_t &value1, uint8_t value2, bool carry)
	{
		bool halfCarry = ((value1 & 0xFU) < (value2 & 0xFU) + carry);

		setFlags(
			reg,
			(value1 - value2 - carry) % 0x100 == 0 ? SET : UNSET,
			SET,
			halfCarry ? SET : UNSET,
			value1 < value2 + carry ? SET : UNSET
		);
		value1 -= value2 + carry;
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Additionne value1 et value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t ADD16(CPU::Registers &reg, uint16_t &value1, uint16_t value2)
	{
		bool halfCarry = (value1 & 0xFFFU) + (value2 & 0xFFFU) > 0xFFFU;

		setFlags(
			reg,
			UNCHANGED,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 + value2 > 0xFFFF ? SET : UNSET
		);
		value1 += value2;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}
	/*!
	 * Soustrait value2 à value2 et stock le résultat dans value1
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SUB16(CPU::Registers &reg, uint16_t &value1, uint16_t value2)
	{
		bool halfCarry = (value1 & 0xFU) < (value2 & 0xFU);

		setFlags(
			reg,
			UNCHANGED,
			SET,
			halfCarry ? SET : UNSET,
			value1 < value2 ? SET : UNSET
		);
		value1 -= value2;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}
	/*!
	 * Incrémente value
	 * @param reg Registres CPU
	 * @param value Valeur incrémentée
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t INC8(CPU::Registers &reg, uint8_t &value)
	{
		bool halfCarry = (((value & 0xf) + 1) & 0x10) == 0x10;

		value++;
		setFlags(
			reg,
			value == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			UNCHANGED
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Décrémente value
	 * @param reg Registres CPU
	 * @param value Valeur décrémentée
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t DEC8(CPU::Registers &reg, uint8_t &value)
	{
		bool halfCarry = (((value & 0xf) - 1) & 0x10) == 0x10;

		value--;
		setFlags(
			reg,
			value == 0 ? SET : UNSET,
			SET,
			halfCarry ? SET : UNSET,
			UNCHANGED
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Incrémente value
	 * @param value Valeur incrémentée
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t INC16(uint16_t &value)
	{
		value++;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}
	/*!
	 * Décrémente value
	 * @param value Valeur Décrémentée
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t DEC16(uint16_t &value)
	{
		value--;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}
	/*!
	 * Incrémente la valeur pointée par address
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la valeur à incrementer
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t INCPTR(CPU &cpu, CPU::Registers &reg, uint16_t address)
	{
		auto tmp = cpu.read(address);
		auto rt_value = INC8(reg, tmp) + INDIRECTION_CYCLE_DURATION * 2;

		cpu.write(address, tmp);
		return rt_value;
	}
	/*!
	 * Décrémente la valeur pointée par address
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la valeur à décrementer
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t DECPTR(CPU &cpu, CPU::Registers &reg, uint16_t address)
	{
		auto tmp = cpu.read(address);
		auto rt_value = DEC8(reg, tmp) + INDIRECTION_CYCLE_DURATION * 2;

		cpu.write(address, tmp);
		return rt_value;
	}
	/*!
	 * Écris value à address
	 * @param cpu CPU
	 * @param address Adresse à écrire
	 * @param value Value à écrire
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t LD8toPTR(CPU &cpu, uint16_t address, uint8_t value)
	{
		cpu.write(address, value);
		return LD_CYCLE_DURATION + INDIRECTION_CYCLE_DURATION;
	}
	/*!
	 * Lis la valeur à address et la place dans value
	 * @param cpu CPU
	 * @param value Valeur à remplacer
	 * @param address Adresse à lire
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t LD8fromPTR(CPU &cpu, uint8_t &value, uint16_t address)
	{
		value = cpu.read(address);
		return LD_CYCLE_DURATION + INDIRECTION_CYCLE_DURATION;
	}
	/*!
	 * Écris value à address
	 * @param cpu CPU
	 * @param address Adresse à écrire
	 * @param value Value à écrire
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t LD16toPTR(CPU &cpu, uint16_t address, uint16_t value)
	{
		cpu.write(address, value & 0x00FFU);
		cpu.write(address + 1, value >> 8U);
		return LD_CYCLE_DURATION * 2 + INDIRECTION_CYCLE_DURATION;
	}
	/*!
	 * Lis la valeur à address et la place dans value
	 * @param cpu CPU
	 * @param value Valeur à remplacer
	 * @param address Adresse à lire
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t LD16fromPTR(CPU &cpu, uint16_t &value, uint16_t address)
	{
		value = cpu.read(address);
		value += cpu.read(address + 1) << 8U;
		return LD_CYCLE_DURATION * 2 + INDIRECTION_CYCLE_DURATION;
	}
	/*!
	 * Pousse value dans la pile.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param value Valeur à pousser.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t PUSH(CPU &cpu, CPU::Registers &reg, uint16_t value)
	{
		cpu.write(--reg.sp, value >> 8U);
		cpu.write(--reg.sp, value);
		return PUSH_CYCLE_DURATION;
	}
	/*!
	 * Retire value de la pile.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param value Valeur rétirée.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t POP(CPU &cpu, CPU::Registers &reg, uint16_t &value)
	{
		uint8_t temp = cpu.read(reg.sp++);

		value = (cpu.read(reg.sp++) << 8U) | temp;

		return POP_CYCLE_DURATION;
	}
	/*!
	 * Affectue un appel à la fonction pointé par address.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param address Adresse de la fonction
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t CALL(CPU &cpu, CPU::Registers &reg, uint16_t address)
	{
		PUSH(cpu, reg, reg.pc);
		JP(reg, true, address);
		return PUSH_CYCLE_DURATION;
	}
	/*!
	 * Affectue un appel à la fonction pointé par address si cond est true.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param cond Condition de saut.
	 * @param address Adresse de la fonction
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t CALLC(CPU &cpu, CPU::Registers &reg, bool cond, uint16_t address)
	{
		if (!cond)
			return NOP_CYCLE_DURATION;
		return CALL(cpu ,reg, address);
	}
	/*!
	 * Compare a et value
	 * @param reg Registres CPU
	 * @param value Valeur à comparer.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t CP(CPU::Registers &reg, uint8_t value)
	{
		uint8_t buf = reg.a;

		return SUB8(reg, buf, value, false);
	}
	/*!
	 * Reset le bit 'bit' de val
	 * @param val Valeur à changer
	 * @param bit Bit à reset
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RES(uint8_t &val, uint8_t bit)
	{
		val &= ~(1U << bit);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Set le bit 'bit' de val.
	 * @param val Valeur à changer
	 * @param bit Bit à changer
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SETB(uint8_t &val, uint8_t bit)
	{
		val |= (1U << bit);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Retourne de l'appel d'une fonction si cond est true.
	 * @param cpu CPU
	 * @param reg Registres CPU
	 * @param cond Condition de retour.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RET(CPU &cpu, CPU::Registers &reg, bool cond)
	{
		if (cond)
			return POP(cpu, reg, reg.pc) + COMPLEX_BIT_OPERATION_CYCLE_DURATION;
		return COMPLEX_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de value à gauche. Le bit 7 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RLC(CPU::Registers &reg, uint8_t &value)
	{
		uint8_t newValue = (value << 1U) | ((value & (1U << 7U)) != 0);

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, value & (1U << 7U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de value à droite. Le bit 0 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RRC(CPU::Registers &reg, uint8_t &value)
	{
		uint8_t newValue = (value >> 1U) | ((value & 1U) << 7U);

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, (value & 1U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de value à gauche. Le flag c est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RL(CPU::Registers &reg, uint8_t &value)
	{
		uint8_t newValue = (value << 1U) | reg.fc;

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, value & (1U << 7U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de value à droite. Le flag c est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RR(CPU::Registers &reg, uint8_t &value)
	{
		uint8_t newValue = (value >> 1U) | (reg.fc << 7U);

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, (value & 1U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de val à gauche. value est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 0
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SL(CPU::Registers &reg, uint8_t &val, bool value)
	{
		uint8_t newValue = (val << 1U) | value;

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, val & (1U << 7U) ? SET : UNSET);
		val = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de val à gauche. value est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 7
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SR(CPU::Registers &reg, uint8_t &val, bool value)
	{
		uint8_t newValue = (val >> 1U) | (value * (val & 0x80U));

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, val & 0x1 ? SET : UNSET);
		val = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de a à gauche. 0 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @param value Nouvelle valeur du bit 0
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SLA(CPU::Registers &re, uint8_t &val)
	{
		return SL(re, val, false);
	}
	/*!
	 * Pivote les bits de a à droite. 1 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SRA(CPU::Registers &re, uint8_t &val)
	{
		return SR(re, val, true);
	}
	/*!
	 * Pivote les bits de a à gauche. Le bit 7 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RLCA(CPU::Registers &re)
	{
		unsigned val = RLC(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}
	/*!
	 * Pivote les bits de a à droite. Le bit 0 est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RRCA(CPU::Registers &re)
	{
		unsigned val = RRC(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}
	/*!
	 * Pivote les bits de a à gauche. Le flag c est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RLA(CPU::Registers &re)
	{
		unsigned val = RL(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}
	/*!
	 * Pivote les bits de a à droite. Le flag c est placé à la place du bit 7.
	 * @param reg Registres CPU
	 * @param value Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t RRA(CPU::Registers &re)
	{
		unsigned val = RR(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}
	/*!
	 * Échange les 4 premiers bits et les 4 derniers bits de val.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SWAP(CPU::Registers &re, uint8_t &val)
	{
		val = ((val & 0b1111U) << 4U) | (val >> 4U);
		setFlags(re, val ? UNSET : SET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Pivote les bits de a à gauche. 1 est placé à la place du bit 0.
	 * @param reg Registres CPU
	 * @param val Valeur à pivoter.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SRL(CPU::Registers &re, uint8_t &val)
	{
		return SR(re, val, false);
	}
	/*!
	 * Stop le CPU.
	 * @param cpu CPU
	 * @return Nombre de cycles écoulés
	 * @throw InvalidSTOPException
	 */
	inline uint8_t STOP(CPU &cpu)
	{
		uint8_t arg = cpu.read(cpu.getRegisters().pc);

		if (arg)
#ifdef __cpp_exceptions
			throw InvalidSTOPException("Malformed STOP instruction", cpu.getRegisters().pc - 1, arg);
#else
		return ERRORED_DURATION;
#endif
		cpu.fetchArgument();
		cpu.stop();
		return NOP_CYCLE_DURATION;
	}
	/*!
	 * Ajuste a pour les addition et soustractions en BCD.
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t DAA(CPU::Registers &reg, uint8_t &val)
	{
		unsigned oldVal = val;
		bool fc = reg.fc;

		if (!reg.fn) {
			if (reg.fh || (oldVal & 0x0FU) > 9)
				oldVal += 0x06U;
			if (reg.fc || oldVal > 0x9FU) {
				oldVal += 0x60U;
				fc = true;
			}
		} else {
			if (reg.fh)
				oldVal -= 0x06U;
			if (reg.fc)
				oldVal -= 0x60;
		}

		val = oldVal;
		setFlags(
			reg,
			val == 0 ? SET : UNSET,
			UNCHANGED,
			UNSET,
			fc ? SET : UNSET
		);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Inverse les bits de a.
	 * @param reg Registres CPU.
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t CPL(CPU::Registers &reg)
	{
		reg.a = ~reg.a;
		setFlags(reg, UNCHANGED, SET, SET, UNCHANGED);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}
	/*!
	 * Effectue une addition sur un nombre 16 bit non signé et un nombre 8 bit signé et stock le résultat dans value1.
	 * @param reg Registres CPU
	 * @param value1 Valeur 1
	 * @param value2 Valeur 2
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t SPECIAL_ADD(CPU::Registers &reg, uint16_t &value1, int8_t value2)
	{
		if (value2 >= 0) {
			setFlags(
				reg,
				UNSET,
				UNSET,
				(value1 & 0xFU) + (value2 & 0xFU) > 0xFU ? SET : UNSET,
				((value1 & 0xFFU) + value2) > 0xFF ? SET : UNSET
			);
		} else {
			setFlags(
				reg,
				UNSET,
				UNSET,
				(value1 & 0xFU) < ((-value2) & 0xFU) ? UNSET : SET,
				((value1 & 0xFF) < -value2) ? UNSET : SET
			);
		}
		value1 += value2;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 3;
	}
	/*!
	 * Execute une fonction sur la valeur pointé par address
	 * @param cpu CPU
	 * @param address Adresse sur laquelle executer fct
	 * @param fct Fonction à executer
	 * @param reg Registres CPU
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t executeOnPtr(CPU &cpu, uint16_t address, uint8_t (&fct)(CPU::Registers &, uint8_t &), CPU::Registers &reg)
	{
		uint8_t value = cpu.read(address);
		uint8_t time = fct(reg, value);

		cpu.write(address, value);
		return time + INDIRECTION_CYCLE_DURATION;
	}

	template <typename ...args>
	/*!
	 * Execute une fonction sur la valeur pointé par address
	 * @param cpu CPU
	 * @param address Adresse sur laquelle executer fct
	 * @param fct Fonction à executer
	 * @param arguments Arguments de fct
	 * @return Nombre de cycles écoulés
	 */
	inline uint8_t executeOnPtr(CPU &cpu, uint16_t address, uint8_t (&fct)(uint8_t &, args...), args... arguments)
	{
		uint8_t value = cpu.read(address);
		uint8_t time = fct(value, arguments...);

		cpu.write(address, value);
		return time + INDIRECTION_CYCLE_DURATION * 2;
	}
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
