/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Test_write.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"

Test(write, wram)
{
	Tests::GBTest gb;

	gb.cpu.write(0xC000, 0x69);

	cr_assert(gb.cpu._ram._memory[0] == 0x69);

	gb.cpu.write(0xC005, 0x07);

	cr_assert(gb.cpu._ram._memory[5] == 0x07);
}

Test(write, echo_ram)
{
	Tests::GBTest gb;

	gb.cpu.write(0xC000, 0x69);

	cr_assert(gb.cpu._ram._memory[0] == 0x69);

	gb.cpu.write(0xC005, 0x07);

	cr_assert(gb.cpu._ram._memory[5] == 0x07);
}

//IOPorts
Test(write, windowY)
{
	Tests::GBTest gb;

	gb.cpu.write(0xFF4A, 10);
	cr_assert(gb.cpu._gpu._windowY == 10);
}

Test(write, windowX)
{
	Tests::GBTest gb;

	gb.cpu.write(0xFF4B, 10);
	cr_assert(gb.cpu._gpu._windowX == 3);
}