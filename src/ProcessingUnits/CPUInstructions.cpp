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
	const std::map<unsigned char, std::function<void(CPU &, CPU::Registers &)>> _bitLevelInstructions{

	};

	const std::map<unsigned char, std::function<void(CPU &, CPU::Registers &)>> _instructions{
		//! 00; NOP: do nothing
		{0x00, [](CPU &, CPU::Registers &) {}},

		//! 01; LD bc, d16: read 16 bytes on pc and put in bc register
		{0x01, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD16(reg.bc, cpu.fetchArgument16()); }},

		//! 02; LD (bc), a: Stores a into the memory location pointed to by bc
		{0x02, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD16(reg.bc, cpu.fetchArgument16()); }},

		//! 21; LD hl, **: Loads ** into hl register
		{0x21, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD16(reg.hl, cpu.fetchArgument16()); }},

		//! 31; LD sp, **: Loads ** into sp register
		{0x31, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD16(reg.sp, cpu.fetchArgument16()); }},

		//! 32; LD [hl-], a: Loads a into address pointed to by hl and decrement hl
		{0x32, [](CPU &cpu, CPU::Registers &reg) { Instructions::LDPTR(cpu, reg.hl--, reg.a); }},

		//! AF; XOR a: Xor a with a
		{0xAF, [](CPU &cpu, CPU::Registers &reg) { reg.a ^= reg.a; }},

		//! CB; Prefix for bit level instructions
		{0xCB, [](CPU &cpu, CPU::Registers &reg) {
			unsigned char opcode = cpu.read(reg.pc++);

			try {
				Instructions::_bitLevelInstructions.at(opcode)(cpu, reg);
			} catch (std::out_of_range &) {
				throw CPU::InvalidOpcodeException(0xCB00U | opcode, reg.pc - 2);
			}
		}},
	};

	void LD8(unsigned char &register1, unsigned char value) {
		register1 = value;
	}

	void LD16(unsigned short &double_register, unsigned short value)
	{
		double_register = value;
	}

	void LDPTR(CPU &cpu, unsigned short address, unsigned char value)
	{
		cpu.write(address, value);
	}
}