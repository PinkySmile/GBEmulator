/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SETunrefHL.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

#define instructions GBEmulator::Instructions::_bitLevelInstructions

Test(SET_0_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x9D);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x9D;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB3);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xB3;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x5D);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x5D;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x91);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x91;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x1C);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x1D;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x1A);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x1B;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x78);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x79;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_0_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xE2);
	unsigned char time = instructions[0xC6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE3;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x42);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x42;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA2);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xA2;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF8);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xBD);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xBF;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6C);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x6E;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_1_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xC);
	unsigned char time = instructions[0xCE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x65);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x65;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x4C);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x4C;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xD6);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xD6;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6B);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x6F;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x70);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x74;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB9);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xBD;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_2_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA);
	unsigned char time = instructions[0xD6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x78);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x78;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB9);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xB9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x4F);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x4F;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x3A);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x3A;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xE6);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xEE;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF2);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFA;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF6);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFE;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_3_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x44);
	unsigned char time = instructions[0xDE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x4C;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x99);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x99;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF1);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF1;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x7F);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x7F;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x74);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x74;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA9);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xB9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x25);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6D);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x7D;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_4_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x87);
	unsigned char time = instructions[0xE6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x97;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x62);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x62;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x2A);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x2A;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF8);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF8;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x37);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x37;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x15);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xDF);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFF;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xDD);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFD;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_5_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xDB);
	unsigned char time = instructions[0xEE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFB;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xE4);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE4;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x68);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x68;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xD4);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xD4;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xE2);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE2;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x82);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xC2;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xAD);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xED;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x3E);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x7E;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_6_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x27);
	unsigned char time = instructions[0xF6](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x67;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_set_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xEA);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xEA;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_set_1) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xE9);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_set_2) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xE3);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE3;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_set_3) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xEF);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xEF;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_unset_4) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x48);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xC8;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_unset_5) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x59);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xD9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_unset_6) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x76);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF6;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}


Test(SET_7_unrefHL, random_value_unset_7) {
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x63);
	unsigned char time = instructions[0xFE](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xE3;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}
