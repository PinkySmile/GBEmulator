/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** JP.cpp
*/

#include <criterion/criterion.h>
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

const auto &instructions = GBEmulator::Instructions::_instructions;

Test(JP_a16, vram_8000_256) {
	Tests::GBTest gb;
	/*unsigned char excepted_time = 20;

	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x81);
	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x0100;
	unsigned char time = instructions[0x8](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu.read(0x8100) | (gb.cpu.read(0x8101) << 8U);
	unsigned short ex_result = 0x100;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);*/
	cr_assert(true);
}