/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** JR.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/Instructions.hpp"

//! INSTRUCTION 18

Test(JR_r8, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x18, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8041;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_r8, backward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu.write(0x8000, 0xFE);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x18, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x7FFF;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 20

Test(JR_nz_r8, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x20, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8001;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_nz_r8, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x20, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8041;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_nz_r8, backward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8000, 0xFE);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x20, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x7FFF;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 28

Test(JR_z_r8, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x28, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8001;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_z_r8, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x28, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8041;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_z_r8, backward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8000, 0xFE);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x28, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x7FFF;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 30

Test(JR_nc_r8, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x30, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8001;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_nc_r8, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x30, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8041;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_nc_r8, backward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8000, 0xFE);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x30, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x7FFF;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 38

Test(JR_c_r8, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x38, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8001;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_c_r8, forward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8000, 0x40);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x38, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x8041;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(JR_c_r8, backward_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8000, 0xFE);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x38, gb.cpu, gb.cpu._registers);
	unsigned short result = gb.cpu._registers.pc;
	unsigned short ex_result = 0x7FFF;

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(result, ex_result, "Register pc must be 0x%X but it was 0x%X", ex_result, result);
}
