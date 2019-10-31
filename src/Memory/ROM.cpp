/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.cpp
*/

#include "ROM.hpp"

namespace GBEmulator::Memory
{
	ROM::ROM() :
		Memory(1, 1, true)
	{
		this->forceWrite(0, 0);
	}
}