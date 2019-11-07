/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Test_isStatInterrupt.cpp
*/

#include <criterion/criterion.h>
#include <iostream>
#include "../communism.hpp"
#include "../TestComponents.hpp"

Test(isStatInterrupt, no_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._stat = 0;

	cr_assert(!gb.cpu._gpu._isStatInterrupt());
}

Test(isStatInterrupt, lyc_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._lyc = 4;
	gb.cpu._gpu._cycles = 1850;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b01000000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());
}

Test(isStatInterrupt, oam_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._cycles = 1850;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b00100000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());
}

Test(isStatInterrupt, vblank_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._cycles = 69000; // Current line > 144
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b00010000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());
}

Test(isStatInterrupt, hblank_interrupt)
{
	Tests::GBTest gb;

	gb.cpu._gpu._cycles = 60000;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b00001000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());
}

Test(isStatInterrupt, interrupt_x2)
{
	Tests::GBTest gb;

	gb.cpu._gpu._lyc = 4;
	gb.cpu._gpu._cycles = 1850;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b01000000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());

	gb.cpu._gpu._cycles = 60000;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b00001000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());

}

Test(isStatInterrupt, same_interrupt_x2)
{
	Tests::GBTest gb;

	gb.cpu._gpu._lyc = 4;
	gb.cpu._gpu._cycles = 1850;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b01000000U);

	cr_assert(gb.cpu._gpu._isStatInterrupt());

	gb.cpu._gpu._lyc = 4;
	gb.cpu._gpu._cycles = 1850;
	gb.cpu._gpu._control = 0b10000000U;
	gb.cpu._gpu._stat = static_cast<unsigned char>(0b01000000U);

	cr_assert(!gb.cpu._gpu._isStatInterrupt());

}