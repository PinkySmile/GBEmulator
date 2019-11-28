from random import randint

BITS = [
    [128, 0, 'b'],
    [129, 0, 'c'],
    [130, 0, 'd'],
    [131, 0, 'e'],
    [132, 0, 'h'],
    [133, 0, 'l'],
    [135, 0, 'a'],
    [136, 1, 'b'],
    [137, 1, 'c'],
    [138, 1, 'd'],
    [139, 1, 'e'],
    [140, 1, 'h'],
    [141, 1, 'l'],
    [143, 1, 'a'],
    [144, 2, 'b'],
    [145, 2, 'c'],
    [146, 2, 'd'],
    [147, 2, 'e'],
    [148, 2, 'h'],
    [149, 2, 'l'],
    [151, 2, 'a'],
    [152, 3, 'b'],
    [153, 3, 'c'],
    [154, 3, 'd'],
    [155, 3, 'e'],
    [156, 3, 'h'],
    [157, 3, 'l'],
    [159, 3, 'a'],
    [160, 4, 'b'],
    [161, 4, 'c'],
    [162, 4, 'd'],
    [163, 4, 'e'],
    [164, 4, 'h'],
    [165, 4, 'l'],
    [167, 4, 'a'],
    [168, 5, 'b'],
    [169, 5, 'c'],
    [170, 5, 'd'],
    [171, 5, 'e'],
    [172, 5, 'h'],
    [173, 5, 'l'],
    [175, 5, 'a'],
    [176, 6, 'b'],
    [177, 6, 'c'],
    [178, 6, 'd'],
    [179, 6, 'e'],
    [180, 6, 'h'],
    [181, 6, 'l'],
    [183, 6, 'a'],
    [184, 7, 'b'],
    [185, 7, 'c'],
    [186, 7, 'd'],
    [187, 7, 'e'],
    [188, 7, 'h'],
    [189, 7, 'l'],
    [191, 7, 'a'],
]

TEST_FORMAT = """
Test({type}_{bitnb}_{src}, random_value_{set_status}_{nb_test}) {{
	Tests::GBTest gb;
	unsigned char excepted_time = 8 - 4;

	gb.cpu._registers.{src} = 0x{random_value:X};
	unsigned char time = instructions[0x{instruction_number:X}](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.{src};
	unsigned char ex_result = 0x{except_value:X};
	cr_assert_eq(result, ex_result, "Register {src} must be 0x%X but it was 0x%X", ex_result, result);
}}
"""

def gen_res():
    for instruction_number, bitnb, src in BITS:
        for i in range(4):
            v = randint(0, 0xFF)
            if i < 2: v |= (1 << bitnb)
            else: v &= (0xFF - 2**bitnb)
            ev = v & (0xFF - 2**bitnb)
            print(TEST_FORMAT.format(instruction_number=instruction_number, bitnb=bitnb, src=src, set_status="set" if i < 2 else "unset",
                                     random_value=v, except_value=ev, nb_test=i, type="RES"))

def gen_set():
    for instruction_number, bitnb, src in BITS:
        for i in range(4):
            v = randint(0, 0xFF)
            if i < 2: v |= (1 << bitnb)
            else: v &= (0xFF - 2**bitnb)
            ev = v | (1 << bitnb)
            print(TEST_FORMAT.format(instruction_number=instruction_number + 0x40, bitnb=bitnb, src=src, set_status="set" if i < 2 else "unset",
                                     random_value=v, except_value=ev, nb_test=i, type="SET"))

if __name__ == '__main__':
    gen_set()