/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.hpp
*/

#ifndef GBEMULATOR_ROM_HPP
#define GBEMULATOR_ROM_HPP


#include <map>
#include <string>
#include "Memory.hpp"

namespace GBEmulator
{
	class InvalidRomException : public std::exception {
	private:
		std::string _msg;

	public:
		InvalidRomException(const std::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	class ROM : public Memory {
	private:
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
			MBC4                    = 0x15,
			MBC4_RAM                = 0x16,
			MBC4_RAM_BATTERY        = 0x17,
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

		void _checkROM();

	public:
		ROM(const std::string &path, unsigned short bankSize);
	};
}


#endif //GBEMULATOR_ROM_HPP
