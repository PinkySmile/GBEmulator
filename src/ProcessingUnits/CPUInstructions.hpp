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

namespace GBEmulator::Instructions
{
	void LD8(unsigned char &register1, unsigned char register2);
	void LD16(unsigned short &register1, unsigned short register2);
	void LDPTR(CPU &cpu, unsigned short address, unsigned char value);

	extern const std::map<unsigned char, std::function<void(CPU &, CPU::Registers &)>> _instructions;
	extern const std::map<unsigned char, std::function<void(CPU &, CPU::Registers &)>> _bitLevelInstructions;
}


#endif //GBEMULATOR_CPUINSTRUCTIONS_HPP
