/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Instructions.h
*/

#ifndef GBEMULATOR_INSTRUCTIONS_HPP
#define GBEMULATOR_INSTRUCTIONS_HPP

#include "CPUInstructions.hpp"

namespace GBEmulator::Instructions {
	unsigned executeInstruction(unsigned char opcode, GBEmulator::CPU &cpu, GBEmulator::CPU::Registers &reg);
	unsigned executeBitInstruction(unsigned char opcode, GBEmulator::CPU &cpu, GBEmulator::CPU::Registers &reg);
}

#endif //GBEMULATOR_INSTRUCTIONS_HPP
