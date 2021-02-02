/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** RES.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/Instructions.hpp"

Test(RES_0_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xBB;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x80, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x9F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x80, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x9E;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xD0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x80, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD0;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xB0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x80, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xB0;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x99;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x81, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x98;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x3B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x81, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x3A;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x81, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x8;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x34;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x81, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x34;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x25;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x82, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x4F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x82, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x4E;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xE0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x82, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x9C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x82, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x9C;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x31;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x83, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x53;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x83, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x52;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x4E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x83, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x4E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x83, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x4;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x73;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x84, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x72;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x2D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x84, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x8C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x84, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x8C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x84, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x2F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x85, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x73;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x85, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x72;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xB8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x85, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xB8;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x8A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x85, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x8A;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x99;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x87, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x98;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xA3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x87, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xE8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x87, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xE8;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_0_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xD8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x87, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x3A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x88, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x38;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xAF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x88, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xAD;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x6C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x88, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x6C;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x6D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x88, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x6D;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x96;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x89, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x94;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x6A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x89, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x68;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x61;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x89, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x61;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x15;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x89, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x15;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x27;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x25;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x1B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x19;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x2C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x2C;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x99;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x99;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x8B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x89;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x5;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x79;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x79;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x1;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x1C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xEE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xEC;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xF5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xF5;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x45;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x45;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xA6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xA4;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xCF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xCD;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x54;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x54;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xE5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xE5;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x7E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x7C;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x52;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x50;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x74;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x74;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_1_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xE0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x4E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x90, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x4A;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x96;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x90, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x92;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x51;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x90, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x51;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x29;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x90, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x29;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x3E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x91, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x3A;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x96;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x91, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x92;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x69;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x91, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x69;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x12;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x91, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x12;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x92, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xC0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x2D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x92, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x29;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x33;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x92, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x33;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xF8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x92, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xF8;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x5C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x93, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x58;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xB6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x93, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xB2;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xCA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x93, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xCA;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x71;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x93, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x71;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xE4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x94, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xD4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x94, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xD0;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xDB;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x94, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xDB;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x94, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xA;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x94;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x95, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x90;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xC6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x95, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xC2;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xAB;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x95, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xAB;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x5B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x95, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x5B;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x86;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x97, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x82;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x3F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x97, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x3B;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xB3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x97, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xB3;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_2_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x50;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x97, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x50;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x88;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x98, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xB8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x98, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xB0;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x98, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD5;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x13;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x98, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x13;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x8E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x99, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x86;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x3D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x99, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xD2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x99, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xD2;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x93;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x99, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x93;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x59;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x51;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x6A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x62;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x81;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xD0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9A, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xD0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x7D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x75;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xD8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xD0;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x41;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x41;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x24;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9B, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x2B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x23;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x99;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x91;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x80;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xB4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9C, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xB4;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x4B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x43;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x16;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x26;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x26;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x82;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9D, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x82;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xFC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xF4;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x2C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xD1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD1;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_3_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x13;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9F, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x13;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xDB;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xCB;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xFD;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xED;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xE9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xE9;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xE6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xE6;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xF1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xE1;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x71;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x61;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xA2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x83;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x83;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x1A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xA;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x9B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x23;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x23;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xA3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xA3;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xB1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xA1;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xD9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xC9;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xCC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xCC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x6A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x6A;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x31;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x21;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xB2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xAD;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xAD;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xEF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xEF;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x59;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x49;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x56;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x46;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xAC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xAC;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x6C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x6C;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x7D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x6D;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x5D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x4D;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x24;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_4_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x4A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x4A;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xA0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x34;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x14;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xDE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xDE;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xD8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD8;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xA8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x88;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xE7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xC7;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x9B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x9B;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x98;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x98;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x23;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x3;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xB4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x94;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xC0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x56;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x56;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x79;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x59;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xFF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xDF;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x42;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x42;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x8;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xB4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x94;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x20;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x0;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x50;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x50;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x97;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x97;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xE9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xC9;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x31;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x11;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xD1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD1;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x1D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x36;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x16;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xA9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x89;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xD2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD2;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_5_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xE;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xC8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x88;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xD0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x90;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x9A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x9A;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x3A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x3A;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xE2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xE4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA4;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x82;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x82;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xF;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x48;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x8;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x84;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x84;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x2E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x58;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x18;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x7E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x3E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x1D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x7;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x6C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x54;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x14;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x91;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x91;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xBC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xBC;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xC7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x87;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xFC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xBC;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x3B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x3B;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x27;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x27;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xE3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA3;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x4C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xC;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x2B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x2B;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_6_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x9C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x9C;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_b, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x9E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x1E;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_b, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xA3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x23;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_b, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x5C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x5C;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_b, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x1D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_c, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x83;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x3;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_c, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xD4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x54;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_c, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xF;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_c, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x23;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x23;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_d, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x9F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x1F;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_d, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x49;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_d, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x71;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x71;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_d, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x3B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x3B;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_e, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x82;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x2;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_e, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xB9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x39;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_e, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x11;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x11;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_e, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x40;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x40;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_h, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xA4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_h, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xBB;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x3B;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_h, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x3E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x3E;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_h, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x2C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_l, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xB2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x32;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_l, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x9A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x1A;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_l, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x70;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x70;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_l, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x79;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x79;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_a, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xB8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x38;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_a, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x8B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xB;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_a, random_value_unset_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x40;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x40;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(RES_7_a, random_value_unset_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x7B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x7B;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}