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

//! INSTRUCTION 05

Test(DEC_B, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x00;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x7F;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x7E;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x80;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xFF;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x30;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x2F;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x01;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xD7;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD6;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 07
//TODO: Faire ces merdes

//! INSTRUCTION 08

Test(LD_a16_SP, vram_8000_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 20;

	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x81);
	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x0100;
	unsigned char time = instructions[0x8](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu.read(0x8100) | (gb.cpu.read(0x8101) << 8U);
	unsigned short ex_result = 0x100;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_a16_SP, wram_C159) {
	Tests::GBTest gb;
	unsigned char excepted_time = 20;

	gb.cpu.write(0xC159, 0x43);
	gb.cpu.write(0xC15A, 0xEA);
	gb.cpu._registers.pc = 0xC159;
	gb.cpu._registers.sp = 0xA7F4;
	unsigned char time = instructions[0x8](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu.read(0xEA43) + (gb.cpu.read(0xEA44) << 8U);
	unsigned short ex_result = 0xA7F4;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 09

Test(ADD_HL_BC, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x0000;
	gb.cpu._registers.bc = 0x0000;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu._registers.bc = 0xA7F4;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x694D;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	gb.cpu._registers.bc = 0x2000;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x9FFF;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x8000;
	gb.cpu._registers.bc = 0x8000;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x004E;
	gb.cpu._registers.bc = 0x00F5;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0143;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	gb.cpu._registers.bc = 0x2001;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0xA000;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	gb.cpu._registers.bc = 0x0002;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_BC, value_8) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	gb.cpu._registers.bc = 0x0101;
	unsigned char time = instructions[0x9](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0100;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}