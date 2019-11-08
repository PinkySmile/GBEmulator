/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ADD16.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

const auto instructions = GBEmulator::Instructions::_instructions;

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

//! INSTRUCTION 19

Test(ADD_HL_DE, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x0000;
	gb.cpu._registers.de = 0x0000;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu._registers.de = 0xA7F4;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x694D;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	gb.cpu._registers.de = 0x2000;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x9FFF;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 0 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x8000;
	gb.cpu._registers.de = 0x8000;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x004E;
	gb.cpu._registers.de = 0x00F5;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0143;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	gb.cpu._registers.de = 0x2001;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0xA000;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	gb.cpu._registers.de = 0x0002;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_DE, value_8) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	gb.cpu._registers.de = 0x0101;
	unsigned char time = instructions[0x19](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0100;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

//! INSTRUCTION 29

Test(ADD_HL_HL, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x0000;
	unsigned char time = instructions[0x29](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_HL, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xC159;
	unsigned char time = instructions[0x29](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x82B2;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_HL, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	unsigned char time = instructions[0x29](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0xFFFE;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 0 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_HL, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x8000;
	unsigned char time = instructions[0x29](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_HL, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x00F5;
	unsigned char time = instructions[0x29](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x01EA;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

//! INSTRUCTION 19

Test(ADD_HL_SP, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x0000;
	gb.cpu._registers.sp = 0x0000;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu._registers.sp = 0xA7F4;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x694D;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	gb.cpu._registers.sp = 0x2000;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x9FFF;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x8000;
	gb.cpu._registers.sp = 0x8000;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x004E;
	gb.cpu._registers.sp = 0x00F5;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0143;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	gb.cpu._registers.sp = 0x2001;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0xA000;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	gb.cpu._registers.sp = 0x0002;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}

Test(ADD_HL_SP, value_8) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	gb.cpu._registers.sp = 0x0101;
	unsigned char time = instructions[0x39](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0100;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
	cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 but it was %d", gb.cpu._registers.fc);
}