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
	enum FlagValue {
		UNSET,
		SET,
		UNCHANGED
	};

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

	std::string intToHex(unsigned i, unsigned size = 2);
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
	unsigned char INCPTR(CPU &cpu, CPU::Registers &reg, unsigned short address);
	unsigned char DECPTR(CPU &cpu, CPU::Registers &reg, unsigned short address);
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
	unsigned char RES(unsigned char &val, unsigned char bit);
	unsigned char SETB(unsigned char &val, unsigned char bit);
	unsigned char RET(CPU &cpu, CPU::Registers &reg, bool cond);
	unsigned char RLCA(CPU::Registers &re);
	unsigned char RRCA(CPU::Registers &re);
	unsigned char RLA(CPU::Registers &re);
	unsigned char RRA(CPU::Registers &re);
	unsigned char RLC(CPU::Registers &re, unsigned char &val);
	unsigned char RRC(CPU::Registers &re, unsigned char &val);
	unsigned char RL(CPU::Registers &re, unsigned char &val);
	unsigned char RR(CPU::Registers &re, unsigned char &val);
	unsigned char SL(CPU::Registers &re, unsigned char &val, bool value);
	unsigned char SR(CPU::Registers &re, unsigned char &val, bool value);
	unsigned char SLA(CPU::Registers &re, unsigned char &val);
	unsigned char SRA(CPU::Registers &re, unsigned char &val);
	unsigned char SWAP(CPU::Registers &re, unsigned char &val);
	unsigned char SRL(CPU::Registers &re, unsigned char &val);
	unsigned char STOP(CPU &cpu);
	unsigned char DAA(CPU::Registers &reg, unsigned char &val);
	unsigned char CPL(CPU::Registers &reg);
	unsigned char executeOnPtr(CPU &cpu, unsigned short address, unsigned char (&fct)(CPU::Registers &, unsigned char &), CPU::Registers &reg);

	template <typename ...args>
	unsigned char executeOnPtr(CPU &cpu, unsigned short address, unsigned char (&fct)(unsigned char &, args...), args... arguments)
	{
		unsigned char value = cpu.read(address);
		unsigned char time = fct(value, arguments...);

		cpu.write(address, value);
		return time + INDIRECTION_CYCLE_DURATION * 2;
	}

	extern const std::function<unsigned char (CPU &, CPU::Registers &)> _instructions[256];
	extern const std::function<unsigned char (CPU &, CPU::Registers &)> _bitLevelInstructions[256];
	extern const std::function<std::string (const CPU &, unsigned short address)> _instructionsString[256];
	extern const std::function<std::string (const CPU &, unsigned short address)> _bitLevelInstructionsString[256];
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
