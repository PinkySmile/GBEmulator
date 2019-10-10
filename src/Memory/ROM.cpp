/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.cpp
*/

#include <fstream>
#include "ROM.hpp"

namespace GBEmulator
{
	ROM::ROM(const std::string &path, unsigned short bankSize) :
		Memory(0, bankSize)
	{
		std::ifstream stream{path};

		if (stream.fail())
			throw InvalidRomException("Cannot open file " + path);
		this->_memory = std::vector<unsigned char>(std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{});
	}
}