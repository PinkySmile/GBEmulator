/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.c
*/

#include <sstream>
#include <iomanip>
#include "CPUInstructions.hpp"
#include "../CPU.hpp"

namespace GBEmulator::Instructions
{
	std::string intToHex(unsigned i, unsigned size)
	{
		std::stringstream stream;
		stream << std::setfill ('0') << std::setw(size) << std::hex << std::uppercase << static_cast<int>(i);
		return stream.str();
	}

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

	unsigned char CALL(CPU &cpu, CPU::Registers &reg, unsigned short address)
	{
		PUSH(cpu, reg, reg.pc);
		JP(reg, true, address);
		return PUSH_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char CALLC(CPU &cpu, CPU::Registers &reg, bool cond, unsigned short address)
	{
		if (!cond)
			return NOP_CYCLE_DURATION;
		return CALL(cpu ,reg, address);
	}

	unsigned char PUSH(CPU &cpu, CPU::Registers &reg, unsigned short value)
	{
		cpu.write(--reg.sp, value >> 8U);
		cpu.write(--reg.sp, value);
		return PUSH_CYCLE_DURATION;
	}

	unsigned char POP(CPU &cpu, CPU::Registers &reg, unsigned short &value)
	{
		unsigned char temp = cpu.read(reg.sp++);

		value = (cpu.read(reg.sp++) << 8U) | temp;
		return PUSH_CYCLE_DURATION;
	}

	unsigned char RET(CPU &cpu, CPU::Registers &reg, bool cond)
	{
		if (cond)
			return POP(cpu, reg, reg.pc) + COMPLEX_BIT_OPERATION_CYCLE_DURATION;
		return COMPLEX_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char JR(CPU::Registers &reg, bool cond, char off)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc += off;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char JP(CPU::Registers &reg, bool cond, unsigned short address)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc = address;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit)
	{
		setFlags(reg, ((1U << bit) & value) == 0 ? SET : UNSET, UNSET, SET, UNCHANGED);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char XOR(CPU::Registers &reg, unsigned char value)
	{
		reg.a ^= value;
		setFlags(reg, reg.a == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
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

	unsigned char LD8toPTR(CPU &cpu, unsigned short address, unsigned char value)
	{
		cpu.write(address, value);
		return LD_CYCLE_DURATION + INDIRECTION_CYCLE_DURATION;
	}

	unsigned char LD8fromPTR(CPU &cpu, unsigned char &value, unsigned short address)
	{
		value = cpu.read(address);
		return LD_CYCLE_DURATION + INDIRECTION_CYCLE_DURATION;
	}

	unsigned char LD16toPTR(CPU &cpu, unsigned short address, unsigned short value)
	{
		cpu.write(address, value & 0x00FFU);
		cpu.write(address + 1, value >> 8U);
		return LD_CYCLE_DURATION * 2 + INDIRECTION_CYCLE_DURATION;
	}

	unsigned char LD16fromPTR(CPU &cpu, unsigned short &value, unsigned short address)
	{
		value = cpu.read(address);
		value += cpu.read(address + 1) << 8U;
		return LD_CYCLE_DURATION * 2 + INDIRECTION_CYCLE_DURATION;
	}

	unsigned char AND8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		value1 &= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, SET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char OR8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		value1 |= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char ADD8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		bool halfCarry = (((value1 & 0xFU) + (value2 & 0xFU)) & 0x10U) == 0x10U;

		setFlags(
			reg,
			(value1 + value2) == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 + value2 > 0xFF ? SET : UNSET
		);
		value1 += value2;
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}

	unsigned char SUB8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		bool halfCarry = (((value1 & 0xFU) - (value2 & 0xFU)) & 0x10U) == 0x10U;

		setFlags(
			reg,
			value1 == value2 ? SET : UNSET,
			SET,
			halfCarry ? SET : UNSET,
			value1 < value2 ? SET : UNSET
		);
		value1 -= value2;
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}

	unsigned char ADD16(CPU::Registers &reg, unsigned short &value1, unsigned short value2)
	{
		bool halfCarry = (((value1 & 0xFFU) + (value2 & 0xFFU)) & 0x100U) == 0x100U;

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

	unsigned char SUB16(CPU::Registers &reg, unsigned short &value1, unsigned short value2)
	{
		bool halfCarry = (((value1 & 0xFFU) - (value2 & 0xFFU)) & 0x100U) == 0x100U;

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

	unsigned char INC8(CPU::Registers &reg, unsigned char &value)
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

	unsigned char DEC8(CPU::Registers &reg, unsigned char &value)
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

	unsigned char INC16(unsigned short &value)
	{
		value++;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}

	unsigned char DEC16(unsigned short &value)
	{
		value--;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}

	unsigned char INCPTR(CPU &cpu, CPU::Registers &reg, unsigned short address)
	{
		auto tmp = cpu.read(address);
		auto rt_value = INC8(reg, tmp) + INDIRECTION_CYCLE_DURATION * 2;

		cpu.write(address, tmp);
		return rt_value;
	}

	unsigned char DECPTR(CPU &cpu, CPU::Registers &reg, unsigned short address)
	{
		auto tmp = cpu.read(address);
		auto rt_value = DEC8(reg, tmp) + INDIRECTION_CYCLE_DURATION * 2;

		cpu.write(address, tmp);
		return rt_value;
	}

	unsigned char CP(CPU::Registers &reg, unsigned char value)
	{
		unsigned char buf = reg.a;

		return SUB8(reg, buf, value);
	}

	unsigned char RES(unsigned char &val, unsigned char bit)
	{
		val &= ~(1U << bit);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char SETB(unsigned char &val, unsigned char bit)
	{
		val |= (1U << bit);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char RLCA(CPU::Registers &re)
	{
		unsigned val = RLC(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}

	unsigned char RRCA(CPU::Registers &re)
	{
		unsigned val = RRC(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}

	unsigned char RLA(CPU::Registers &re)
	{
		unsigned val = RL(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}

	unsigned char RRA(CPU::Registers &re)
	{
		unsigned val = RR(re, re.a);

		setFlags(re, UNSET, UNCHANGED, UNCHANGED, UNCHANGED);
		return val;
	}

	unsigned char RLC(CPU::Registers &reg, unsigned char &value)
	{
		unsigned char newValue = (value << 1U) | ((value & (1U << 7U)) != 0);

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, value & (1U << 7U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char RRC(CPU::Registers &reg, unsigned char &value)
	{
		unsigned char newValue = (value >> 1U) | ((value & 1U) << 7U);

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, (value & 1U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char RL(CPU::Registers &reg, unsigned char &value)
	{
		unsigned char newValue = (value << 1U) | reg.fc;

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, value & (1U << 7U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char RR(CPU::Registers &reg, unsigned char &value)
	{
		unsigned char newValue = (value >> 1U) | (reg.fc << 7U);

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, (value & 1U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char STOP(CPU &cpu)
	{
		unsigned char arg = cpu.read(cpu.getRegisters().pc);

		if (arg)
			throw InvalidSTOPException("Malformed STOP instruction", cpu.getRegisters().pc - 1, arg);
		cpu.fetchArgument();
		cpu.stop();
		return NOP_CYCLE_DURATION;
	}

	unsigned char DAA(CPU::Registers &reg, unsigned char &val)
	{
		unsigned char oldVal = val;
		bool cf = false;

		if (((reg.fh & 0x0FU) > 9) || reg.fh) {
			val += 6;
			reg.fc = reg.fc || val >= 0xA0;
		}

		if ((oldVal > 0x99) || reg.fc) {
			val += 0x60;
			cf = true;
		}
		setFlags(reg, val == 0 ? SET : UNSET, UNCHANGED, UNSET, cf ? SET : UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char CPL(CPU::Registers &reg)
	{
		reg.a = ~reg.a;
		setFlags(reg, UNCHANGED, SET, SET, UNCHANGED);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char SL(CPU::Registers &reg, unsigned char &val, bool value)
	{
		unsigned char newValue = (val << 1U) | value;

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, val & (1U << 7U) ? SET : UNSET);
		val = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char SR(CPU::Registers &reg, unsigned char &val, bool value)
	{
		unsigned char newValue = (val >> 1U) | (value * (val & 0x80U));

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, val & 0x1 ? SET : UNSET);
		val = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char SLA(CPU::Registers &re, unsigned char &val)
	{
		return SL(re, val, false);
	}

	unsigned char SRA(CPU::Registers &re, unsigned char &val)
	{
		return SR(re, val, true);
	}

	unsigned char SLL(CPU::Registers &re, unsigned char &val)
	{
		return SL(re, val, true);
	}

	unsigned char SRL(CPU::Registers &re, unsigned char &val)
	{
		return SR(re, val, false);
	}

	unsigned char executeOnPtr(CPU &cpu, unsigned short address, unsigned char (&fct)(CPU::Registers &, unsigned char &), CPU::Registers &reg)
	{
		unsigned char value = cpu.read(address);
		unsigned char time = fct(reg, value);

		cpu.write(address, value);
		return time + INDIRECTION_CYCLE_DURATION;
	}
}