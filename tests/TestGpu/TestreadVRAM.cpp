/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestreadVRAM.cpp
*/

#include <criterion/criterion.h>
#include <iostream>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/ProcessingUnits/Instructions/CPUInstructions.hpp"

Test(readVRAM, simple_read)
{
	Tests::GBTest gb;

	for (int i = 0; i < NB_TILES; i++)
		gb.cpu._gpu._tiles[i] = 0;
	for (int i = 0; i < 8; i++)
		gb.cpu._gpu._tiles[i] = 2;
	int r = gb.cpu._gpu.readVRAM(0);
	cr_assert(r == 0xFF);
}

Test(readVRAM, read_less_than_a_byte)
{
	Tests::GBTest gb;

	for (int i = 0; i < NB_TILES; i++)
		gb.cpu._gpu._tiles[i] = 0;
	for (int i = 0; i < 4; i++)
		gb.cpu._gpu._tiles[i] = 2;
	int r = gb.cpu._gpu.readVRAM(0);
	cr_assert(r == 0xF0);
}
