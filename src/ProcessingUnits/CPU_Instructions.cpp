/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.c
*/

#include "CPU_Instructions.hpp"
#include "CPU.hpp"

namespace GBEmulator::Instructions {

	void LD8(unsigned char &register1, unsigned char value) {
		register1 = value;
	}

	void LD16(unsigned short &double_register, unsigned short value)
	{
		double_register = value;
	}

	void LDPTR(CPU &cpu, unsigned short address, unsigned short value)
	{
		cpu.write(address, value);
	}
}