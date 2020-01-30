/*
** EPITECH PROJECT, 2022
** GBEmulator
** File description:
** Created by agrellier,
*/

#include <vector>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "CPU.hpp"
#include "Instructions/CPUInstructions.hpp"
#include "Instructions/Instructions.hpp"

namespace GBEmulator
{
	CPU::InvalidOpcodeException::InvalidOpcodeException(unsigned short op, unsigned short address)
	{
		if (op & 0xFF00U)
			sprintf(this->_buffer, "Invalid opcode 0x%04X at address 0x%04X", op, address);
		else
			sprintf(this->_buffer, "Invalid opcode 0x%02X at address 0x%04X", op, address);
	}

	const char *CPU::InvalidOpcodeException::what() const noexcept
	{
		return this->_buffer;
	}

	CPU::CPU(
		ISound &channelOne,
		ISound &channelTwo,
		ISound &channelThree,
		ISound &channelFour,
		Graphics::ILCD &window,
		Input::JoypadEmulator &joypad,
		Network::CableInterface &cable
	) :
		_apu(channelOne, channelTwo, channelThree, channelFour),
		_gpu(window),
		_buttonEnabled(false),
		_directionEnabled(false),
		_halted(false),
		_stopped(false),
		_ram(RAM_SIZE, RAM_SIZE),
		_hram(HRAM_SIZE, HRAM_SIZE),
		_registers{
			.af = 0,
			.bc = 0,
			.de = 0,
			.hl = 0,
			.pc = 0,
			.sp = 0
		},
		_window(window),
		_internalRomEnabled(true),
		_divRegister(0),
		_joypad(joypad),
		_interruptEnabled(0x00),
		_interruptRequest(0x00),
		_interruptMasterEnableFlag(false),
		_cable(cable)
	{
	}

	Memory::Cartridge& CPU::getCartridgeEmulator()
	{
		return this->_rom;
	}

	const Memory::Cartridge& CPU::getCartridgeEmulator() const
	{
		return this->_rom;
	}

	unsigned char CPU::read(unsigned short address) const
	{
		switch (address) {
		case STARTUP_CODE_RANGE:
			if (this->_internalRomEnabled)
				return CPU::_startupCode[address];
			__attribute__((fallthrough));

		case ROM0_RANGE:
		case ROM1_RANGE:
			return this->_rom.read(address);

		case VRAM_RANGE:
			return this->_gpu.readVRAM(address - 0x8000);

		case SRAM_RANGE:
			return this->_rom.read(address);

		case WRAM_RANGE:
			return this->_ram.read(address - WRAM_STARTING_ADDRESS);

		case ECHO_RAM_RANGE:
			return this->_ram.read(address - ECHO_RAM_STARTING_ADDRESS);

		case OAM_RANGE:
			return this->_gpu.readOAM(address - 0xFE00);

		case IO_PORT1_RANGE:
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		case APU_RANGE:
			return this->_apu.read(address - APU_STARTING_ADDRESS);

		case WPRAM_RANGE:
			return this->_apu.read(address - APU_STARTING_ADDRESS);

		case IO_PORT2_RANGE:
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		case HRAM_RANGE:
			return this->_hram.read(address - HRAM_STARTING_ADDRESS);

		case INTERRUPT_ENABLE_ADDRESS:
			return this->_interruptEnabled;

		default:
			return 0x00;
		}
	}

	unsigned char CPU::fetchArgument()
	{
		return this->read(this->_registers.pc++);
	}

	unsigned short CPU::fetchArgument16()
	{
		return this->fetchArgument() | (this->fetchArgument() << 8U);
	}

	CPU::Registers CPU::getRegisters() const
	{
		return this->_registers;
	}

	void CPU::halt()
	{
		this->_halted = true;
	}

	void CPU::stop()
	{
		this->_stopped = true;
	}

	bool CPU::isStopped() const
	{
		return this->_stopped;
	}

	void CPU::write(unsigned short address, unsigned char value)
	{
		switch (address) {
		case STARTUP_CODE_RANGE:
		case ROM0_RANGE:
		case ROM1_RANGE:
			return this->_rom.write(address, value);

		case VRAM_RANGE:
			return this->_gpu.writeVRAM(address - 0x8000, value);

		case SRAM_RANGE:
			return this->_rom.write(address, value);

		case WRAM_RANGE:
			return this->_ram.write(address - WRAM_STARTING_ADDRESS, value);

		case ECHO_RAM_RANGE:
			return this->_ram.write(address - ECHO_RAM_STARTING_ADDRESS, value);

		case IO_PORT1_RANGE:
			return this->_writeIOPort(address - IO_PORTS_STARTING_ADDRESS, value);

		case APU_RANGE:
			return this->_apu.write(address - APU_STARTING_ADDRESS, value);

		case WPRAM_RANGE:
			return this->_apu.write(address - APU_STARTING_ADDRESS, value);

		case IO_PORT2_RANGE:
			return this->_writeIOPort(address - IO_PORTS_STARTING_ADDRESS, value);

		case OAM_RANGE:
			return this->_gpu.writeOAM(address - 0xFE00, value);

		case HRAM_RANGE:
			return this->_hram.write(address - HRAM_STARTING_ADDRESS, value);

		case INTERRUPT_ENABLE_ADDRESS:
			this->_interruptEnabled = value;
			break;

		//Read only address
		default:
			break;
		}
	}

	void CPU::setInterruptMaster(bool val)
	{
		this->_interruptMasterEnableFlag = val;
	}

	bool CPU::isHalted() const
	{
		return this->_halted;
	}

	void CPU::update()
	{
		if (this->_stopped) {
			for (unsigned i = 0; i < Input::ENABLE_DEBUGGING; i++)
				if (this->_joypad.isButtonPressed(static_cast<Input::Keys>(i)))
					this->_stopped = false;
			this->_window.display();
			return;
		}

		if (this->_checkInterrupts())
			return;

		if (!this->_halted)
			this->_executeNextInstruction();
		else
			this->_updateComponents(16);
	}

	void CPU::_updateComponents(unsigned int cycles)
	{
		unsigned gpuInts = this->_gpu.update(cycles);

		this->_hardwareInterruptRequests = 0;

		this->_hardwareInterruptRequests |= gpuInts;

		if (this->_cable.triggerInterrupt())
			this->_hardwareInterruptRequests |= SERIAL_INTERRUPT;
		this->_cable.update(cycles);

		if (this->_timer.update(cycles))
			this->_interruptRequest |= TIMER_INTERRUPT;

		this->_apu.update(cycles);
	}

	bool CPU::_checkInterrupts()
	{
		unsigned char mask = this->_interruptRequest | this->_hardwareInterruptRequests;

		for (unsigned i = 0; i < NB_INTERRUPT_BITS; i++)
			if (mask & (1U << i))
				return this->_executeInterrupt(i), true;
		return false;
	}

	void CPU::_executeInterrupt(unsigned int id)
	{
		this->_halted = false;
		this->_interruptRequest &= ~(1U << id);
		this->_hardwareInterruptRequests &= ~(1U << id);

		if (!this->_interruptMasterEnableFlag || !((1U << id) & this->_interruptEnabled))
			return;

		Instructions::CALL(*this, this->_registers, INTERRUPT_CODE_OFFSET + id * INTERRUPT_CODE_SIZE);
		this->_interruptMasterEnableFlag = false;
	}

	unsigned char CPU::_generateJoypadByte() const
	{
		unsigned char dirs = (0b11110000U |
			this->_joypad.isButtonPressed(Input::JOYPAD_DOWN) << 3U |
			this->_joypad.isButtonPressed(Input::JOYPAD_UP)   << 2U |
			this->_joypad.isButtonPressed(Input::JOYPAD_LEFT) << 1U |
			this->_joypad.isButtonPressed(Input::JOYPAD_RIGHT)<< 0U
		);
		unsigned char buts = (0b11110000U |
			this->_joypad.isButtonPressed(Input::JOYPAD_START) << 3U |
			this->_joypad.isButtonPressed(Input::JOYPAD_SELECT)<< 2U |
			this->_joypad.isButtonPressed(Input::JOYPAD_B)     << 1U |
			this->_joypad.isButtonPressed(Input::JOYPAD_A)     << 0U
		);
		unsigned char common = 0b11000000U | (this->_buttonEnabled * 0b100000U) | (this->_directionEnabled * 0b010000U);

		return (
			common | (
				this->_buttonEnabled * ~dirs
			) | (
				this->_directionEnabled * ~buts
			) | (
				!this->_directionEnabled * !this->_buttonEnabled * 0b1111
			)
		);
	}

	unsigned char CPU::_readIOPort(unsigned char address) const
	{
		switch (address) {
		case SERIAL_DATA:
			return this->_cable.byte;

		case SERIAL_TRANSFER_CONTROL:
			return this->_cable.getControlByte();

		case TIMER_COUNTER:
			return this->_timer.getCounter();

		case LCD_CONTROL:
			return this->_gpu.getControlByte();

		case LCDC_STAT:
			return this->_gpu.getStatByte();

		case LCDC_Y_COORD:
			return this->_gpu.getCurrentLine();

		case LCD_LYC:
			return this->_gpu.getLycByte();

		case LCD_BG_COLOR:
			return this->_gpu.getBGPalette();

		case OBJECT_PALETTE_0:
			return this->_gpu.getObjectPalette0();

		case OBJECT_PALETTE_1:
			return this->_gpu.getObjectPalette1();

		case LCD_SCROLL_X:
			return this->_gpu.getXScroll();

		case LCD_SCROLL_Y:
			return this->_gpu.getYScroll();

		case LCD_WINDOW_X:
			return this->_gpu.getWindowX();

		case LCD_WINDOW_Y:
			return this->_gpu.getWindowY();

		case TIMER_MODULO:
			return this->_timer.modulo;

		case TIMER_CONTROL:
			return this->_timer.getControlByte();

		case JOYPAD_REGISTER:
			return this->_generateJoypadByte();

		case INTERRUPT_REQUESTS:
			return this->_interruptRequest | 0b11100000U;

		case DIVIDER_REGISTER:
			return this->_divRegister >> 8U;

		default:
			return 0xFF;
		}
	}

	void CPU::_writeIOPort(unsigned char address, unsigned char value)
	{
		switch (address) {
		case SERIAL_DATA:
			this->_cable.byte = value;
			break;

		case SERIAL_TRANSFER_CONTROL:
			return this->_cable.setControlByte(value);

		case TIMER_COUNTER:
			return this->_timer.setCounter(value);

		case TIMER_MODULO:
			this->_timer.modulo = value;
			break;

		case INTERNAL_ROM_ENABLE:
			if (value != 1)
				this->_halted = true;
			else
				this->_internalRomEnabled = false;
			break;

		case TIMER_CONTROL:
			return this->_timer.setControlByte(value);

		case LCD_CONTROL:
			return this->_gpu.setControlByte(value);

		case LCDC_STAT:
			return this->_gpu.setStatByte(value);

		//TODO: Add inaccessibility of everything but HRAM during DMA and copy only when OAM is accessible
		case OAM_DMA:
			if (value <= 0xF1) {
				for (int i = 0; i < 40; i++) {
					this->_gpu.writeOAM(i * 4, this->read(value * 0x100 + i * 4));
					this->_gpu.writeOAM(i * 4 + 1, this->read(value * 0x100 + i * 4 + 1));
					this->_gpu.writeOAM(i * 4 + 2, this->read(value * 0x100 + i * 4 + 2));
					this->_gpu.writeOAM(i * 4 + 3, this->read(value * 0x100 + i * 4 + 3));
				}
			}
			break;

		case LCD_BG_COLOR:
			return this->_gpu.setBGPalette(value);

		case OBJECT_PALETTE_0:
			return this->_gpu.setObjectPalette0(value);

		case OBJECT_PALETTE_1:
			return this->_gpu.setObjectPalette1(value);

		case LCD_SCROLL_X:
			return this->_gpu.setXScroll(value);

		case LCD_SCROLL_Y:
			return this->_gpu.setYScroll(value);

		case LCD_LYC:
			return this->_gpu.setLycByte(value);

		case LCD_WINDOW_X:
			return this->_gpu.setWindowX(value);

		case LCD_WINDOW_Y:
			return this->_gpu.setWindowY(value);

		case JOYPAD_REGISTER:
			this->_directionEnabled = (value & 0b10000U) != 0;
			this->_buttonEnabled =    (value & 0b100000U)!= 0;
			break;

		case INTERRUPT_REQUESTS:
			this->_interruptRequest = value;
			break;

		case DIVIDER_REGISTER:
			this->_divRegister = 0;
			break;

		default:
			break;
		}
	}

	void CPU::_executeNextInstruction()
	{
		unsigned char opcode = this->read(this->_registers.pc++);

		unsigned cycles = Instructions::executeInstruction(opcode, *this, this->_registers);

		this->_registers._ = 0;
		this->_divRegister += cycles;
		this->_updateComponents(cycles);
	}

	void CPU::dumpRegisters() const
	{
		std::cout << std::hex << std::uppercase;
		std::cout << "af: " << std::setw(4) << std::setfill('0') << this->_registers.af;
		std::cout << " (a: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.a);
		std::cout << ", f: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.f) << ")" << std::endl;

		std::cout << "bc: " << std::setw(4) << std::setfill('0') << this->_registers.bc;
		std::cout << " (b: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.b);
		std::cout << ", c: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.c) << ")" << std::endl;

		std::cout << "de: " << std::setw(4) << std::setfill('0') << this->_registers.de;
		std::cout << " (d: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.d);
		std::cout << ", e: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.e) << ")" << std::endl;

		std::cout << "hl: " << std::setw(4) << std::setfill('0') << this->_registers.hl;
		std::cout << " (h: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.h);
		std::cout << ", l: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.l) << ")" << std::endl;

		std::cout << "sp: " << std::setw(4) << std::setfill('0') << this->_registers.sp << std::endl;
		std::cout << "pc: " << std::setw(4) << std::setfill('0') << this->_registers.pc << std::endl;
		std::cout << "z: " << (this->_registers.fz ? "set" : "unset") << std::endl;
		std::cout << "c: " << (this->_registers.fc ? "set" : "unset") << std::endl;
		std::cout << "h: " << (this->_registers.fh ? "set" : "unset") << std::endl;
		std::cout << "n: " << (this->_registers.fn ? "set" : "unset") << std::endl;

		std::cout << "lcdc: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->read(0xFF00 + LCD_CONTROL)) << std::endl;
		std::cout << "stat: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->read(0xFF00 + LCDC_STAT)) << std::endl;
		std::cout << "ly: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->read(0xFF00 + LCDC_Y_COORD)) << std::endl;
		std::cout << "ie: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->read(INTERRUPT_ENABLE_ADDRESS)) << std::endl;
		std::cout << "if: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->read(0xFF00 + INTERRUPT_REQUESTS)) << std::endl;
		std::cout << "rom: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_rom.getRomBank()) << std::endl;

		if (this->_halted)
			std::cout << "Waiting for interrupt..." << std::endl;
		std::cout << "Interrupts " << (this->_interruptMasterEnableFlag ? "enabled" : "disabled") << std::endl;
		std::cout << "Next instruction: " << Instructions::_instructionsString[this->read(this->_registers.pc)](*this, this->_registers.pc + 1);
		std::cout << " (" << static_cast<int>(this->read(this->_registers.pc)) << ")" << std::endl;
	}

	void CPU::dumpMemory() const
	{
		for (unsigned int i = 0; i < 0x10000; i += 0x10) {
			std::cout << std::setw(4) << std::setfill('0') << i << ":  ";
			for (unsigned j = 0; j < 0x10 && j + i < 0x10000; j++)
				std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(this->read(j + i)) << " ";
			for (int j = 0; j < static_cast<int>(i - 0x10000 + 0x10); j++)
				std::cout << "   ";
			std::cout << " ";
			for (unsigned j = 0; j < 0x10 && j + i < 0x10000; j++)
				std::cout << static_cast<char>(std::isprint(this->read(j + i)) ? this->read(j + i) : '.');
			for (int j = 0; j < static_cast<int>(i - 0x10000 + 0x10); j++)
				std::cout << " ";
			std::cout << std::endl;
		}
	}

	void CPU::dump() const
	{
		this->dumpMemory();
		this->dumpRegisters();
	}

	unsigned short CPU::getDecPc() noexcept
	{
		this->_registers.pc--;
		return this->_registers.pc;
	}
}
