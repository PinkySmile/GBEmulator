/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CALL.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/Instructions.hpp"

//! INSTRUCTION C4

Test(CALL_nz_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC4, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x00, "Value at address 0x8FFF must be 0x00 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x00, "Value at address 0x8FFE must be 0x00 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x8002, "Register pc must be 0x8002 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

Test(CALL_nz_a16, basic_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 24;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xC4, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x80, "Value at address 0x8FFF must be 0x80 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x02, "Value at address 0x8FFE must be 0x02 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x8000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION CC

Test(CALL_z_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fz = false;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xCC, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x00, "Value at address 0x8FFF must be 0x00 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x00, "Value at address 0x8FFE must be 0x00 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x8002, "Register pc must be 0x8002 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

Test(CALL_z_a16, basic_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fz = true;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 24;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xCC, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x80, "Value at address 0x8FFF must be 0x80 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x02, "Value at address 0x8FFE must be 0x02 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x8000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION CD

Test(CALL_a16, basic_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 24;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xCD, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x80, "Value at address 0x8FFF must be 0x80 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x02, "Value at address 0x8FFE must be 0x02 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x8000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION D4

Test(CALL_nc_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD4, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x00, "Value at address 0x8FFF must be 0x00 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x00, "Value at address 0x8FFE must be 0x00 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x8002, "Register pc must be 0x8002 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

Test(CALL_nc_a16, basic_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 24;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xD4, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x80, "Value at address 0x8FFF must be 0x80 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x02, "Value at address 0x8FFE must be 0x02 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x8000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}

//! INSTRUCTION DC

Test(CALL_c_a16, no_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fc = false;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 12;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xDC, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x00, "Value at address 0x8FFF must be 0x00 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x00, "Value at address 0x8FFE must be 0x00 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x8002, "Register pc must be 0x8002 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x9000, "Register sp must be 0x9000 but it was 0x%X", gb.cpu._registers.sp);
}

Test(CALL_c_a16, basic_jump) {
	Tests::GBTest gb;

	gb.cpu._registers.pc = 0x8000;
	gb.cpu._registers.sp = 0x9000;
	gb.cpu._registers.bc = 0x8FF8;
	gb.cpu._registers.fc = true;
	gb.cpu.write(0x8FFF, 0x00);
	gb.cpu.write(0x8FFE, 0x00);
	gb.cpu.write(0x8000, 0x00);
	gb.cpu.write(0x8001, 0x00);

	unsigned char excepted_time = 24;
	unsigned char time = GBEmulator::Instructions::executeInstruction(0xDC, gb.cpu, gb.cpu._registers);

	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	cr_assert_eq(gb.cpu.read(0x8FFF), 0x80, "Value at address 0x8FFF must be 0x80 but was 0x%X", gb.cpu.read(0x8FFF));
	cr_assert_eq(gb.cpu.read(0x8FFE), 0x02, "Value at address 0x8FFE must be 0x02 but was 0x%X", gb.cpu.read(0x8FFE));
	cr_assert_eq(gb.cpu._registers.pc, 0x0000, "Register pc must be 0x8000 but it was 0x%X", gb.cpu._registers.pc);
	cr_assert_eq(gb.cpu._registers.sp, 0x8FFE, "Register sp must be 0x8FFE but it was 0x%X", gb.cpu._registers.sp);
}
