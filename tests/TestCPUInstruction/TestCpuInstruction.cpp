/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestCpuInstruction.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

const auto instructions = GBEmulator::Instructions::_instructions;

//! INSTRUCTIONS

Test(Basic, build_test_gb) {
	Tests::GBTest gb;
	cr_assert(true);
}

//! INSTRUCTION 00

Test(NOP, return_value) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	unsigned char time = instructions[0x0](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
}

//! INSTRUCTION 07
//TODO: Faire ces merdes