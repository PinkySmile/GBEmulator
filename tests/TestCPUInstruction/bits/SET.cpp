/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SET.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/Instructions.hpp"

Test(SET_0_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xF9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xF9;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x71;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x71;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xAE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xAF;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xC0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xC1;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x3F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x3F;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x8B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x8A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xD2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xD3;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x21;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x21;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xA7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xA7;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x92;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x93;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x94;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x95;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x8F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x8F;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xAD;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xAD;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x98;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x99;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x68;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x69;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x2F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2F;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x4F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x4F;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x54;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x55;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x18;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x19;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xA7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xA7;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x3F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x3F;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xE2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xE3;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x1F;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xC3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xC3;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x11;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x11;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x16;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x94;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x95;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xB2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xB2;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x36;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x36;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x51;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x53;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xB8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xFA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x2;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xB8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x31;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xC9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x33;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x12;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x12;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xF;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x29;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x2B;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xD9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xDB;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xE6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xE6;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x3B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x3B;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xFC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x65;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x67;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x5A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x5A;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x32;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x32;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x54;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x56;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xD6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD6;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xBE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xBE;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x38;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x3A;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x14;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x16;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xFF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x17;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xAC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xAE;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xCD;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xCF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xCF;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x86;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x86;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x2E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x98;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x9C;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x12;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x16;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xBC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xBC;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x4;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x39;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x3D;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x21;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x25;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x7D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x7D;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xBE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xBE;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xA2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xA6;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x22;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x26;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x9E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x9E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x6C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x6C;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x73;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x77;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xC3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xC7;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x8F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x8F;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x2C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x19;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x4A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x4E;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x7C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x7C;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xD;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xD;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xC9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xCD;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x18;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x1C;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD5;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x4;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x41;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x45;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xD0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xD4;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x1F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x1F;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x3D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x3D;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xC2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xCA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x1E;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xDE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xDE;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x63;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x6B;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xD5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xD9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xDD;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x4A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x4A;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xC;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xF2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x54;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x5C;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xEC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xEC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xCC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xCC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xF4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x66;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x6E;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x9E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x9E;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xC9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xC9;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xA5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xAD;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x25;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x2D;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x9D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x9D;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x8;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x42;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x4A;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xA;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xB9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xB9;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x59;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x59;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xB1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xB9;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xF3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xDF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xFB;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x30;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xBA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x21;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x31;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xE4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xF4;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x7F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xBA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xE2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xF2;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x60;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x70;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x35;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x1D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x8D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x9D;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC3;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xD3;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xDE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xDE;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x98;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x98;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x6C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x7C;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x85;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x95;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x19;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x19;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x1C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x1C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x62;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x72;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x83;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x93;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x75;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x75;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x50;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x50;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x20;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x2A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x3A;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xB6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xB6;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x3C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x3C;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xEA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x83;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x93;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x76;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x76;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xE5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xE5;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x8D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xAD;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x58;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x78;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x2E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x2E;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xA0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xA0;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x59;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x79;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xC6;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xE9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xE6;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xAE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xAE;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xA8;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xA8;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xCE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xEE;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x11;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x31;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xA2;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x2F;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x2F;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x5D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x7D;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xDF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xBF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xBF;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x64;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x64;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x93;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xB3;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x5C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x7C;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x60;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xED, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x60;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xA5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xED, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xA5;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x9D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xED, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xBD;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xED, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x2F;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xFF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xFF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xD9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xF9;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xEF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x2C;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x57;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x57;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xF0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xF0;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x12;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x52;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x99;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF0, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD9;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xC5;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xC5;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xF9;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xF9;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x3D;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x7D;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF1, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0x5E;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xE0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x47;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x47;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0xC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x4C;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x9E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF2, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xDE;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x76;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x76;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xC7;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xC7;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xBC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xFC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x30;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF3, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x70;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xCF;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xCF;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xE0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x80;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xC0;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x26;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF4, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x66;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x44;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x44;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xFE;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x9A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xDA;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x89;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF5, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xC9;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xDA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xDA;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xCC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xCC;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x29;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x69;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x15;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF7, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x55;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_b, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x8E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0x8E;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_b, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0xD1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xD1;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_b, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x68;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xE8;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_b, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.b = 0x6A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF8, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.b;
	unsigned char ex_result = 0xEA;
	cr_assert_eq(result, ex_result, "Register b must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_c, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xE0;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xE0;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_c, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0xDC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xDC;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_c, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x67;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xE7;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_c, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.c = 0x4C;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xF9, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.c;
	unsigned char ex_result = 0xCC;
	cr_assert_eq(result, ex_result, "Register c must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_d, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x8B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_d, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x92;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0x92;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_d, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x4A;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xCA;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_d, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.d = 0x30;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFA, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.d;
	unsigned char ex_result = 0xB0;
	cr_assert_eq(result, ex_result, "Register d must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_e, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0xAC;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xAC;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_e, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x87;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x87;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_e, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x3B;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0xBB;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_e, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.e = 0x12;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFB, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.e;
	unsigned char ex_result = 0x92;
	cr_assert_eq(result, ex_result, "Register e must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_h, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x80;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_h, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0xB1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xB1;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_h, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x64;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xE4;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_h, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.h = 0x44;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFC, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.h;
	unsigned char ex_result = 0xC4;
	cr_assert_eq(result, ex_result, "Register h must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_l, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xBA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xBA;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_l, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0xC1;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0xC1;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_l, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x1E;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x9E;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_l, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.l = 0x4;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFD, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.l;
	unsigned char ex_result = 0x84;
	cr_assert_eq(result, ex_result, "Register l must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_a, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0xAA;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xAA;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_a, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x83;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0x83;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_a, random_value_unset_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x27;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xA7;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_a, random_value_unset_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.a = 0x49;
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xFF, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.a;
	unsigned char ex_result = 0xC9;
	cr_assert_eq(result, ex_result, "Register a must be 0x%X but it was 0x%X", ex_result, result);
}
