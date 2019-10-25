/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP


#include "../Memory/Memory.hpp"

namespace GBEmulator
{
	enum regist {
		FF10 = 0x0,
		FF11 = 0x1,
		FF12 = 0x2,
		FF13 = 0x3,
		FF14 = 0x4,
		FF16 = 0x6,
		FF17 = 0x7,
		FF18 = 0x8,
		FF19 = 0x9,
		FF1A = 0xA,
		FF1B = 0xB,
		FF1C = 0xC,
		FF1D = 0xD,
		FF1E = 0xE,
		FF20 = 0x10,
		FF21 = 0x11,
		FF22 = 0x12,
		FF23 = 0x13,
		FF24 = 0x14,
		FF25 = 0x15,
		FF26 = 0x16,
		FF30 = 0x20
	};
	class APU {
	public:
		APU();
		~APU();
		APU(const APU &) = delete;
		APU &operator=(const APU &) = delete;

		void write(unsigned short, unsigned char);
		unsigned char read(unsigned short) const;

	private:
		Memory _memory;
	};
}


#endif //GBEMULATOR_APU_HPP
