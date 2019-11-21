/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** PUSH.cpp
*/

#include <criterion/criterion.h>
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

#define instructions GBEmulator::Instructions::_instructions

//! INSTRUCTION C5

Test(PUSH_bc, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xC5](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), gb.cpu._registers.b, "Value at address 0x8FFF must be 0x%X but was 0x%X", gb.cpu._registers.b, gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), gb.cpu._registers.c, "Value at address 0x8FFE must be 0x%X but was 0x%X", gb.cpu._registers.c, gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION D5

Test(PUSH_de, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.de = 0x8FF8;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xD5](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), gb.cpu._registers.d, "Value at address 0x8FFF must be 0x%X but was 0x%X", gb.cpu._registers.d, gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), gb.cpu._registers.e, "Value at address 0x8FFE must be 0x%X but was 0x%X", gb.cpu._registers.e, gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION E5

Test(PUSH_hl, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.hl = 0x8FF8;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xE5](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), gb.cpu._registers.h, "Value at address 0x8FFF must be 0x%X but was 0x%X", gb.cpu._registers.h, gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), gb.cpu._registers.l, "Value at address 0x8FFE must be 0x%X but was 0x%X", gb.cpu._registers.l, gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION F5

Test(PUSH_af, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.af = 0x8FF8;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xF5](gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), gb.cpu._registers.a, "Value at address 0x8FFF must be 0x%X but was 0x%X", gb.cpu._registers.a, gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), gb.cpu._registers.f, "Value at address 0x8FFE must be 0x%X but was 0x%X", gb.cpu._registers.f, gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}
