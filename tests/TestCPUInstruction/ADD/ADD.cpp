/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ADD.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

#define instructions GBEmulator::Instructions::_instructions


//! INSTRUCTION 80: ADD a,b

Test(ADD_A_B, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.b = j;

			unsigned time = instructions[0x80](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 81: ADD a,c

Test(ADD_A_C, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.c = j;

			unsigned time = instructions[0x81](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 82: ADD a,d

Test(ADD_A_D, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.d = j;

			unsigned time = instructions[0x82](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 83: ADD a,e

Test(ADD_A_E, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.e = j;

			unsigned time = instructions[0x83](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 84: ADD a,h

Test(ADD_A_H, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.h = j;

			unsigned time = instructions[0x84](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 85: ADD a,l

Test(ADD_A_L, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.l = j;

			unsigned time = instructions[0x85](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 86: ADD a,(hl)

Test(ADD_A_HL_UNREF, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = instructions[0x86](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 87: ADD a,a

Test(ADD_A_A, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		gb.cpu._registers.a = i;

		unsigned time = instructions[0x87](gb.cpu, gb.cpu._registers);

		cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
		cr_assert_eq(gb.cpu._registers.a, (i + i) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + i) % 0x100, i, i, gb.cpu._registers.a);
		cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
		cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (i & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (i & 0xF) > 0xF, i, i, gb.cpu._registers.fh);
		cr_assert_eq(gb.cpu._registers.fc, (i + i) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + i) >= 0x100, i, i, gb.cpu._registers.fc);
		cr_assert_eq(gb.cpu._registers.fz, (i + i) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + i) % 0x100 == 0, i, i, gb.cpu._registers.fz);
	}
}


//! INSTRUCTION C6: ADD a,*

Test(ADD_A_val, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.a = i;
			gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = instructions[0xC6](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}