/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Cartridge.cpp
*/

#ifndef ARDUINO
#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <cmath>
#include "../ProcessingUnits/Instructions/Strings.hpp"
#else
#include <string.h>
#include <math.h>
#include <stdio.h>
#endif
#include "Cartridge.hpp"
#include "../ProcessingUnits/Instructions/CPUInstructions.hpp"

namespace GBEmulator::Memory
{
	const standard::map<uint32_t, Cartridge::ROMSize> Cartridge::_sizeBytes{
		standard::pair<uint32_t, Cartridge::ROMSize>{0x008000L, SIZE_32KByte },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x010000L, SIZE_64KByte },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x020000L, SIZE_128KByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x040000L, SIZE_256KByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x080000L, SIZE_512KByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x100000L, SIZE_1MByte  },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x200000L, SIZE_2MByte  },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x400000L, SIZE_4MByte  },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x120000L, SIZE_1_1MByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x140000L, SIZE_1_2MByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x180000L, SIZE_1_5MByte},
	};

	void Cartridge::_checkROM()
	{
#ifdef __cpp_exceptions
		try {
			if (Cartridge::_sizeBytes.at(this->_rom.getSize()) != this->_rom.rawRead(0x148))
				throw InvalidRomException(
					"The ROM size and size byte doesn't match (Expected byte " +
					standard::to_string(Cartridge::_sizeBytes.at(this->_rom.getSize())) +
					" but found " + standard::to_string(this->_rom.rawRead(0x148)) + ")"
				);
			if (this->_rom.rawRead(0x149) > 0x04)
				throw InvalidRomRamSizeException("The RAM size specified in the ROM file is not in range 0-3");
		} catch (standard::out_of_range &) {
			throw InvalidRomSizeException("The ROM size isn't valid");
		}
#endif
	}

	size_t Cartridge::_getBestSizeForFile(const standard::string &path)
	{
#ifndef __cpp_exceptions
#ifdef ARDUINO
		return 0;
#else
		struct stat stats;

		if (stat(path.c_str(), &stats) == -1)
			return 0;
		return stats.st_size;
#endif
#else
		size_t best = 0x400000;
		struct stat stats;

		if (stat(path.c_str(), &stats) == -1)
			throw InvalidRomException("Cannot stat file " + path + ": " + strerror(errno));

		if (stats.st_size > 0x400000) {
			standard::string sizeRepresentation;
#ifdef __serenity__
			char buffer[64];

			sprintf(buffer, "%f\n", stats.st_size / 1048576.);
			sizeRepresentation = buffer;
#else
			sizeRepresentation = standard::to_string(stats.st_size / 1048576.);
#endif
			throw InvalidRomSizeException("The ROM is too large (Max 4MB but rom size is " + sizeRepresentation + "MB)");
		}

		for (auto &size : Cartridge::_sizeBytes) {
			if (size.first >= static_cast<size_t>(stats.st_size) && size.first < best)
				best = size.first;
		}
		return best;
#endif
	}

	void Cartridge::resetROM()
	{
		this->_rom.resize(1);
		this->_rom.forceWrite(0, 0);
		this->_rom.setBankSize(1);
	}

	bool Cartridge::loadROM(const standard::string &rom)
	{
#ifdef __cpp_exceptions
		try {
#endif
			size_t size = this->_getBestSizeForFile(rom);

			if (size == 0)
				return false;

			FILE *stream = fopen(rom.c_str(), "rb");
			unsigned char *mem;

			if (!stream)
#ifdef __cpp_exceptions
				throw InvalidRomException("Cannot open file " + rom + ": " + strerror(errno));
#else
				return false;
#endif

			mem = new unsigned char[size];
			memset(mem, 0, size);
			fread(mem, 1, size, stream);
			fclose(stream);

			bool result = this->loadROM(mem, size, true);

			this->_savePath = rom.substr(0, rom.find_last_of('.')) + ".sav";
			stream = fopen(this->_savePath.c_str(), "rb");
			if (stream) {
				fread(mem, 1, size, stream);
				fclose(stream);
			}
			return false;
#ifdef __cpp_exceptions
		} catch (InvalidRomSizeException &) {
			this->resetROM();
			throw;
		} catch (InvalidRomRamSizeException &) {
			this->resetROM();
			throw;
		}
#endif
	}

	bool Cartridge::loadROM(unsigned char *data, size_t size, bool canKeep)
	{
		unsigned char *mem;

		if (canKeep)
			mem = data;
		else {
			mem = new unsigned char[size];
			memcpy(mem, data, size);
		}
		this->_rom.setMemory(mem, size);
		this->_rom.setBank(1);
		this->_rom.setBankSize(ROM_BANK_SIZE);
		this->_type = static_cast<CartridgeType>(this->_rom.rawRead(0x147));
		this->_checkROM();

		size = (this->_rom.rawRead(0x149) != 0) * 2 * pow(4, this->_rom.rawRead(0x149) - 1) * 1024;
		mem = new unsigned char[size];
		this->_ram.setMemory(mem, size);
		if (size > RAM_BANKING_SIZE)
			this->_ram.setBank(0);
		else
			this->_ram.setBankSize(size);
		for (size_t i = 0; i < size; i++)
			mem[i] = rand() % 0x100;
		this->_ramMem = mem;
	}

	bool Cartridge::saveRAM()
	{
		FILE *stream = fopen(this->_savePath.c_str(), "wb");

		if (!stream)
#ifdef __cpp_exceptions
			throw SavingFailedException("Cannot open " + this->_savePath + ": " + strerror(errno));
#else
			return false;
#endif

		fwrite(this->_ramMem, 1, this->_ram.getSize(), stream);
		fclose(stream);
		return true;
	}

	unsigned char Cartridge::read(uint16_t address) const
	{
		if (address < 0x4000)
			return this->_rom.rawRead(address);

		switch (this->_type) {
		default:
#ifdef __cpp_exceptions
			throw InvalidRomException("Cartridge " + Instructions::intToHex(this->_type) + " not implemented");
#endif
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
			else if (address < 0x8000)
				return this->_rom.read(address - 0x4000);
			return 0xFF;
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

	void Cartridge::write(uint16_t address, uint8_t value)
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

		default:
#ifdef __cpp_exceptions
			throw InvalidRomException("Cartridge " + Instructions::intToHex(this->_type) + " not implemented");
#endif
		case MBC1:
		case MBC1_RAM:
		case MBC1_RAM_BATTERY:
			return this->_handleMBC1Write(address, value);

		case MBC2:
		case MBC2_BATTERY:
			return this->_handleMBC2Write(address, value);

		case MBC3_TIMER_RAM_BATTERY:
		case MBC3_TIMER_BATTERY:
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
		}
	}

	void Cartridge::_handleHuCWrite(uint16_t address, uint8_t value)
	{
		return this->_handleMBC1Write(address, value);
	}

	void Cartridge::_handleMBC1Write(uint16_t address, uint8_t value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			return this->_ram.write(address - 0xA000, value);

		else if (address < 0x2000)
			this->_ramEnabled = (value & 0xFU) == 0x0A;

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

	void Cartridge::_handleMBC2Write(uint16_t address, uint8_t value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			return this->_ram.write(address - 0xA000, value);
		else if ((address >> 8) % 0x2 == 0 && address < 0x2000)
			this->_ramEnabled = (value & 0b1111U) == 0x0A;
		else if ((address >> 8) % 0x2 == 1 && address < 0x4000) {
			value &= 0b11111U;
			this->_rom.setBank(value + (value % 0x20 == 0));
		}
	}

	void Cartridge::_handleMBC3Write(uint16_t address, uint8_t value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			this->_ram.write(address - 0xA000, value);

		else if (address < 0x2000)
			this->_ramEnabled = (value & 0b1111U) == 0x0A;

		else if (address < 0x4000) {
			value &= 0b1111111U;
			this->_rom.setBank(value);

			//TODO: Implement timers
		} else if (address < 0x6000)
			this->_ram.setBank(value & 0b11U);
	}

	void Cartridge::_handleMBC5Write(uint16_t address, uint8_t value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			this->_ram.write(address - 0xA000, value);

		else if (address < 0x2000)
			this->_ramEnabled = (value & 0b1111U) == 0x0A;

		else if (address < 0x3000)
			this->_rom.setBank((this->_rom.getCurrentBank() & 0x100U) + value);

		else if (address < 0x4000)
			this->_rom.setBank((this->_rom.getCurrentBank() & 0xFFU) + ((value & 0x1U) << 8U));

		else if (address < 0x6000)
			this->_ram.setBank(value & 0b1111U);

		else if (address >= 0xA000 && this->_ramEnabled)
			printf("RAM disabled\n");
	}

	void Cartridge::_handleRumbleWrite(uint16_t address, uint8_t value)
	{
		if (address >= 0xA000 && this->_ramEnabled && this->_ram.getSize())
			this->_ram.write(address - 0xA000, value);

		else if (address < 0x2000)
			this->_ramEnabled = (value & 0b1111U) == 0x0A;

		else if (address < 0x3000)
			this->_rom.setBank((this->_rom.getCurrentBank() & 0x100U) + value);

		else if (address < 0x4000)
			this->_rom.setBank((this->_rom.getCurrentBank() & 0xFFU) + ((value & 0x1U) << 8U));

		else if (address < 0x6000)
			this->_ram.setBank(value & 0b111U);
	}

	bool Cartridge::isGameBoyOnly() const
	{
		return !(this->read(0x0143) & 0x80U);
	}
}
