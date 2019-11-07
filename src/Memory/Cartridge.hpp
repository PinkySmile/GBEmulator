/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Cartridge.hpp
*/

#ifndef GBEMULATOR_CARTRIDGE_HPP
#define GBEMULATOR_CARTRIDGE_HPP


#include <map>
#include "ROM.hpp"

//The default size of a ROM bank
#define ROM_BANK_SIZE 0x4000

//The size of a RAM bank in the cartridges
#define RAM_BANKING_SIZE 0x2000

namespace GBEmulator::Memory
{
	class Cartridge {
	private:
		class InvalidRomException : public std::exception {
		private:
			std::string _msg;

		public:
			InvalidRomException(const std::string &msg) : _msg(msg) {};
			const char *what() const noexcept override { return this->_msg.c_str(); };
		};

		class InvalidRomSizeException : public InvalidRomException {
		public:
			InvalidRomSizeException(const std::string &msg) : InvalidRomException(msg) {};
		};

		class InvalidRomRamSizeException : public InvalidRomException {
		public:
			InvalidRomRamSizeException(const std::string &msg) : InvalidRomException(msg) {};
		};

		enum CartridgeType {
			ROM_ONLY                = 0x00,
			MBC1                    = 0x01,
			MBC1_RAM                = 0x02,
			MBC1_RAM_BATTERY        = 0x03,
			MBC2                    = 0x05,
			MBC2_BATTERY            = 0x06,
			ROM_RAM                 = 0x08,
			ROM_RAM_BATTERY         = 0x09,
			MMM01                   = 0x0B,
			MMM01_RAM               = 0x0C,
			MMM01_RAM_BATTERY       = 0x0D,
			MBC3_TIMER_BATTERY      = 0x0F,
			MBC3_TIMER_RAM_BATTERY  = 0x10,
			MBC3                    = 0x11,
			MBC3_RAM                = 0x12,
			MBC3_RAM_BATTERY        = 0x13,
			MBC5                    = 0x19,
			MBC5_RAM                = 0x1A,
			MBC5_RAM_BATTERY        = 0x1B,
			MBC5_RUMBLE             = 0x1C,
			MBC5_RUMBLE_RAM         = 0x1D,
			MBC5_RUMBLE_RAM_BATTERY = 0x1E,
			POCKET_CAMERA           = 0xFC,
			BANDAI_TAMA5            = 0xFD,
			HuC3                    = 0xFE,
			HuC1_RAM_BATTERY        = 0xFF,
		};

		enum ROMSize
		{
			SIZE_32KByte  = 0x00,
			SIZE_64KByte  = 0x01,
			SIZE_128KByte = 0x02,
			SIZE_256KByte = 0x03,
			SIZE_512KByte = 0x04,
			SIZE_1MByte   = 0x05,
			SIZE_2MByte   = 0x06,
			SIZE_4MByte   = 0x07,
			SIZE_1_1MByte = 0x52,
			SIZE_1_2MByte = 0x53,
			SIZE_1_5MByte = 0x54,
		};

		static const std::map<size_t, ROMSize> _sizeBytes;

		ROM _rom;
		bool _ramEnabled = false;
		bool _ramExtended = false;
		Memory _ram{0, RAM_BANKING_SIZE};
		CartridgeType _type = ROM_ONLY;

		void _checkROM();
		static size_t _getBestSizeForFile(const std::string &path);

		void _handleHuCWrite(unsigned short address, unsigned char value);
		void _handleMBC1Write(unsigned short address, unsigned char value);
		void _handleMBC2Write(unsigned short address, unsigned char value);
		void _handleMBC3Write(unsigned short address, unsigned char value);
		void _handleMBC5Write(unsigned short address, unsigned char value);
		void _handleRumbleWrite(unsigned short address, unsigned char value);

	public:
		Cartridge() = default;
		Cartridge(const Cartridge &) = delete;
		~Cartridge() = default;
		Cartridge &operator=(const Cartridge &) = delete;

		void resetROM();
		void loadROM(const std::string &rom);
		void write(unsigned short address, unsigned char value);
		unsigned char read(unsigned short address) const;
	};
}


#endif //GBEMULATOR_CARTRIDGE_HPP
