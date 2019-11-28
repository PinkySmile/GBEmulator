/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** JP.cpp
*/

#include <criterion/criterion.h>
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

#define instructions GBEmulator::Instructions::_instructions

//! INSTRUCTION C2

Test(JP_nz_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = true;

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xC2](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8002;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_nz_a16, jump_0000) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xC2](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x00;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_nz_a16, jump_random) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = false;

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xC2](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu.read(0x8000) | (gb.cpu.read(0x8001) << 8U);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION C3

Test(JP_a16, jump_0000) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xC3](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x00;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_a16, jump_random) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xC3](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu.read(0x8000) | (gb.cpu.read(0x8001) << 8U);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION CA

Test(JP_z_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = false;

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xCA](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8002;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_z_a16, jump_0000) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xCA](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x00;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_z_a16, jump_random) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = true;

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xCA](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu.read(0x8000) | (gb.cpu.read(0x8001) << 8U);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION D2

Test(JP_nc_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = true;

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xD2](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8002;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_nc_a16, jump_0000) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xD2](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x00;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_nc_a16, jump_random) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = false;

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xD2](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu.read(0x8000) | (gb.cpu.read(0x8001) << 8U);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION DA

Test(JP_c_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = false;

	unsigned char excepted_time = 12;
	unsigned char time = instructions[0xDA](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8002;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_c_a16, jump_0000) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xDA](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x00;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_c_a16, jump_random) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = true;

	unsigned char excepted_time = 16;
	unsigned char time = instructions[0xDA](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu.read(0x8000) | (gb.cpu.read(0x8001) << 8U);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION E9

Test(JP_hl, jump_0000) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.hl = 0x0000;

	unsigned char excepted_time = 4;
	unsigned char time = instructions[0xE9](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu._registers.hl;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JP_hl, jump_random) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.hl = gb.cpu.read(0x8000) | (gb.cpu.read(0x8001) << 8U);

	unsigned char excepted_time = 4;
	unsigned char time = instructions[0xE9](gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = gb.cpu._registers.hl;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}