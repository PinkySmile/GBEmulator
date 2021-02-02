/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** RESunrefHL.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/Instructions.hpp"


Test(RES_0_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xD3);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xD2;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x37);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x36;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB3);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xB2;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x67);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x66;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x30);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x30;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xC2);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xC2;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_0_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xDA);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x86, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xDA;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x9E);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x9C;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF7);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF5;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xDE);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xDC;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x73);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x71;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x58);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x58;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xAC);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xAC;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF9);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_1_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xCD);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x8E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xCD;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xFF);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xFB;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x8E);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x8A;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x54);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x50;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x8F);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x8B;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x18);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x18;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x83);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x83;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF9);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xF9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_2_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x0);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x96, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x0;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA8);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xA0;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x2C);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x4F);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x47;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x18);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x10;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x85);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x85;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x74);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x74;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xC4);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xC4;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_3_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x76);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0x9E, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x76;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x73);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x63;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x90);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x80;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x30);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x20;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB3);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xA3;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x28);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x28;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xC);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xC;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xAA);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xAA;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_4_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA9);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xA6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xA9;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA1);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x81;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xBF);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x9F;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA5);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x85;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB5);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x95;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x45);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x45;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x17);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x58);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x58;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_5_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xDA);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xAE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xDA;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xD1);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x91;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xF0);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xB0;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xCF);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x8F;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x64);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x24;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x86);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x86;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x89);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x89;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA0);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xA0;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_6_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x3D);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xB6, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x3D;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_set_0)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xB4);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x34;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_set_1)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x97);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x17;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_set_2)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0xA6);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x26;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_set_3)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x8B);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0xB;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_unset_4)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x35);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x35;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_unset_5)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x6);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x6;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_unset_6)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x77);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x77;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}


Test(RES_7_unrefHL, random_value_unset_7)
{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x4E);
	unsigned char time = GBEmulator::Instructions::executeBitInstruction(0xBE, gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x4E;
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result,
				 result);
}
