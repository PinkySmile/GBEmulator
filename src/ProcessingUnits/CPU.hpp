/*
** EPITECH PROJECT, 2022
** GBEmulator
** File description:
** Created by agrellier,
*/

#ifndef GBEMULATOR_CPU_HPP
#define GBEMULATOR_CPU_HPP

#include <string>
#include <functional>
#include "APU.hpp"
#include "GPU.hpp"
#include "../Memory/ROM.hpp"


#define ROM_BANK_SIZE 0x4000
#define RAM_SIZE 0x8000
#define HRAM_SIZE 0x7F


namespace GBEmulator
{
	class CPU {
	public:
		struct Registers {
			union {
				struct {
					union {
						unsigned char f;
						struct {
							unsigned char _ : 4;
							bool fc : 1;
							bool fh : 1;
							bool fn : 1;
							bool fz : 1;
						};
					};
					unsigned char a;
				};
				unsigned short af;
			};
			union {
				struct {
					unsigned char c;
					unsigned char b;
				};
				unsigned short bc;
			};
			union {
				struct {
					unsigned char e;
					unsigned char d;
				};
				unsigned short de;
			};
			union {
				struct {
					unsigned char l;
					unsigned char h;
				};
				unsigned short hl;
			};
			unsigned short pc;
			unsigned short sp;
		};

		class InvalidOpcodeException : public std::exception {
		private:
			char _buffer[40];

		public:
			InvalidOpcodeException(unsigned short op, unsigned short address);
			const char *what() const noexcept override;
		};

		CPU(const std::string &romPath);

		unsigned char read(unsigned short address)const;
		unsigned char fetchArgument();
		unsigned short fetchArgument16();
		void write(unsigned short address, unsigned char value);
		bool executeNextInstruction();
		void dump() const;
		void dumpMemory() const;
		void dumpRegisters() const;

	private:
		static const std::vector<unsigned char> _startupCode;

		APU _apu;
		GPU _gpu;
		ROM _rom;
		bool _halted;
		Memory _ram;
		Memory _hram;
		Registers _registers;
		unsigned char _interrupt;
		unsigned long _totalCycles;
	};
}

#endif //GBEMULATOR_CPU_HPP
