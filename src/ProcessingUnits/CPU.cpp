/*
** EPITECH PROJECT, 2022
** GBEmulator
** File description:
** Created by agrellier,
*/

#include <cstring>
#include "CPU.hpp"

namespace GBEmulator
{
	CPU::CPU(const std::string &romPath) :
		_rom(romPath, ROM_BANK_SIZE),
		_registers{0, 0, 0, 0, 0, 0}
	{
	}

	bool CPU::executeNextInstruction()
	{
		if (this->_halted)
			return false;
		//TODO: CPU
		return true;
	}
}