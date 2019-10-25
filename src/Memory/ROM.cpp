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
	const std::map<size_t, ROM::ROMSize> ROM::_sizeBytes{
		{0x008000, SIZE_32KByte },
		{0x010000, SIZE_64KByte },
		{0x020000, SIZE_128KByte},
		{0x040000, SIZE_256KByte},
		{0x080000, SIZE_512KByte},
		{0x100000, SIZE_1MByte  },
		{0x200000, SIZE_2MByte  },
		{0x400000, SIZE_4MByte  },
		{0x120000, SIZE_1_1MByte},
		{0x140000, SIZE_1_2MByte},
		{0x180000, SIZE_1_5MByte},
	};

	void ROM::_checkROM()
	{
		try {
			if (ROM::_sizeBytes.at(this->_memory.size()) != this->read(0x148))
				throw InvalidRomException("The ROM size and size byte doesn't match");
		} catch (std::out_of_range &) {
			throw InvalidRomException("The ROM size isn't valid");
		}
	}

	ROM::ROM(const std::string &path, unsigned short bankSize) :
		Memory(0, bankSize)
	{
		std::ifstream stream{path};

		if (stream.fail())
			throw InvalidRomException("Cannot open file " + path);
		this->_memory = std::vector<unsigned char>(std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{});
		stream.close();
		this->_checkROM();
	}
}