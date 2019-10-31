/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Cartridge.cpp
*/

#include <sys/stat.h>
#include <cstring>
#include "Cartridge.hpp"

namespace GBEmulator::Memory
{
	const std::map<size_t, Cartridge::ROMSize> Cartridge::_sizeBytes{
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

	void Cartridge::_checkROM()
	{
		try {
			if (Cartridge::_sizeBytes.at(this->_rom.getSize()) != this->_rom.read(0x148))
				throw InvalidRomException(
					"The ROM size and size byte doesn't match (Expected byte " +
					std::to_string(Cartridge::_sizeBytes.at(this->_rom.getSize())) +
					" but found " + std::to_string(this->_rom.read(0x148)) + ")"
				);
		} catch (std::out_of_range &) {
			throw InvalidRomSizeException("The ROM size isn't valid");
		}
	}

	size_t Cartridge::_getBestSizeForFile(const std::string &path)
	{
		size_t best = 0x400000;
		struct stat stats;

		if (stat(path.c_str(), &stats) == -1)
			throw InvalidRomException("Cannot stat file " + path + ": " + strerror(errno));

		if (stats.st_size > 0x400000)
			throw InvalidRomSizeException("The ROM is too large (Max 4MB but rom size is " + std::to_string(stats.st_size / 1048576.) + "MB)");

		for (auto &size : Cartridge::_sizeBytes) {
			if (size.first >= static_cast<size_t>(stats.st_size) && size.first < best)
				best = size.first;
		}
		return best;
	}

	void Cartridge::resetROM()
	{
		this->_rom.resize(1);
		this->_rom.forceWrite(0, 0);
		this->_rom.setBankSize(1);
	}

	void Cartridge::loadROM(const std::string &rom)
	{
		try {
			size_t size = this->_getBestSizeForFile(rom);
			FILE *stream = fopen(rom.c_str(), "rb");
			unsigned char *mem;

			if (!stream)
				throw InvalidRomException("Cannot open file " + rom + ": " + strerror(errno));

			mem = new unsigned char[size];
			fread(mem, 1, size, stream);
			fclose(stream);
			this->_rom.setMemory(mem, size);
			this->_rom.setBankSize(ROM_BANK_SIZE);
			this->_checkROM();
		} catch (InvalidRomSizeException &) {
			this->resetROM();
			throw;
		}
	}

	unsigned char Cartridge::read(unsigned short address) const
	{
		return this->_rom.read(address);
	}

	void Cartridge::write(unsigned short address, unsigned char value)
	{
		this->_rom.write(address, value);
	}
}