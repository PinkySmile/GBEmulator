/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** RET.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/Instructions.hpp"

//! INSTRUCTION C0

Test(RET_nz, no_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC0, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x0000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

Test(RET_nz, basic_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 20;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC0, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x8FF8, "Register pc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION C8

Test(RET_z, no_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC8, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x0000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

Test(RET_z, basic_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 20;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC8, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x8FF8, "Register pc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION C9

Test(RET, basic_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 16;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC9, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x8FF8, "Register pc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION D0

Test(RET_nc, no_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD0, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x0000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

Test(RET_nc, basic_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 20;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD0, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x8FF8, "Register pc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION D8

Test(RET_c, no_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 8;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD8, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x0000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

Test(RET_c, basic_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 20;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD8, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x8FF8, "Register pc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION D9

Test(RETI, basic_return) {
	Tests::GBTest gb;

	gb.cpu._registers.sp = 0x8FFE;
	gb.cpu._registers.pc = 0x0000;
	gb.cpu.write(0x8FFF, 0x8F);
	gb.cpu.write(0x8FFE, 0xF8);

	unsigned char excepted_time = 16;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD9, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu._registers.pc, 0x8FF8, "Register pc must be 0x8FF8 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
	cr_assert(gb.cpu._interruptMasterEnableFlag, "The IME must be set");
}
