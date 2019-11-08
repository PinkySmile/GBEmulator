/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Test_isVBlankInterrupt.cpp
*/

#include <criterion/criterion.h>
#include <iostream>
#include "../communism.hpp"
#include "../TestComponents.hpp"

Test(isVBlankInterrupt, no_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._control = 0;
	gb.cpu._gpu._cycles = 0;

	cr_assert(!gb.cpu._gpu._isVBlankInterrupt());
}

Test(isVBlankInterrupt, one_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._control = 0x80;
	gb.cpu._gpu._cycles = 69000;

	cr_assert(gb.cpu._gpu._isVBlankInterrupt());
}

Test(isVBlankIntrrupt, multiple_calls)
{
	Tests::GBTest gb;

	gb.cpu._gpu._control = 0x80;
	gb.cpu._gpu._cycles = 69000;

	cr_assert(gb.cpu._gpu._isVBlankInterrupt());

	cr_assert(!gb.cpu._gpu._isVBlankInterrupt());
}