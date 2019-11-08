/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** DEC.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

const auto instructions = GBEmulator::Instructions::_instructions;

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

Test(DEC_B, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x2F;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xD7;
	unsigned char time = instructions[0x5](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD6;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_B, value_7) {
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

//! INSTRUCTION 0B

Test(DEC_BC, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x0000;
	unsigned char time = instructions[0xB](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0xFFFF;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(DEC_BC, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x1234;
	unsigned char time = instructions[0xB](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x1233;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(DEC_BC, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x7FFF;
	unsigned char time = instructions[0xB](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x7FFE;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(DEC_BC, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0xFFFF;
	unsigned char time = instructions[0xB](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0xFFFE;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(DEC_BC, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.bc = 0x8000;
	unsigned char time = instructions[0xB](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x7FFF;
	cr_assert_eq(result, ex_result, "Register bc must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 0D

Test(DEC_C, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x00;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_C, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x7F;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x7E;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_C, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x80;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_C, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xFF;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_C, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x2F;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_C, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xD7;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xD6;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_C, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x01;
	unsigned char time = instructions[0xD](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 0D

Test(DEC_D, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x00;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_D, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x7F;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x7E;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_D, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x80;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_D, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xFF;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_D, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x2F;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_D, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x157;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x156;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_D, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x01;
	unsigned char time = instructions[0x15](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 0D

Test(DEC_E, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x00;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_E, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x7F;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x7E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_E, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x80;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_E, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xFF;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_E, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x2F;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_E, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x157;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x156;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(DEC_E, value_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x01;
	unsigned char time = instructions[0x1D](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 1, "fn must be 1 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}