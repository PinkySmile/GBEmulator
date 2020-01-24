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
	/*!
	 * Execute une instruction.
	 * @param opcode Opcode à executer.
	 * @param cpu CPU executant l'instruction.
	 * @param reg Registres du CPU qui execute l'instruction.
	 * @return Le nombre de cycles écoulés.
	 */
	unsigned executeInstruction(unsigned char opcode, GBEmulator::CPU &cpu, GBEmulator::CPU::Registers &reg);
	/*!
	 * Execute une instruction bit.
	 * @param opcode Opcode à executer.
	 * @param cpu CPU executant l'instruction.
	 * @param reg Registres du CPU qui execute l'instruction.
	 * @return Le nombre de cycles écoulés.
	 */
	unsigned executeBitInstruction(unsigned char opcode, GBEmulator::CPU &cpu, GBEmulator::CPU::Registers &reg);
}

#endif //GBEMULATOR_INSTRUCTIONS_HPP
