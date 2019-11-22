/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** POP.cpp
*/

#include <criterion/criterion.h>
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

#define instructions GBEmulator::Instructions::_instructions

//! INSTRUCTION C1

Test(POP_bc, basic_pop) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.bc = 0x0000;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xC1](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.bc, 0x8FF8, "Register bc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.bc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION D1

Test(POP_de, basic_pop) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.de = 0x0000;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xD1](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.de, 0x8FF8, "Register de must be 0x8FF8 but it was 0x%X", gb.cpu._registers.de);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION E1

Test(PUSH_hl, basic_pop) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.hl = 0x0000;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xE1](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.hl, 0x8FF8, "Register hl must be 0x8FF8 but it was 0x%X", gb.cpu._registers.hl);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION F1

Test(PUSH_af, basic_pop) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.af = 0x0000;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xF1](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.af, 0x8FF8, "Register af must be 0x8FF8 but it was 0x%X", gb.cpu._registers.af);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}
