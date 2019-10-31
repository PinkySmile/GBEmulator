/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.cpp
*/

#include <fstream>
#include <sys/stat.h>
#include <cstring>
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
			if (ROM::_sizeBytes.at(this->_size) != this->read(0x148))
				throw InvalidRomException(
					"The ROM size and size byte doesn't match (Expected byte " +
					std::to_string(ROM::_sizeBytes.at(this->_size)) +
					" but found " + std::to_string(this->read(0x148)) + ")"
				);
		} catch (std::out_of_range &) {
			throw InvalidRomException("The ROM size isn't valid");
		}
	}

	ROM::ROM(const std::string &path, unsigned short bankSize) :
		Memory(getBestSizeForFile(path), bankSize)
	{
		FILE *stream = fopen(path.c_str(), "rb");

		if (!stream)
			throw InvalidRomException("Cannot open file " + path + ": " + strerror(errno));
		fread(this->_memory, 1, this->_size, stream);
		fclose(stream);
		this->_checkROM();
	}

	size_t ROM::getBestSizeForFile(const std::string &path)
	{
		size_t best = 0x400000;
		struct stat stats;

		if (stat(path.c_str(), &stats) == -1)
			throw InvalidRomException("Cannot stat file " + path + ": " + strerror(errno));

		if (stats.st_size > 0x400000)
			throw InvalidRomException("The ROM is too large (Max 4MB but rom size is " + std::to_string(stats.st_size / 1048576.) + "MB)");

		for (auto &size : ROM::_sizeBytes) {
			if (size.first >= static_cast<size_t>(stats.st_size) && size.first < best)
				best = size.first;
		}
		return best;
	}
}