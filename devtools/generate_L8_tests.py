from random import randint

LD_8 = [
    [64, 'b', 'b'],
    [65, 'b', 'c'],
    [66, 'b', 'd'],
    [67, 'b', 'e'],
    [68, 'b', 'h'],
    [69, 'b', 'l'],
    [71, 'b', 'a'],
    [72, 'c', 'b'],
    [73, 'c', 'c'],
    [74, 'c', 'd'],
    [75, 'c', 'e'],
    [76, 'c', 'h'],
    [77, 'c', 'l'],
    [79, 'c', 'a'],
    [80, 'd', 'b'],
    [81, 'd', 'c'],
    [82, 'd', 'd'],
    [83, 'd', 'e'],
    [84, 'd', 'h'],
    [85, 'd', 'l'],
    [87, 'd', 'a'],
    [88, 'e', 'b'],
    [89, 'e', 'c'],
    [90, 'e', 'd'],
    [91, 'e', 'e'],
    [92, 'e', 'h'],
    [93, 'e', 'l'],
    [95, 'e', 'a'],
    [96, 'h', 'b'],
    [97, 'h', 'c'],
    [98, 'h', 'd'],
    [99, 'h', 'e'],
    [100, 'h', 'h'],
    [101, 'h', 'l'],
    [103, 'h', 'a'],
    [104, 'l', 'b'],
    [105, 'l', 'c'],
    [106, 'l', 'd'],
    [107, 'l', 'e'],
    [108, 'l', 'h'],
    [109, 'l', 'l'],
    [111, 'l', 'a'],
    [120, 'a', 'b'],
    [121, 'a', 'c'],
    [122, 'a', 'd'],
    [123, 'a', 'e'],
    [124, 'a', 'h'],
    [125, 'a', 'l'],
    [127, 'a', 'a'],
]


TEST_FORMAT = """
Test(LD_8_{rtarget}_{rsrc}, random_value_{nb_test}) {{
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	gb.cpu._registers.{rsrc} = 0x{random_value:X};
	unsigned char time = instructions[0x{instruction_number:X}](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned char result = gb.cpu._registers.{rtarget};
	unsigned char ex_result = 0x{random_value:X};
	cr_assert_eq(result, ex_result, "Register {rtarget} must be 0x%X but it was 0x%X", ex_result, result);
}}
"""


for instruction_number, rtarget, rsrc,  in LD_8:
    for i in range(4):
        random_value = randint(0, 255)
        print(TEST_FORMAT.format(rsrc=rsrc, rtarget=rtarget, nb_test=i, random_value=random_value, instruction_number=instruction_number))