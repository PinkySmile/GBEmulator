/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestCpuInstruction.cpp
*/

#include <criterion/criterion.h>
#include "communism.hpp"
#include "TestComponents.hpp"
#include "../src/ProcessingUnits/Instructions/CPUInstructions.hpp"


//! INSTRUCTIONS

const auto instructions = GBEmulator::Instructions::_instructions;

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

//! INSTRUCTION 01

Test(LD_BC_d16, rom_500_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x500, 0);
	gb.cpu.write(0x501, 0);
	gb.cpu._registers.pc = 0x500;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, rom_500_65535) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x500, 0xFF);
	gb.cpu.write(0x501, 0xFF);
	gb.cpu._registers.pc = 0x500;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, rom_4242_2142) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x4242, 21);
	gb.cpu.write(0x4243, 42);
	gb.cpu._registers.pc = 0x4242;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, rom_1234_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x1234, 0);
	gb.cpu.write(0x1235, 1);
	gb.cpu._registers.pc = 0x1234;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x0;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, vram_8000_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x8000, 0);
	gb.cpu.write(0x8001, 1);
	gb.cpu._registers.pc = 0x8000;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x100;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, wram_C000_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0xC000, 0x42);
	gb.cpu.write(0xC001, 0xC9);
	gb.cpu._registers.pc = 0xC000;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0xC942;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 2

Test(LD_unrefBC_A, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.a = 0xD8;
	gb.cpu._registers.bc = 0xC000;
	unsigned char time = instructions[0x2](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC000);
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_unrefBC_A, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.a = 0xFD;
	gb.cpu._registers.bc = 0xD83E;
	unsigned char time = instructions[0x2](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xD83E);
	unsigned char ex_result = 0xFD;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_unrefBC_A, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.a = 0x01;
	gb.cpu._registers.bc = 0xF0D0;
	unsigned char time = instructions[0x2](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xF0D0);
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 03

Test(INC_BC, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x0000;
	unsigned char time = instructions[0x3](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_BC, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x1234;
	unsigned char time = instructions[0x3](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x1235;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_BC, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x7FFF;
	unsigned char time = instructions[0x3](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x8000;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_BC, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0xFFFF;
	unsigned char time = instructions[0x3](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 04

Test(INC_B, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x00;
	unsigned char time = instructions[0x4](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_B, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x7F;
	unsigned char time = instructions[0x4](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_B, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x80;
	unsigned char time = instructions[0x4](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_B, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xFF;
	unsigned char time = instructions[0x4](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_B, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x2F;
	unsigned char time = instructions[0x4](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_B, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xD7;
	unsigned char time = instructions[0x4](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
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

//! INSTRUCTION 06

Test(LD_B_d8, wram_C159_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu.write(0xC159, 0x2E);
	gb.cpu._registers.pc = 0xC159;
	unsigned char time = instructions[0x6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
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