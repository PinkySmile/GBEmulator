/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** INC.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

const auto &instructions = GBEmulator::Instructions::_instructions;

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
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
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
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 0C

Test(INC_C, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x00;
	unsigned char time = instructions[0xC](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_C, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x7F;
	unsigned char time = instructions[0xC](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_C, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x80;
	unsigned char time = instructions[0xC](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_C, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xFF;
	unsigned char time = instructions[0xC](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_C, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x2F;
	unsigned char time = instructions[0xC](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_C, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xD7;
	unsigned char time = instructions[0xC](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 13

Test(INC_DE, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.de = 0x0000;
	unsigned char time = instructions[0x13](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.de;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_DE, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.de = 0x1234;
	unsigned char time = instructions[0x13](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.de;
	unsigned short ex_result = 0x1235;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_DE, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.de = 0x7FFF;
	unsigned char time = instructions[0x13](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.de;
	unsigned short ex_result = 0x8000;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_DE, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.de = 0xFFFF;
	unsigned char time = instructions[0x13](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.de;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register de must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 14

Test(INC_D, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x00;
	unsigned char time = instructions[0x14](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_D, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x7F;
	unsigned char time = instructions[0x14](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_D, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x80;
	unsigned char time = instructions[0x14](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_D, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xFF;
	unsigned char time = instructions[0x14](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_D, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x2F;
	unsigned char time = instructions[0x14](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_D, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xD7;
	unsigned char time = instructions[0x14](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 1C

Test(INC_E, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x00;
	unsigned char time = instructions[0x1C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_E, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x7F;
	unsigned char time = instructions[0x1C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_E, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x80;
	unsigned char time = instructions[0x1C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_E, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xFF;
	unsigned char time = instructions[0x1C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_E, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x2F;
	unsigned char time = instructions[0x1C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_E, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xD7;
	unsigned char time = instructions[0x1C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 23

Test(INC_HL, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x0000;
	unsigned char time = instructions[0x23](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_HL, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x1234;
	unsigned char time = instructions[0x23](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x1235;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_HL, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0x7FFF;
	unsigned char time = instructions[0x23](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x8000;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_HL, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.hl = 0xFFFF;
	unsigned char time = instructions[0x23](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.hl;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register hl must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 24

Test(INC_H, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x00;
	unsigned char time = instructions[0x24](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_H, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x7F;
	unsigned char time = instructions[0x24](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_H, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x80;
	unsigned char time = instructions[0x24](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_H, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xFF;
	unsigned char time = instructions[0x24](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_H, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x2F;
	unsigned char time = instructions[0x24](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_H, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xD7;
	unsigned char time = instructions[0x24](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 24

Test(INC_L, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x00;
	unsigned char time = instructions[0x2C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_L, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x7F;
	unsigned char time = instructions[0x2C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_L, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x80;
	unsigned char time = instructions[0x2C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_L, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xFF;
	unsigned char time = instructions[0x2C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_L, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x2F;
	unsigned char time = instructions[0x2C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_L, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xD7;
	unsigned char time = instructions[0x2C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 33

Test(INC_SP, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.sp = 0x0000;
	unsigned char time = instructions[0x33](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.sp;
	unsigned short ex_result = 0x0001;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_SP, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.sp = 0x1234;
	unsigned char time = instructions[0x33](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.sp;
	unsigned short ex_result = 0x1235;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_SP, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;

	gb.cpu._registers.sp = 0x7FFF;
	unsigned char time = instructions[0x33](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.sp;
	unsigned short ex_result = 0x8000;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
}

Test(INC_SP, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8;
	
	gb.cpu._registers.sp = 0xFFFF;
	unsigned char time = instructions[0x33](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.sp;
	unsigned short ex_result = 0x0000;
	cr_assert_eq(result, ex_result, "Register sp must be 0x%X but it was 0x%X", ex_result, result);
}

//! INSTRUCTION 34

Test(INC_unrefHL, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x00);
	unsigned char time = instructions[0x34](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_unrefHL, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x7F);
	unsigned char time = instructions[0x34](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_unrefHL, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x80);
	unsigned char time = instructions[0x34](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_unrefHL, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xFF);
	unsigned char time = instructions[0x34](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_unrefHL, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x2F);
	unsigned char time = instructions[0x34](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_unrefHL, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xD7);
	unsigned char time = instructions[0x34](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(gb.cpu._registers.hl);
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

//! INSTRUCTION 3C


Test(INC_A, value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x00;
	unsigned char time = instructions[0x3C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x01;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_A, value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x7F;
	unsigned char time = instructions[0x3C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_A, value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x80;
	unsigned char time = instructions[0x3C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
}

Test(INC_A, value_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xFF;
	unsigned char time = instructions[0x3C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x00;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_A, value_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x2F;
	unsigned char time = instructions[0x3C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 but it was %d", gb.cpu._registers.fh);
}

Test(INC_A, value_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xD7;
	unsigned char time = instructions[0x3C](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
	cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 but it was %d", gb.cpu._registers.fz);
	cr_assert_eq(gb.cpu._registers.fn, 0, "fn must be 0 but it was %d", gb.cpu._registers.fn);
	cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 but it was %d", gb.cpu._registers.fh);
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