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
#include "../Memory/Cartridge.hpp"
#include "../Joypad/JoypadEmulator.hpp"
#include "../Network/CableInterface.hpp"
#include "../Timing/Timer.hpp"

//The total size of the working RAM
#define RAM_SIZE 0x8000

//The total size of te high RAM
#define HRAM_SIZE 0x7F

//The number of interrupts
#define NB_INTERRUPT_BITS 5

//The size of the interrupt code
#define INTERRUPT_CODE_SIZE 0x8

//The address of the first interrupt
#define INTERRUPT_CODE_OFFSET 0x40

//The startup code
#define STARTUP_CODE_RANGE 0x0000 ... 0x00FF

//The first bank of the ROM (ROM0)
#define ROM0_RANGE 0x0100 ... 0x3FFF

//The switchable ROM bank (ROM1)
#define ROM1_RANGE 0x4000 ... 0x7FFF
#define ROM1_STARTING_ADDRESS 0x4000

//Video RAM
#define VRAM_RANGE 0x8000 ... 0x9FFF

//Cartridge RAM
#define SRAM_RANGE 0xA000 ... 0xBFFF

//Working RAM
#define WRAM_RANGE 0xC000 ... 0xDFFF
#define WRAM_STARTING_ADDRESS 0xC000

//Echo RAM (Echoing the WRAM)
#define ECHO_RAM_RANGE 0xE000 ... 0xFDFF
#define ECHO_RAM_STARTING_ADDRESS 0xE000

//Object attributes matrix
#define OAM_RANGE 0xFE00 ... 0xFE9F

//The first range of I/O ports
#define IO_PORT1_RANGE 0xFF00 ... 0xFF0F
#define IO_PORTS_STARTING_ADDRESS 0xFF00

//The APU
#define APU_RANGE 0xFF10 ... 0xFF2F

//The wave pattern RAM
#define WPRAM_RANGE 0xFF30 ... 0xFF3F

//The second range of I/O ports
#define IO_PORT2_RANGE 0xFF40 ... 0xFF7F

//High RAM
#define HRAM_RANGE 0xFF80 ... 0xFFFE
#define HRAM_STARTING_ADDRESS 0xFF80

//Interrupt enable
#define INTERRUPT_ENABLE_ADDRESS 0xFFFF

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}

	class CPU {
	public:
		enum InterruptsKind {
			VBLANK_INTERRUPT =   1U << 0U,
			LCD_STAT_INTERRUPT = 1U << 1U,
			TIMER_INTERRUPT =    1U << 2U,
			SERIAL_INTERRUPT =   1U << 3U,
			JOYPAD_INTERRUPT =   1U << 4U,
		};

		enum IOPorts {
			JOYPAD_REGISTER         = 0x00,
			SERIAL_DATA             = 0x01,
			SERIAL_TRANSFER_CONTROL = 0x02,
			DIVIDER_REGISTER        = 0x04,
			TIMER_COUNTER           = 0x05,
			TIMER_MODULO            = 0x06,
			TIMER_CONTROL           = 0x07,
			INTERRUPT_REQUESTS      = 0x0F,
			LCD_CONTROL             = 0x40,
			LCDC_STAT				= 0x41,
			LCD_SCROLL_Y            = 0x42,
			LCD_SCROLL_X            = 0x43,
			LCDC_Y_COORD            = 0x44,
			LCD_LYC					= 0x45,
			LCD_BG_COLOR            = 0x47,
			OBJECT_PALETTE_0		= 0x48,
			OBJECT_PALETTE_1		= 0x49,
			LCD_WINDOW_Y			= 0x4A,
			LCD_WINDOW_X			= 0x4B,
			INTERNAL_ROM_ENABLE     = 0x50,
		};

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

		CPU(Graphics::ILCD &window, Input::JoypadEmulator &joypad, Network::CableInterface &cable);

		CPU() = delete;
		CPU(const CPU &) = delete;
		~CPU() = default;
		CPU &operator=(const CPU &) = delete;

		void halt();
		void stop();
		unsigned char read(unsigned short address) const;
		unsigned char fetchArgument();
		unsigned short fetchArgument16();
		void setInterruptMaster(bool val);
		void write(unsigned short address, unsigned char value);
		void dump() const;
		bool isHalted() const;
		bool isStopped() const;
		void dumpMemory() const;
		void dumpRegisters() const;
		Registers getRegisters() const;
		Memory::Cartridge &getCartridgeEmulator();
		const Memory::Cartridge &getCartridgeEmulator() const;
		void update();

	private:
		friend Debugger::Debugger;
		static const std::vector<unsigned char> _startupCode;

		APU _apu;
		GPU _gpu;
		bool _buttonEnabled;
		bool _directionEnabled;
		bool _halted;
		bool _stopped;
		Memory::Memory _ram;
		Memory::Memory _hram;
		Registers _registers;
		Timing::Timer _timer;
		Graphics::ILCD &_window;
		Memory::Cartridge _rom;
		bool _internalRomEnabled;
		unsigned short _divRegister;
		Input::JoypadEmulator &_joypad;
		unsigned char _interruptEnabled;
		unsigned char _interruptRequest;
		bool _interruptMasterEnableFlag;
		Network::CableInterface &_cable;

		void _updateComponents(unsigned int cycles);
		bool _checkInterrupts();
		void _executeNextInstruction();
		void _executeInterrupt(unsigned int id);
		unsigned char _generateJoypadByte() const;
		unsigned char _readIOPort(unsigned char address) const;
		void _writeIOPort(unsigned char address, unsigned char value);
	};
}

#endif //GBEMULATOR_CPU_HPP
