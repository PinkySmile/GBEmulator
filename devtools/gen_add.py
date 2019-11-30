def gen16(add16):
    return "\n\n".join(["""
//! INSTRUCTION """ + op + ": " + instr + """

Test(""" + instr.upper().replace(" ", "_").replace(",", "_") + """, all_values) {
	Tests::GBTest gb;

	for (unsigned i = 0; i <= 0xFFFF; i++) {
		for (unsigned j = 0; j <= 0xFFFF; j++) {
			gb.cpu._registers.""" + instr[4:].split(",")[0] + """ = i;
			gb.cpu._registers.""" + instr[4:].split(",")[1] + """ = j;

			unsigned time = instructions[0x""" + op + """](gb.cpu, gb.cpu._registers);

			cr_assert_eq(time, 8, "Execution time must be 8 but it was %d", time);
			cr_assert_eq(gb.cpu._registers.""" + instr[4:].split(",")[0] + """, (i + j) % 0x10000, "Result must be 0x%X but it was 0x%X", (i + j) % 0x10000, gb.cpu._registers.""" + instr[4:].split(",")[0] + """);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xFF) + (j & 0xFF) > 0xFF, "fh must be %i but it was %d", (i & 0xFF) + (j & 0xFF) > 0xFF, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x10000, "fc must be %i but it was %d", (i + j) >= 0x10000, gb.cpu._registers.fc);
		}
	}
}""" for op, instr in add16])

def gen(add):
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
			cr_assert_eq(gb.cpu._registers.""" + instr[4:].split(",")[0] + """, (i + j) % 0x100, "Result must be 0x%X when adding %i with %i but it was 0x%X", (i + j) % 0x100, i, j, gb.cpu._registers.""" + instr[4:].split(",")[0] + """);
			cr_assert_eq(gb.cpu._registers.fn, 0, "fn must 0 but it was %d", gb.cpu._registers.fn);
			cr_assert_eq(gb.cpu._registers.fh, (i & 0xF) + (j & 0xF) > 0xF, "fh must be %i when adding %i with %i but it was %d", (i & 0xF) + (j & 0xF) > 0xF, i, j, gb.cpu._registers.fh);
			cr_assert_eq(gb.cpu._registers.fc, (i + j) >= 0x100, "fc must be %i when adding %i with %i but it was %d", (i + j) >= 0x100, i, j, gb.cpu._registers.fc);
			cr_assert_eq(gb.cpu._registers.fz, (i + j) % 0x100 == 0, "fz must be %i when adding %i with %i but it was %d", (i + j) % 0x100 == 0, i, j, gb.cpu._registers.fz);
		}
	}
}""" for op, instr in add])

[('09', 'ADD hl,bc'), ('19', 'ADD hl,de'), ('29', 'ADD hl,hl'), ('39', 'ADD hl,sp')]
[('80', 'ADD a,b'), ('81', 'ADD a,c'), ('82', 'ADD a,d'), ('83', 'ADD a,e'), ('84', 'ADD a,h'), ('85', 'ADD a,l'), ('86', 'ADD a,(hl)'), ('87', 'ADD a,a'), ('C6', 'ADD a,*')]
