/*
** EPITECH PROJECT, 2022
** GBEmulator
** File description:
** Created by agrellier,
*/

#ifndef GBEMULATOR_CPU_HPP
#define GBEMULATOR_CPU_HPP

#include <string>
#include "APU.hpp"
#include "GPU.hpp"
#include "../Memory/ROM.hpp"

#define ROM_BANK_SIZE 0x4000
#define RAM_SIZE 0x8000
#define HRAM_SIZE 0x7F

namespace GBEmulator
{
	class CPU {
	private:
		struct Registers {
			union {
				struct {
					unsigned char a;
					unsigned char f;
				};
				unsigned short af;
			};
			union {
				struct {
					unsigned char b;
					unsigned char c;
				};
				unsigned short bc;
			};
			union {
				struct {
					unsigned char d;
					unsigned char e;
				};
				unsigned short de;
			};
			union {
				struct {
					unsigned char h;
					unsigned char l;
				};
				unsigned short hl;
			};
			unsigned short pc;
			unsigned short sp;
		};

		static const std::vector<unsigned char> _startupCode;

		unsigned char _interrupt;
		bool _halted;
		APU _apu;
		GPU _gpu;
		ROM _rom;
		Memory _ram;
		Memory _hram;
		Registers _registers;

	public:
		CPU(const std::string &romPath);

		unsigned char read(unsigned short address);
		void write(unsigned short address, unsigned char value);
		bool executeNextInstruction();
	};
}

#endif //GBEMULATOR_CPU_HPP
