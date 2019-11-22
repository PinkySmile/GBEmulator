/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Cartridge.cpp
*/

#include <sys/stat.h>
#include <cstring>
#include <cmath>
#include "Cartridge.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"

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
			if (Cartridge::_sizeBytes.at(this->_rom.getSize()) != this->_rom.rawRead(0x148))
				throw InvalidRomException(
					"The ROM size and size byte doesn't match (Expected byte " +
					std::to_string(Cartridge::_sizeBytes.at(this->_rom.getSize())) +
					" but found " + std::to_string(this->_rom.rawRead(0x148)) + ")"
				);
			if (this->_rom.rawRead(0x149) > 0x04)
				throw InvalidRomRamSizeException("The RAM size specified in the ROM file is not in range 0-3");
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
			this->_rom.setBank(1);
			this->_rom.setBankSize(ROM_BANK_SIZE);
			this->_type = static_cast<CartridgeType>(this->_rom.rawRead(0x147));
			try {
				this->_checkROM();
			} catch (std::exception &) {
				throw;
			}
			this->_ram.resize(this->_rom.read((this->_rom.read(0x149) != 0) * 2 * std::pow(4, this->_rom.read(0x149) - 1)) * 1024);
		} catch (InvalidRomSizeException &) {
			this->resetROM();
			throw;
		} catch (InvalidRomRamSizeException &) {
			this->resetROM();
			throw;
		}
	}

	unsigned char Cartridge::read(unsigned short address) const
	{
		if (address < 0x4000)
			return this->_rom.rawRead(address);

		switch (this->_type) {
		case ROM_ONLY:
		case ROM_RAM:
		case ROM_RAM_BATTERY:
		case MMM01:
		case MMM01_RAM:
		case MMM01_RAM_BATTERY:
		case MBC1:
		case MBC1_RAM:
		case MBC1_RAM_BATTERY:
		case MBC2:
		case MBC2_BATTERY:
		case MBC3:
		case MBC3_RAM:
		case MBC3_RAM_BATTERY:
		case MBC3_TIMER_BATTERY:
		case MBC3_TIMER_RAM_BATTERY:
		case MBC5:
		case MBC5_RAM:
		case MBC5_RAM_BATTERY:
		case MBC5_RUMBLE:
		case MBC5_RUMBLE_RAM:
		case MBC5_RUMBLE_RAM_BATTERY:
		case HuC1_RAM_BATTERY:
		case HuC3:
			if (address >= 0xA000 && this->_ram.getSize())
				return this->_ram.read(address - 0xA000);
			else if (address < 0x7FFF)
				return this->_rom.read(address - 0x4000);
			return 0xFF;
		default:
			throw InvalidRomException("Cartridge " + Instructions::intToHex(this->_type) + " not implemented");
		}
	}

	unsigned char Cartridge::getRamBank() const
	{
		return this->_ram.getCurrentBank();
	}

	unsigned char Cartridge::getRomBank() const
	{
		return this->_rom.getCurrentBank();
	}

	void Cartridge::write(unsigned short address, unsigned char value)
	{
		switch (this->_type) {
		case ROM_ONLY:
			return;

		case ROM_RAM:
		case ROM_RAM_BATTERY:
		case MMM01:
		case MMM01_RAM:
		case MMM01_RAM_BATTERY:
			if (address >= 0xA000 && this->_ram.getSize())
				return this->_ram.write(address - 0xA000, value);
			break;

		case MBC1:
		case MBC1_RAM:
		case MBC1_RAM_BATTERY:
			return this->_handleMBC1Write(address, value);

		case MBC2:
		case MBC2_BATTERY:
			return this->_handleMBC2Write(address, value);

		case MBC3_RAM_BATTERY:
		case MBC3_RAM:
		case MBC3:
			return this->_handleMBC3Write(address, value);

		case MBC5:
		case MBC5_RAM:
		case MBC5_RAM_BATTERY:
			return this->_handleMBC5Write(address, value);

		case MBC5_RUMBLE:
		case MBC5_RUMBLE_RAM:
		case MBC5_RUMBLE_RAM_BATTERY:
			return this->_handleRumbleWrite(address, value);

		case HuC1_RAM_BATTERY:
		case HuC3:
			return this->_handleHuCWrite(address, value);

		default:
			throw InvalidRomException("Cartridge " + Instructions::intToHex(this->_type) + " not implemented");
		}
	}

	void Cartridge::_handleHuCWrite(unsigned short address, unsigned char value)
	{
		return this->_handleMBC1Write(address, value);
	}

	void Cartridge::_handleMBC1Write(unsigned short address, unsigned char value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			return this->_ram.write(address - 0xA000, value);

		else if (address < 0x2000)
			this->_ramEnabled = value & 0b1010U;

		else if (address < 0x4000) {
			value &= 0b11111U;
			value |= value == 0;
			this->_romBank = (this->_romBank & 0b1100000U) | value;
			this->_rom.setBank(this->_ramExtended ? value : this->_romBank);

		} else if (address < 0x6000) {
			if (this->_ramExtended) {
				if (this->_ram.getSize())
					this->_ram.setBank(value & 0b11U);
			} else {
				this->_romBank = (this->_romBank & 0b0011111U) | ((value & 0b11U) << 5U);
				this->_rom.setBank(this->_romBank);
			}

		} else if (address < 0x8000) {
			this->_ramExtended = value & 0b1U;
			if (!this->_ramExtended) {
				if (this->_ram.getSize())
					this->_ram.setBank(0);
			} else
				this->_rom.setBank(this->_romBank & 0b11111U);
		}
	}

	void Cartridge::_handleMBC2Write(unsigned short address, unsigned char value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			return this->_ram.write(address - 0xA000, value);
		else if ((address >> 8) % 0x2 == 0 && address < 0x2000)
			this->_ramEnabled = value & 0b1010U;
		else if ((address >> 8) % 0x2 == 1 && address < 0x4000) {
			value &= 0b11111U;
			this->_rom.setBank(value + (value % 0x20 == 0 && value <= 0x60));
		}
	}

	void Cartridge::_handleMBC3Write(unsigned short address, unsigned char value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			this->_ram.write(address - 0xA000, value);
		else if (address < 0x2000)
			this->_ramEnabled = value & 0b1010U;
		else if (address < 0x4000) {
			value &= 0b1111111U;
			this->_rom.setBank(value + (value % 0x20 == 0 && value <= 0x60));
		} else if (address < 0x6000)
			this->_ram.setBank(value & 0b11U);
	}

	void Cartridge::_handleMBC5Write(unsigned short address, unsigned char value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			this->_ram.write(address - 0xA000, value);
		else if (address < 0x2000)
			this->_ramEnabled = value & 0b1010U;
		else if (address < 0x3000)
			this->_rom.setBank((this->_rom.getCurrentBank() & 0x100U) + value);
		else if (address < 0x4000) {
			this->_rom.setBank((this->_rom.getCurrentBank() & 0xFFU) + ((value & 0x1U) << 8U));
		} else if (address < 0x6000)
			this->_ram.setBank(value & 0b1111U);
	}

	void Cartridge::_handleRumbleWrite(unsigned short address, unsigned char value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			this->_ram.write(address - 0xA000, value);
		else if (address < 0x2000)
			this->_ramEnabled = value & 0b1010U;
		else if (address < 0x3000)
			this->_rom.setBank((this->_rom.getCurrentBank() & 0x100U) + value);
		else if (address < 0x4000) {
			this->_rom.setBank((this->_rom.getCurrentBank() & 0xFFU) + ((value & 0x1U) << 8U));
		} else if (address < 0x6000)
			this->_ram.setBank(value & 0b111U);
	}
}