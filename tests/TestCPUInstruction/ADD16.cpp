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

#define instructions GBEmulator::Instructions::_instructions


//! INSTRUCTION 09: ADD hl,bc

Test(ADD_HL_BC, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFFFF; i++) {
		for (unsigned j = 0; j <= 0xFFFF; j++) {
			gb.cpu._registers.hl = i;
			gb.cpu._registers.bc = j;

			unsigned time = instructions[0x09](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.hl, (i + j) % 0x10000, "Result must be 0x%X but it was 0x%X", (i + j) % 0x10000, gb.cpu._registers.hl);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xFF) + (j & 0xFF) > 0xFF, "fh must be %i but it was %d", (i & 0xFF) + (j & 0xFF) > 0xFF, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x10000, "fc must be %i but it was %d", (i + j) >= 0x10000, gb.cpu._registers.fc);
		}
	}
}


//! INSTRUCTION 19: ADD hl,de

Test(ADD_HL_DE, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFFFF; i++) {
		for (unsigned j = 0; j <= 0xFFFF; j++) {
			gb.cpu._registers.hl = i;
			gb.cpu._registers.de = j;

			unsigned time = instructions[0x19](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.hl, (i + j) % 0x10000, "Result must be 0x%X but it was 0x%X", (i + j) % 0x10000, gb.cpu._registers.hl);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xFF) + (j & 0xFF) > 0xFF, "fh must be %i but it was %d", (i & 0xFF) + (j & 0xFF) > 0xFF, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x10000, "fc must be %i but it was %d", (i + j) >= 0x10000, gb.cpu._registers.fc);
		}
	}
}


//! INSTRUCTION 29: ADD hl,hl

Test(ADD_HL_HL, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFFFF; i++) {
		gb.cpu._registers.hl = i;

		unsigned time = instructions[0x29](gb.cpu, gb.cpu._registers);

		cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
		cr_assert_eq(gb.cpu._registers.hl, (i + i) % 0x10000, "Result must be 0x%X but it was 0x%X", (i + i) % 0x10000, gb.cpu._registers.hl);
		cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
		cr_assert_eq(gb.cpu._registers.fh, (i & 0xFF) + (i & 0xFF) > 0xFF, "fh must be %i but it was %d", (i & 0xFF) + (i & 0xFF) > 0xFF, gb.cpu._registers.fh);
		cr_assert_eq(gb.cpu._registers.fc, (i + i) >= 0x10000, "fc must be %i but it was %d", (i + i) >= 0x10000, gb.cpu._registers.fc);
	}
}


//! INSTRUCTION 39: ADD hl,sp

Test(ADD_HL_SP, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFFFF; i++) {
		for (unsigned j = 0; j <= 0xFFFF; j++) {
			gb.cpu._registers.hl = i;
			gb.cpu._registers.sp = j;

			unsigned time = instructions[0x39](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.hl, (i + j) % 0x10000, "Result must be 0x%X but it was 0x%X", (i + j) % 0x10000, gb.cpu._registers.hl);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xFF) + (j & 0xFF) > 0xFF, "fh must be %i but it was %d", (i & 0xFF) + (j & 0xFF) > 0xFF, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x10000, "fc must be %i but it was %d", (i + j) >= 0x10000, gb.cpu._registers.fc);
		}
	}
}