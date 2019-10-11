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
#include "CPU.hpp"

#define LD_CYCLE_DURATION 4
#define NOP_CYCLE_DURATION 4
#define JUMP_CYCLE_DURATION 4
#define INDIRECTION_CYLCE_DURATION 4
#define FETCH_ARGUMENT8_CYLCE_DURATION 4
#define FETCH_ARGUMENT16_CYLCE_DURATION 8
#define BASIC_BIT_OPERATION_CYCLE_DURATION 4
#define COMPLEX_BIT_OPERATION_CYCLE_DURATION 8

namespace GBEmulator::Instructions
{
	enum FlagValue {
		UNSET,
		SET,
		UNCHANGED
	};

	void setFlags(CPU::Registers &reg, FlagValue z, FlagValue n, FlagValue h, FlagValue c);
	unsigned char JR(CPU::Registers &reg, bool cond, char off);
	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit);
	unsigned char XOR(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	unsigned char LD8(unsigned char &value1, unsigned char value2);
	unsigned char LD16(unsigned short &value1, unsigned short value2);
	unsigned char LDtoPTR(CPU &cpu, unsigned short address,
			      unsigned char value);

	extern const std::map<unsigned char, std::function<unsigned char (CPU &, CPU::Registers &)>> _instructions;
	extern const std::map<unsigned char, std::function<unsigned char (CPU &, CPU::Registers &)>> _bitLevelInstructions;
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
