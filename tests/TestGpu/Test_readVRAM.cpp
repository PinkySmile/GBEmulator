/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestreadVRAM.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"

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

Test(readVRAM, read_mutiple_location)
{
	Tests::GBTest gb;

	for (int i = 0; i < NB_TILES; i++)
		gb.cpu._gpu._tiles[i] = 0;
	for (int i = 0; i < 4; i++)
		gb.cpu._gpu._tiles[i] = 2;

	for (int i = 80; i < 88; i++)
		gb.cpu._gpu._tiles[i] = 3;
	int r = gb.cpu._gpu.readVRAM(0);
	cr_assert(r == 0xF0);
	r = gb.cpu._gpu.readVRAM(1);
	cr_assert(r == 0x00);
	r = gb.cpu._gpu.readVRAM(20);
	cr_assert(r == 0xFF);
	r = gb.cpu._gpu.readVRAM(21);
	cr_assert(r == 0xFF);
}
