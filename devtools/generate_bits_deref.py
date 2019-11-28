from random import randint

TEST_FORMAT = """
Test({type}_{bitnb}_{src}, random_value_{set_status}_{nb_test}) {{
	Tests::GBTest gb;
	unsigned char excepted_time = 16 - 4;

	gb.cpu._registers.hl = 0xC159;
	gb.cpu.write(0xC159, 0x{random_value:X});
	unsigned char time = instructions[0x{instruction_number:X}](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu.read(0xC159);
	unsigned char ex_result = 0x{except_value:X};
	cr_assert_eq(result, ex_result, "Value at addr 0xC159 (pointed by hl) must be 0x%X but it was 0x%X", ex_result, result);
}}
"""

def res_gen():
    for bitnb, instruction_number in enumerate(range(0x86, 0xC0, 0x8)):
        for i in range(8):
            v = randint(0, 0xFF)
            if i < 4: v |= (1 << bitnb)
            else: v &= (0xFF - 2**bitnb)
            ev = v & (0xFF - 2**bitnb)
            print(TEST_FORMAT.format(instruction_number=instruction_number, bitnb=bitnb, src="unrefHL", set_status="set" if i < 4 else "unset",
                                     random_value=v, except_value=ev, nb_test=i, type="RES"))

def set_gen():
    for bitnb, instruction_number in enumerate(range(0xC6, 0x100, 0x8)):
        for i in range(8):
            v = randint(0, 0xFF)
            if i < 4: v |= (1 << bitnb)
            else: v &= (0xFF - 2**bitnb)
            ev = v | (1 << bitnb)
            print(TEST_FORMAT.format(instruction_number=instruction_number, bitnb=bitnb, src="unrefHL", set_status="set" if i < 4 else "unset",
                                     random_value=v, except_value=ev, nb_test=i, type="SET"))


if __name__ == '__main__':
    set_gen()