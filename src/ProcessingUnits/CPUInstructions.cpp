/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.c
*/

#include "CPUInstructions.hpp"
#include "CPU.hpp"

namespace GBEmulator::Instructions
{
	const std::map<unsigned char, std::function<unsigned char (CPU &, CPU::Registers &)>> _bitLevelInstructions{
		//! 7C; BIT 7,h
		{0x7C, [](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 7); }},
	};

	const std::map<unsigned char, std::function<unsigned char (CPU &, CPU::Registers &)>> _instructions{
		//! 00; NOP: do nothing
		{0x00, [](CPU &, CPU::Registers &) { return NOP_CYCLE_DURATION; }},

		//! 01; LD bc, d16: read 16 bytes on pc and put in bc register
		{0x01, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.bc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; }},

		//! 02; LD (bc), a: Stores a into the memory location pointed to by bc
		{0x02, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.bc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; }},

		//! 20; JR nz, *: If the Z flag is not set, add the signed value * to pc
		{0x20, [](CPU &cpu, CPU::Registers &reg) { return JR(reg, !reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; }},

		//! 21; LD hl, **: Loads ** into hl register
		{0x21, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.hl, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; }},

		//! 31; LD sp, **: Loads ** into sp register
		{0x31, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.sp, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; }},

		//! 32; LD (hl-), a: Loads a into address pointed to by hl and decrement hl
		{0x32, [](CPU &cpu, CPU::Registers &reg) { return LDPTR(cpu, reg.hl--, reg.a); }},

		//! AF; XOR a: Xor a with a
		{0xAF, [](CPU &cpu, CPU::Registers &reg) { return XOR(reg, reg.a, reg.a); }},

		//! CB; Prefix for bit level instructions
		{0xCB, [](CPU &cpu, CPU::Registers &reg) {
			unsigned char opcode = cpu.read(reg.pc++);

			try {
				return Instructions::_bitLevelInstructions.at(opcode)(cpu, reg);
			} catch (std::out_of_range &) {
				throw CPU::InvalidOpcodeException(0xCB00U | opcode, reg.pc - 2);
			}
		}},
	};

	void setFlags(CPU::Registers &reg, FlagValue z, FlagValue n, FlagValue h, FlagValue c)
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

	unsigned char JR(CPU::Registers &reg, bool cond, char off)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc += off;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit)
	{
		setFlags(reg, ((1U << bit) & value) == 0 ? SET : UNSET, UNSET, SET, UNCHANGED);
		return COMPLEX_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char XOR(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		value1 ^= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char LD8(unsigned char &register1, unsigned char value)
	{
		register1 = value;
		return LD_CYCLE_DURATION;
	}

	unsigned char LD16(unsigned short &double_register, unsigned short value)
	{
		double_register = value;
		return LD_CYCLE_DURATION;
	}

	unsigned char LDPTR(CPU &cpu, unsigned short address, unsigned char value)
	{
		cpu.write(address, value);
		return LD_CYCLE_DURATION + INDIRECTION_CYLCE_DURATION;
	}
}