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
#define PUSH_CYCLE_DURATION 12
#define INDIRECTION_CYLCE_DURATION 4
#define FETCH_ARGUMENT8_CYLCE_DURATION 4
#define FETCH_ARGUMENT16_CYLCE_DURATION 8
#define BASIC_BIT_OPERATION_CYCLE_DURATION 4
#define ARITHMETIC_OPERATION_CYCLE_DURATION 4
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
	unsigned char JP(CPU::Registers &reg, bool cond, unsigned short address);
	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit);
	unsigned char XOR(CPU::Registers &reg, unsigned char value);
	unsigned char LD8(unsigned char &value1, unsigned char value2);
	unsigned char LD16(unsigned short &value1, unsigned short value2);
	unsigned char AND8(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	unsigned char OR8(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	unsigned char ADD8(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	unsigned char SUB8(CPU::Registers &reg, unsigned char &value1, unsigned char value2);
	unsigned char ADD16(CPU::Registers &reg, unsigned short &value1, unsigned short value2);
	unsigned char SUB16(CPU::Registers &reg, unsigned short &value1, unsigned short value2);
	unsigned char INC8(CPU::Registers &reg, unsigned char &value);
	unsigned char DEC8(CPU::Registers &reg, unsigned char &value);
	unsigned char INC16(unsigned short &value);
	unsigned char DEC16(unsigned short &value);
	unsigned char INCPTR(CPU &cpu, CPU::Registers &reg, unsigned short &address);
	unsigned char DECPTR(CPU &cpu, CPU::Registers &reg, unsigned short &address);
	unsigned char LD8toPTR(CPU &cpu, unsigned short address, unsigned char value);
	unsigned char LD8fromPTR(CPU &cpu, unsigned char &value, unsigned short address);
	unsigned char LD16toPTR(CPU &cpu, unsigned short address, unsigned short value);
	unsigned char LD16fromPTR(CPU &cpu, unsigned short &value, unsigned short address);
	unsigned char CALL(CPU &cpu, CPU::Registers &reg, unsigned short address);
	unsigned char CALLC(CPU &cpu, CPU::Registers &reg, bool cond, unsigned short address);
	unsigned char PUSH(CPU &cpu, CPU::Registers &reg, unsigned short value);
	unsigned char POP(CPU &cpu, CPU::Registers &reg, unsigned short &value);
	unsigned char RL(CPU::Registers &reg, unsigned char &value);
	unsigned char CP(CPU::Registers &reg, unsigned char value);

	extern const std::function<unsigned char (CPU &, CPU::Registers &)> _instructions[256];
	extern const std::function<unsigned char (CPU &, CPU::Registers &)> _bitLevelInstructions[256];
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
