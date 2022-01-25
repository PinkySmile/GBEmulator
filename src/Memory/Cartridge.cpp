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
#include <dirent.h>
#include <fstream>
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
#ifndef _WIN32
	std::string sanatize(std::string val)
	{
		for (auto i = 0ULL; i < val.size(); i++) {
			if (val[i] == '"' || val[i] == '\\' || val[i] == '$') {
				val.insert(val.begin() + i, '\\');
				i++;
			}
		}
		return val;
	}
	std::string exec(const char *cmd) {
		setenv("LANG", "EN_us.UTF8", true);

		std::array<char, 128> buffer;
		std::string result;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

		printf("Exec %s\n", cmd);
		if (!pipe)
			throw std::runtime_error("popen() failed!");
		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			result += buffer.data();
		}
		return result;
	}
#endif

	const standard::map<uint32_t, Cartridge::ROMSize> Cartridge::_sizeBytes{
		standard::pair<uint32_t, Cartridge::ROMSize>{0x008000L, SIZE_32KByte },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x010000L, SIZE_64KByte },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x020000L, SIZE_128KByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x040000L, SIZE_256KByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x080000L, SIZE_512KByte},
		standard::pair<uint32_t, Cartridge::ROMSize>{0x100000L, SIZE_1MByte  },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x200000L, SIZE_2MByte  },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x400000L, SIZE_4MByte  },
		standard::pair<uint32_t, Cartridge::ROMSize>{0x800000L, SIZE_8MByte  },
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
		size_t best = 0x800000;
		struct stat stats;

		if (stat(path.c_str(), &stats) == -1)
			throw InvalidRomException("Cannot stat file " + path + ": " + strerror(errno));

		if (stats.st_size > 0x800000) {
			standard::string sizeRepresentation;
#ifdef __serenity__
			char buffer[64];

			sprintf(buffer, "%f\n", stats.st_size / 1048576.);
			sizeRepresentation = buffer;
#else
			sizeRepresentation = standard::to_string(stats.st_size / 1048576.);
#endif
			throw InvalidRomSizeException("The ROM is too large (Max 8MB but rom size is " + sizeRepresentation + "MB)");
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

	bool Cartridge::loadROM(const standard::string &rom, bool resetActual)
	{
		printf("Loading rom %s\n", rom.c_str());
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

			bool result = this->loadROM(mem, size, true, resetActual);

			this->_savePath = rom.substr(0, rom.find_last_of('.')) + ".sav";
			this->loadRAM(this->_savePath);
			return result;
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

	bool Cartridge::loadROM(const unsigned char *data, size_t size, bool canKeep, bool resetActual)
	{
		unsigned char *mem;

		if (canKeep)
			mem = const_cast<unsigned char *>(data);
		else {
			mem = new unsigned char[size];
			memcpy(mem, data, size);
		}
		this->_rom.setMemory(mem, size);
		this->_rom.setBankSize(ROM_BANK_SIZE);
		this->_rom.setBank(1);
		if (resetActual) {
			mem = new unsigned char[size];
			memcpy(mem, data, size);
			this->_originalRom.setMemory(mem, size);
			this->_originalRom.setBankSize(ROM_BANK_SIZE);
			this->_originalRom.setBank(1);
		}
		this->_type = static_cast<CartridgeType>(this->_rom.rawRead(0x147));
		if (resetActual)
			this->_actualType = this->_type;
		this->_checkROM();

		if (this->_type == WIFI_CUSTOM_ROM)
			size = 0x400;
		else
			size = (this->_rom.rawRead(0x149) != 0) * 2 * pow(4, this->_rom.rawRead(0x149) - 1) * 1024;

		mem = new unsigned char[size];
		this->_ram.setMemory(mem, size);
		this->_ram.setBankSize(RAM_BANKING_SIZE);
		if (size > RAM_BANKING_SIZE)
			this->_ram.setBank(0);
		else
			this->_ram.setBankSize(size);
		if (this->_type == WIFI_CUSTOM_ROM)
			memset(this->_ram.getBuffer(), 0, size);
		else
			for (size_t i = 0; i < size; i++)
				mem[i] = rand() % 0x100;
		return true;
	}

	bool Cartridge::loadRAM(const standard::string &ram)
	{
		if (this->_type == WIFI_CUSTOM_ROM)
			return true;
		FILE *stream = fopen(ram.c_str(), "rb");
		if (stream) {
			fread(this->_ram.getBuffer(), 1, this->_ram.getSize(), stream);
			fclose(stream);
			return true;
		}
		return false;
	}

	bool Cartridge::loadRAM(unsigned char *data, size_t size)
	{
		if (this->_type == WIFI_CUSTOM_ROM)
			return true;
		if (this->_ram.getSize() != size)
			return false;
		memcpy(this->_ram.getBuffer(), data, size);
		return true;
	}

	bool Cartridge::saveRAM(const char *path)
	{
		if (this->_type == WIFI_CUSTOM_ROM)
			return true;
		if (this->_ram.getSize() == 0)
			return true;

		FILE *stream = fopen(path ? path : this->_savePath.c_str(), "wb");

		if (!stream)
#ifdef __cpp_exceptions
			throw SavingFailedException("Cannot open " + this->_savePath + ": " + strerror(errno));
#else
			return false;
#endif

		fwrite(this->_ram.getBuffer(), 1, this->_ram.getSize(), stream);
		fclose(stream);
		return true;
	}

	uint8_t Cartridge::read(uint16_t address) const
	{
		if (address < 0x4000)
			return this->_rom.rawRead(address);

		switch (this->_type) {
		default:
#ifdef __cpp_exceptions
			throw InvalidRomException("Cartridge " + Instructions::intToHex(this->_type) + " not implemented");
#endif
#ifndef _WIN32
		case WIFI_CUSTOM_ROM:
			if ((address & (1 << 14)) && (address & (1 << 15)))
				return (this->_interrupt << 1) | this->_ram.read(address & 0x3FF);
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
			if (address < 0x8000)
				return this->_rom.read(address - 0x4000);
			if (address >= 0xA000 && this->_ram.getSize())
				return this->_ram.read(address & 0x3FF);
			return 0xFF;
		case FILE_SYSTEM_CUSTOM_ROM:
			if (address < 0x8000)
				return this->_rom.read(address - 0x4000);
			if (address == 0xA000)
				return this->_currentEntryLow;
			if (address == 0xA001)
				return this->_currentEntryHigh;
			if (address == 0xA002)
				return this->_entries.size() & 0xFF;
			if (address == 0xA003)
				return this->_entries.size() >> 8;
			if (this->_currentEntry >= this->_entries.size())
				return 0xFF;
			if (address == 0xA004)
				return this->_entries[this->_currentEntry].first;
			if (address <= this->_entries[this->_currentEntry].second.size() + 0xA005)
				return this->_entries[this->_currentEntry].second[address - 0xA005];
			return 0xFF;
		}
	}

	uint8_t Cartridge::getRamBank() const
	{
		return this->_ram.getCurrentBank();
	}

	uint8_t Cartridge::getRomBank() const
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

		case FILE_SYSTEM_CUSTOM_ROM:
			return this->_handleFSCustomWrite(address, value);

#ifndef _WIN32
		case WIFI_CUSTOM_ROM:
			return this->_handleWifiCustomWrite(address, value);
#endif
		}
	}

	void Cartridge::_handleHuCWrite(uint16_t address, uint8_t value)
	{
		return this->_handleMBC1Write(address, value);
	}

	void Cartridge::_handleFSCustomWrite(uint16_t address, uint8_t value)
	{
		if (address == 0xA000) {
			this->_currentEntryLow = value;
			return;
		}

		if (address == 0xA001) {
			this->_currentEntryHigh = value;
			return;
		}

		if (address == 0xA002) {
			this->_onlyRoms = (value & 1) == 1;
			this->_getFolderContent(this->_rootFolder + this->_currentSelectedFolder, this->_currentSelectedFolder != "/");
			return;
		}

		if (address < 0xB000 || this->_currentEntry >= this->_entries.size())
			return;

		auto entry = this->_entries[this->_currentEntry];

		printf("Selected entry %s\n", entry.second.c_str());
		if (entry.first == TYPE_DIRECTORY) {
			if (entry.second == "..") {
				auto pos = this->_currentSelectedFolder.find_last_of('/');

				if (pos == 0)
					this->_currentSelectedFolder = "/";
				else
					this->_currentSelectedFolder = this->_currentSelectedFolder.substr(0, pos);
				printf("New current folder is %s\n", this->_currentSelectedFolder.c_str());
				this->_getFolderContent(this->_rootFolder + this->_currentSelectedFolder, this->_currentSelectedFolder != "/");
				return;
			}

			if (this->_getFolderContent(this->_rootFolder + this->_currentSelectedFolder + "/" + entry.second, true)) {
				this->_currentSelectedFolder += "/" + entry.second;
				printf("New current folder is %s\n", this->_currentSelectedFolder.c_str());
			}
			return;
		}
		if (entry.first != TYPE_SYMLINK) {
			this->loadROM(this->_rootFolder + this->_currentSelectedFolder + "/" + entry.second, false);
			return;
		}
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

	void Cartridge::_handleWifiCustomWrite(uint16_t address, uint8_t value)
	{
		if (address < 0x8000)
			return;

		this->_ram.write(address - 0xA000, value);
		this->_interrupt |= (address & 0x3FF) == 0x3FF;
		if ((address & 0x3FF) == 0x3FE) {
			switch (this->_ram.read(0)) {
			case 1: {
				auto ssid     = reinterpret_cast<char *>(this->_ram.getBuffer() + 1);
				auto ssidLen  = strnlen(ssid, 0x200);
				auto passwd   = reinterpret_cast<char *>(this->_ram.getBuffer() + 1 + strnlen(ssid, 0x200) + 1);
				auto passwdLen= strnlen(passwd, 0x200 - (strnlen(ssid, 0xFFF) + 1));
				auto v = exec((
					"nmcli dev wifi connect \"" + sanatize({ssid, ssid + ssidLen}) + "\" "
					"password \"" + sanatize({passwd, passwd + passwdLen}) + "\" 2>&1"
				).c_str());

				memset(this->_ram.getBuffer(), 0, std::min<size_t>(0x2000, ssidLen + passwdLen + 3));
				if (v.find("successfully activated") == std::string::npos)
					return sendOpcode(3, v.c_str(), v.size());

				unsigned char wifiLevel = Cartridge::getWifiLevel();

				sendOpcode(1, &wifiLevel, 1);
				return;
			}
			case 2: {
				auto len = *reinterpret_cast<unsigned short *>(this->_ram.getBuffer() + 1);

				if (len < 0x400 - 3) { // Let's not do that
					if (*(this->_ram.getBuffer() + 3) == 1 && len == 4) {
						struct {
							unsigned char op;
							float x;
							float y;
							unsigned char zoom;
						} pack;

						this->_x += *(char *)(this->_ram.getBuffer() + 4);
						this->_y += *(char *)(this->_ram.getBuffer() + 5);
						pack.op = *(this->_ram.getBuffer() + 3);
						pack.x = this->_x;
						pack.y = this->_y;
						pack.zoom += *(char *)(this->_ram.getBuffer() + 6);
						this->_sock.send(&pack, sizeof(pack), this->_addr, this->_port);
					} else
						this->_sock.send(this->_ram.getBuffer() + 3, len, this->_addr, this->_port);
					puts("Sent!");
					this->_sent = true;
				}
				memset(this->_ram.getBuffer(), 0, std::min<size_t>(0x400, len + 3));
				return;
			}
			default:
				memset(this->_ram.getBuffer(), 0, 0x200);
				return;
			}
		}
	}

	bool Cartridge::isGameBoyOnly() const
	{
		return !(this->read(0x0143) & 0x80U);
	}

	bool Cartridge::goToMenu()
	{
		if (this->_actualType != FILE_SYSTEM_CUSTOM_ROM)
			return false;
		this->saveRAM();
		return this->loadROM(this->_originalRom.getBuffer(), this->_originalRom.getSize(), false, false);
	}

	bool Cartridge::setRootFolder(const std::string &root)
	{
		if (!this->_getFolderContent(root, false))
#ifdef __cpp_exceptions
			throw InvalidRomException(strerror(errno));
#else
			return false;
#endif
		this->_rootFolder = root;
		this->_currentSelectedFolder = "/";
		return true;
	}

	bool Cartridge::_getFolderContent(const std::string &path, bool keepDotDot)
	{
		DIR *stream = opendir(path.c_str());

		printf("Fetching content of %s\n", path.c_str());
		if (!stream)
			return false;
		this->_entries.clear();
		for (struct dirent *dir = readdir(stream); dir && this->_entries.size() < 65535; dir = readdir(stream)) {
			if (strcmp(dir->d_name, ".") == 0)
				continue;
			if (strcmp(dir->d_name, "..") == 0 && !keepDotDot)
				continue;

			struct stat s;
			auto chr = strrchr(dir->d_name, '.');

			stat((path + "/" + dir->d_name).c_str(), &s);
			if (
				this->_onlyRoms &&
				!S_ISDIR(s.st_mode) &&
				(chr == nullptr || (
					strcmp(chr, ".gb") != 0 &&
					strcmp(chr, ".gbc") != 0 &&
					strcmp(chr, ".GB") != 0 &&
					strcmp(chr, ".GBC") != 0
				))
			)
				continue;
			this->_entries.emplace_back(Cartridge::_getOSType(s.st_mode), dir->d_name);
		}
		closedir(stream);
		std::sort(this->_entries.begin(), this->_entries.end());
		return true;
	}

	Cartridge::Cartridge()
	{
		this->_getFolderContent(".", false);
		this->_sock.setBlocking(false);
	}

	Cartridge::OSType Cartridge::_getOSType(uint16_t type)
	{
		switch (type & S_IFMT) {
		case S_IFDIR:
			return Cartridge::TYPE_DIRECTORY;
		case S_IFREG:
			return Cartridge::TYPE_FILE;
#ifdef S_IFFIFO
		case S_IFFIFO:
			return Cartridge::TYPE_FIFO;
#endif
		case S_IFCHR:
			return Cartridge::TYPE_CHARACTER_DEV;
#ifdef S_IFLNK
		case S_IFLNK:
			return Cartridge::TYPE_SYMLINK;
#endif
		case S_IFBLK:
			return Cartridge::TYPE_BLOCK_DEV;
#ifdef S_IFSOCK
		case S_IFSOCK:
			return Cartridge::TYPE_SOCKET;
#endif
		default:
			return Cartridge::TYPE_UNKNOWN;
		}
	}

	void Cartridge::sendOpcode(int opcode, const void *data, size_t datalen, bool writeLen)
	{
		size_t start = 0x200;

		for (auto op = this->_ram.read(start); op && start < 0x3FF; op = this->_ram.read(start)) {
			if (opcode == op && op == 1)
				break;
			start++;
			switch (op) {
			case 1:
				start++;
				break;
			case 2:
				start += (this->_ram.read(start) + (this->_ram.read(start) << 8)) + 2;
				break;
			case 3:
				start += strnlen(reinterpret_cast<char *>(this->_ram.getBuffer() + start), 0x400 - start) + 1;
				break;
			default:
				start--;
				memset(this->_ram.getBuffer() + start, 0, 0x400 - start);
				break;
			}
		}
		if ((start + datalen + 1 + writeLen * 2) >= 0x400) {
			if (opcode != 4)
				sendOpcode(4, nullptr, 0);
			return;
		}
		this->_ram.write(start, opcode);
		if (writeLen) {
			this->_ram.write(start + 1, datalen & 0xFF);
			this->_ram.write(start + 2, (datalen >> 8) & 0xFF);
		}
		if (datalen)
			memcpy(&this->_ram.getBuffer()[start + 1 + writeLen * 2], data, datalen);
		this->_interrupt = true;
	}

	unsigned char Cartridge::getWifiLevel()
	{
		std::ifstream stream{"/proc/net/wireless"};
		std::string line;
		int level = 0;
		size_t i = 0;
		bool space = false;

		if (!std::getline(std::getline(std::getline(stream, line), line), line))
			return 0;
		for (; i < line.size() && level < 3; i++) {
			bool newSpace = std::isspace(line[i]);

			if (space && !newSpace)
				level++;
			space = newSpace;
		}
		if (level != 3 || i >= line.size())
			return 0;
		return atoi(line.c_str() + i) + 128;
	}

	void Cartridge::update()
	{
		if (this->_type != WIFI_CUSTOM_ROM)
			return;

		bool ok = true;
		char buffer[0x200];
		size_t length;

		this->_cycle++;
		if ((this->_cycle & 0xFFFF) == 0) {
			unsigned char wifiLevel = Cartridge::getWifiLevel();

			sendOpcode(1, &wifiLevel, 1);
		}
		if (this->_sent && (this->_cycle & 0xFFF) == 0)
			while (true) {
				switch (this->_sock.receive(buffer, 0x200, length, this->_addr, this->_port)) {
				case sf::UdpSocket::Done:
					if (ok)
						sendOpcode(2, buffer, length, true);
				case sf::UdpSocket::NotReady:
					return;
				case sf::UdpSocket::Partial:
					break;
				case sf::UdpSocket::Error:
					return sendOpcode(2, "Socket error", strlen("Socket error"));
				}
				ok = false;
			}
	}
}
