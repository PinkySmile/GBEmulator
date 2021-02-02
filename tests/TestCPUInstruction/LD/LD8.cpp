/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** LD8.c
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/Instructions.hpp"

Test(LD_8_b_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x66;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x40, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x66;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x40, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xB;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x66;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x40, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x66;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x67;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x40, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x67;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xEE;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x41, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xEE;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xBA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x41, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x3C;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x41, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x3C;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x4F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x41, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x4F;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x7D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x42, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x7D;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xA2;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x42, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xB7;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x42, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xB7;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x7F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x42, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xFA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x43, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x1B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x43, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x1B;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xBA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x43, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x14;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x43, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x14;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x6B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x44, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x6B;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x8B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x44, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xF;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x44, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xF;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x44, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x3;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xBE;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x45, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xBE;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x80;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x45, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x7C;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x45, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x7C;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x4F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x45, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x4F;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xCB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x47, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xCB;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x36;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x47, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x36;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xE4;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x47, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xE4;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_b_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x83;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x47, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x83;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x57;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x48, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x57;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x78;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x48, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x78;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x1D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x48, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xC7;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x48, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xC7;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xF7;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x49, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xF7;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x49, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x8D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x49, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x8D;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xA7;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x49, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA7;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x48;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x48;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xC9;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xC9;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x1F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x1F;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xE8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xE8;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xB9;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xB9;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xD9;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xD9;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x6;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xC4;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xC4;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xA1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA1;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x36;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x36;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xB5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xB5;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x2;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x2;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xAB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xAB;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x70;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x70;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x3B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x3B;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x99;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x99;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x16;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x16;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x8D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x8D;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x0;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x0;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_c_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x4F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x1E;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xBD;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x50, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xBD;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x6E;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x50, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x6E;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x59;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x50, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x59;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xA5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x50, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xA5;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x8B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x51, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x73;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x51, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x73;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xD0;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x51, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xD0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xF1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x51, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xF1;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xBF;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x52, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xBF;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xD0;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x52, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xD0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xFF;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x52, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x42;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x52, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x42;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x34;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x53, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x34;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x34;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x53, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x34;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x61;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x53, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x61;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x85;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x53, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x85;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xFA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x54, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x23;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x54, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x23;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x54;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x54, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x54;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x46;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x54, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x46;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xEF;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x55, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xEF;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x9A;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x55, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x9A;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xC4;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x55, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xC4;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x17;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x55, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x71;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x57, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x71;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xD;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x57, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xD;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xB1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x57, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xB1;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_d_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x1B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x57, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x1B;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x64;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x58, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x64;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x4A;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x58, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x4A;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xAC;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x58, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xAC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x9B;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x58, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x9B;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x9E;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x59, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x9E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x71;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x59, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x71;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xEB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x59, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xEB;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xBE;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x59, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xBE;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xAB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xAB;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x51;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x51;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xAA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xAA;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xFA;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x56;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x56;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x10;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x10;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x7E;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x7E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x75;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x75;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xE0;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xE5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xE5;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xD5;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x95;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x95;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xA9;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xA9;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x77;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x77;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x9D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x9D;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xE1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xE1;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x1F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x1F;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xD5;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x68;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x68;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_e_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xD1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x5F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xD1;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x94;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x60, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x94;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0xE6;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x60, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xE6;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x25;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x60, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x25;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x74;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x60, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x74;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xCD;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x61, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xCD;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xCD;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x61, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xCD;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x5D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x61, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x5D;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x4D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x61, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x4D;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x46;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x62, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x46;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xEC;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x62, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xEC;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x16;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x62, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x16;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xDD;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x62, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xDD;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x5D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x63, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x5D;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x63, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xD5;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xA6;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x63, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xA6;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x35;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x63, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x19;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x64, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x19;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x21;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x64, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x21;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x98;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x64, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x98;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x2F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x64, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2F;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x2D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x65, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2D;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x17;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x65, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xFB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x65, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xFB;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xA8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x65, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xA8;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x23;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x67, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x23;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x57;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x67, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x57;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x9C;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x67, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x9C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_h_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xB1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x67, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xB1;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x68, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x3;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x63;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x68, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x63;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x67;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x68, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x67;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x35;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x68, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x73;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x69, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x73;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x17;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x69, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x22;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x69, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x22;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x2F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x69, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x2F;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x59;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x59;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x50;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x50;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xE3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xE3;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x12;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD5;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xB9;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xB9;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x1D;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x7F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x27;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x27;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xD2;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD2;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xD8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xC3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xC3;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x82;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x82;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x6C;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x6C;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x64;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x64;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x6A;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x6A;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x49;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x49;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x80;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xDC;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xDC;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_l_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xF3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x6F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xF3;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_b, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x63;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x78, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x63;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_b, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x9C;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x78, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x9C;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_b, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x19;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x78, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x19;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_b, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.b = 0x99;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x78, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x99;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_c, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xA3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x79, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA3;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_c, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0xA4;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x79, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA4;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_c, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x13;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x79, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x13;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_c, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.c = 0x35;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x79, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_d, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xAB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xAB;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_d, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xAF;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xAF;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_d, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0x88;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x88;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_d, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.d = 0xC3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xC3;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_e, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x5F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x5F;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_e, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x3F;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x3F;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_e, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0x6;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_e, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.e = 0xBB;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xBB;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_h, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xD8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_h, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0x65;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x65;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_h, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xED;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xED;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_h, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.h = 0xD4;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD4;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_l, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xA3;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA3;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_l, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xF8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xF8;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_l, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0xF2;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xF2;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_l, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.l = 0x42;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x42;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_a, random_value_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xF2;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xF2;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_a, random_value_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0xA1;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA1;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_a, random_value_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x1C;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x1C;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(LD_8_a_a, random_value_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.a = 0x1A;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0x7F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x1A;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}

