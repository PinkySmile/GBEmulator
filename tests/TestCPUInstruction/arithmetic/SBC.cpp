/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SBC.cpp
*/

#include <criterion/criterion.h>
#include "../../communism.hpp"
#include "../../TestComponents.hpp"
#include "../../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

#define instructions GBEmulator::Instructions::_instructions


//! INSTRUCTION 98: SBC a,b

Test(SBC_A_B, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.b = j;

			unsigned time = instructions[0x98](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.b = j;

			unsigned time = instructions[0x98](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 99: SBC a,c

Test(SBC_A_C, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.c = j;

			unsigned time = instructions[0x99](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.c = j;

			unsigned time = instructions[0x99](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 9A: SBC a,d

Test(SBC_A_D, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.d = j;

			unsigned time = instructions[0x9A](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.d = j;

			unsigned time = instructions[0x9A](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 9B: SBC a,e

Test(SBC_A_E, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.e = j;

			unsigned time = instructions[0x9B](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.e = j;

			unsigned time = instructions[0x9B](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 9C: SBC a,h

Test(SBC_A_H, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.h = j;

			unsigned time = instructions[0x9C](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.h = j;

			unsigned time = instructions[0x9C](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 9D: SBC a,l

Test(SBC_A_L, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.l = j;

			unsigned time = instructions[0x9D](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.l = j;

			unsigned time = instructions[0x9D](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 9E: SBC a,(hl)

Test(SBC_A_HL_UNREF, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = instructions[0x9E](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = instructions[0x9E](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION DE: SBC a,*

Test(SBC_A_val, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.a = i;
			gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = instructions[0xDE](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.a = i;
			gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j);

			unsigned time = instructions[0xDE](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.a, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.a);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}


//! INSTRUCTION 9F: SBC a,a

Test(SBC_A_A, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		gb.cpu._registers.fc = true;
		gb.cpu._registers.a = i;

		unsigned time = instructions[0x9F](gb.cpu, gb.cpu._registers);

		cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
		cr_assert_eq(gb.cpu._registers.a, 0xFF, "Result must be 0x%X when doing %i - %i - 1 but it was 0x%X", 0xFF, i, i, gb.cpu._registers.a);
		cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
		cr_assert_eq(gb.cpu._registers.fh, 1, "fh must be 1 when doing %i - %i - 1 but it was %d", i, i, gb.cpu._registers.fh);
		cr_assert_eq(gb.cpu._registers.fc, 1, "fc must be 1 when doing %i - %i - 1 but it was %d", i, i, gb.cpu._registers.fc);
		cr_assert_eq(gb.cpu._registers.fz, 0, "fz must be 0 when doing %i - %i - 1 but it was %d", i, i, gb.cpu._registers.fz);
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		gb.cpu._registers.fc = false;
		gb.cpu._registers.a = i;

		unsigned time = instructions[0x9F](gb.cpu, gb.cpu._registers);

		cr_assert_eq(time, 4, "Execution time must be 4 but it was %d", time);
		cr_assert_eq(gb.cpu._registers.a, 0, "Result must be 0x%X when doing %i - %i but it was 0x%X", 0, i, i, gb.cpu._registers.a);
		cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
		cr_assert_eq(gb.cpu._registers.fh, 0, "fh must be 0 when doing %i - %i but it was %d", i, i, gb.cpu._registers.fh);
		cr_assert_eq(gb.cpu._registers.fc, 0, "fc must be 0 when doing %i - %i but it was %d", i, i, gb.cpu._registers.fc);
		cr_assert_eq(gb.cpu._registers.fz, 1, "fz must be 1 when doing %i - %i but it was %d", i, i, gb.cpu._registers.fz);
	}
}
