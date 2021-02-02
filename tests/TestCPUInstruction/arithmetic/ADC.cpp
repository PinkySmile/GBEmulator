/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ADC.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/Instructions.hpp"

//! INSTRUCTION 88: ADC a,b

Test(ADC_A_B, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.b = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x88, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.b = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x88, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 89: ADC a,c

Test(ADC_A_C, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.c = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x89, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.c = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x89, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 8A: ADC a,d

Test(ADC_A_D, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.d = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8A, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.d = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8A, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 8B: ADC a,e

Test(ADC_A_E, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.e = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8B, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.e = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8B, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 8C: ADC a,h

Test(ADC_A_H, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.h = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8C, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.h = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8C, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 8D: ADC a,l

Test(ADC_A_L, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.l = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8D, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.l = j;

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8D, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 8E: ADC a,(hl)

Test(ADC_A_HL_UNREF, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8E, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = GBEmulator::Instructions::executeInstruction(0x8E, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 8F: ADC a,a

Test(ADC_A_A, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		gb.cpu._registers.fc = true;
		gb.cpu._registers.a = i;

		unsigned time = GBEmulator::Instructions::executeInstruction(0x8F, gb.cpu, gb.cpu._registers);

		cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
		cr_assert_eq(gb.cpu._registers.a, (i + i + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + i + 1) % 0x100, i, i + 1, gb.cpu._registers.a);
		cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
		cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (i & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (i & 0xF) + 1 > 0xF, i, i, gb.cpu._registers.fh);
		cr_assert_eq(gb.cpu._registers.fc, (i + i + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + i + 1) >= 0x100, i, i + 1, gb.cpu._registers.fc);
		cr_assert_eq(gb.cpu._registers.fz, (i + i + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + i + 1) % 0x100 == 0, i, i + 1, gb.cpu._registers.fz);
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		gb.cpu._registers.fc = false;
		gb.cpu._registers.a = i;

		unsigned time = GBEmulator::Instructions::executeInstruction(0x8F, gb.cpu, gb.cpu._registers);

		cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
		cr_assert_eq(gb.cpu._registers.a, (i + i) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + i) % 0x100, i, i, gb.cpu._registers.a);
		cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
		cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (i & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (i & 0xF) > 0xF, i, i, gb.cpu._registers.fh);
		cr_assert_eq(gb.cpu._registers.fc, (i + i) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + i) >= 0x100, i, i, gb.cpu._registers.fc);
		cr_assert_eq(gb.cpu._registers.fz, (i + i) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + i) % 0x100 == 0, i, i, gb.cpu._registers.fz);
	}
}


//! INSTRUCTION CE: ADC a,*

Test(ADC_A_val, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = GBEmulator::Instructions::executeInstruction(0xCE, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j + 1) % 0x100, "Result must be 0x%X when adding 0x%X with 0x%X but it was 0x%X", (i + j + 1) % 0x100, i, j + 1, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) + 1 > 0xF, "fh must be %i when adding 0x%X with 0x%X + 1 but it was %d", (i & 0xF) + (j & 0xF) + 1 > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j + 1) >= 0x100, "fc must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) >= 0x100, i, j + 1, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j + 1) % 0x100 == 0, "fz must be %i when adding 0x%X with 0x%X but it was %d", (i + j + 1) % 0x100 == 0, i, j + 1, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = GBEmulator::Instructions::executeInstruction(0xCE, gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}