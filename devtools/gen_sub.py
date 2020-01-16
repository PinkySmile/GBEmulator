def gen(sub):
	return "\n\n\n".join(["""//! INSTRUCTION """ + op + ": " + instr + """

Test(""" + instr.upper().replace(" ", "_").replace(",", "_").replace("(HL)", "HL_UNREF").replace("*", "val") + """, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.""" + instr[4:].split(",")[0] + """ = i;
			""" + ("(hl)" in instr and """gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j)""" or "*" in instr and ("""gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j)""") or ("gb.cpu._registers." + instr[4:].split(",")[1] + " = j")) + """;

			unsigned time = instructions[0x""" + op + """](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, """ + ("8" if ("(hl)" in instr or "*" in instr) else "4") + """, "Execution time must be """ + ("8" if ("(hl)" in instr or "*" in instr) else "4") + """ but it was %d", time);
			cr_assert_eq(gb.cpu._registers.""" + instr[4:].split(",")[0] + """, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.""" + instr[4:].split(",")[0] + """);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}""" for op, instr in sub])

def genc(subc):
	return "\n\n\n".join(["""//! INSTRUCTION """ + op + ": " + instr + """

Test(""" + instr.upper().replace(" ", "_").replace(",", "_").replace("(HL)", "HL_UNREF").replace("*", "val") + """, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = true;
			gb.cpu._registers.""" + instr[4:].split(",")[0] + """ = i;
			""" + ("(hl)" in instr and """gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j)""" or "*" in instr and ("""gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j)""") or ("gb.cpu._registers." + instr[4:].split(",")[1] + " = j")) + """;

			unsigned time = instructions[0x""" + op + """](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, """ + ("8" if ("(hl)" in instr or "*" in instr) else "4") + """, "Execution time must be """ + ("8" if ("(hl)" in instr or "*" in instr) else "4") + """ but it was %d", time);
			cr_assert_eq(gb.cpu._registers.""" + instr[4:].split(",")[0] + """, (i - j - 1 + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.""" + instr[4:].split(",")[0] + """);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF) + 1, "fh must be %i when doing %i - %i but it was %d", (i & 0xF) < (j & 0xF) + 1, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j + 1, "fc must be %i when doing %i - %i but it was %d", i < j + 1, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i - j - 1) % 0x100 == 0, "fz must be %i when doing %i - %i but it was %d", (i - j - 1) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}

	for (unsigned i = 0; i <= 0xFF; i++) {
		for (unsigned j = 0; j <= 0xFF; j++) {
			gb.cpu._registers.fc = false;
			gb.cpu._registers.""" + instr[4:].split(",")[0] + """ = i;
			""" + ("(hl)" in instr and """gb.cpu._registers.hl = 0xC000;
			gb.cpu.write(0xC000, j)""" or "*" in instr and ("""gb.cpu._registers.pc = 0xC000;
			gb.cpu.write(0xC000, j)""") or ("gb.cpu._registers." + instr[4:].split(",")[1] + " = j")) + """;

			unsigned time = instructions[0x""" + op + """](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, """ + ("8" if ("(hl)" in instr or "*" in instr) else "4") + """, "Execution time must be """ + ("8" if ("(hl)" in instr or "*" in instr) else "4") + """ but it was %d", time);
			cr_assert_eq(gb.cpu._registers.""" + instr[4:].split(",")[0] + """, (i - j + 0x100) % 0x100, "Result must be 0x%X when doing %i - %i but it was 0x%X", (i - j + 0x100) % 0x100, i, j, gb.cpu._registers.""" + instr[4:].split(",")[0] + """);
			cr_assert_eq(gb.cpu._registers.fn, 1, "fn must 1 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) < (j & 0xF), "fh must be %i when doing %i - %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, i < j, "fc must be %i when doing %i - %i but it was %d", i < j, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, i == j, "fz must be %i when doing %i - %i but it was %d", i == j, i, j, gb.cpu._registers.fz);
		}
	}
}""" for op, instr in subc])