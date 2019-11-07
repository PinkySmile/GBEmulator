/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Test_writeVRAM.cpp
*/

#include <criterion/criterion.h>
#include "../communism.hpp"
#include "../TestComponents.hpp"

Test(writeVRAM, simple_write)
{
	Tests::GBTest gb;

	for (int i = 0; i < NB_TILES; i++)
		gb.cpu._gpu._tiles[i] = 0;
	gb.cpu._gpu.writeVRAM(0, 0xff);

	std::vector<unsigned char> line;
	std::vector<unsigned char> correct_line = {2, 2, 2, 2, 2, 2, 2, 2};
	for (int i = 0; i < 8; i++)
		line.push_back(gb.cpu._gpu._tiles[i]);
	cr_assert(line == correct_line);
}

Test(writeVRAM, two_adjacent_write)
{
	Tests::GBTest gb;

	for (int i = 0; i < NB_TILES; i++)
		gb.cpu._gpu._tiles[i] = 0;
	gb.cpu._gpu.writeVRAM(0, 0xff);
	gb.cpu._gpu.writeVRAM(1, 0xf0);

	std::vector<unsigned char> line;
	std::vector<unsigned char> correct_line = {3, 3, 3, 3, 2, 2, 2, 2};
	for (int i = 0; i < 8; i++)
		line.push_back(gb.cpu._gpu._tiles[i]);
	cr_assert(line == correct_line);
}