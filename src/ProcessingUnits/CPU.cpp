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
#include "CPU.hpp"
#include "Instructions/CPUInstructions.hpp"

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

	CPU::CPU(const std::string &romPath, Graphics::ILCD &window, Input::JoypadEmulator &joypad, Network::CableInterface &cable) :
		_gpu(window),
		_rom(romPath, ROM_BANK_SIZE),
		_buttonEnabled(false),
		_directionEnabled(false),
		_halted(false),
		_sleeping(false),
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
		_internalRomEnabled(true),
		_divRegister(0),
		_joypad(joypad),
		_interruptEnabled(0x00),
		_interruptRequest(0x00),
		_interruptMasterEnableFlag(false),
		_cable(cable)
	{
		this->_rom.setBank(1);
	}

	unsigned char CPU::read(unsigned short address) const
	{
		switch (address) {
		case STARTUP_CODE_RANGE:
			if (this->_internalRomEnabled)
				return CPU::_startupCode[address];
			__attribute__((fallthrough));

		case ROM0_RANGE:
			return this->_rom.rawRead(address);

		case ROM1_RANGE:
			return this->_rom.read(address - ROM1_STARTING_ADDRESS);

		case VRAM_RANGE:
			return this->_gpu.readVRAM(address - 0x8000);

		case SRAM_RANGE:
			return 0xFF;

		case WRAM_RANGE:
			return this->_ram.read(address - WRAM_STARTING_ADDRESS);

		case ECHO_RAM_RANGE:
			return this->_ram.read(address - ECHO_RAM_STARTING_ADDRESS);

		case OAM_RANGE:
			return this->_gpu.readOAM(address - 0xFE00);

		case IO_PORT1_RANGE:
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		case APU_RANGE:
			return 0xFF;

		case WPRAM_RANGE:
			return 0xFF;

		case IO_PORT2_RANGE:
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		case HRAM_RANGE:
			return this->_hram.read(address - HRAM_STARTING_ADDRESS);

		case INTERRUPT_ENABLE_ADDRESS:
			return this->_interruptEnabled;

		default:
			return 0xFF;
		}
	}

	unsigned char CPU::fetchArgument()
	{
		unsigned char r = this->read(this->_registers.pc);
		this->_registers.pc++;
		return r;
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
		this->_sleeping = true;
	}

	void CPU::write(unsigned short address, unsigned char value)
	{
		switch (address) {
		case VRAM_RANGE:
			return this->_gpu.writeVRAM(address - 0x8000, value);

		case SRAM_RANGE:
			break;

		case WRAM_RANGE:
			return this->_ram.write(address - WRAM_STARTING_ADDRESS, value);

		case ECHO_RAM_RANGE:
			return this->_ram.write(address - ECHO_RAM_STARTING_ADDRESS, value);

		case IO_PORT1_RANGE:
			return this->_writeIOPort(address - IO_PORTS_STARTING_ADDRESS, value);

		case APU_RANGE:
			return;

		case WPRAM_RANGE:
			return;

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
		if (this->_halted)
			return;

		if (this->_interruptMasterEnableFlag && this->_checkInterrupts())
			return;

		if (!this->_sleeping)
			this->_executeNextInstruction();
		else
			this->_updateComponents(16);
	}

	void CPU::_updateComponents(unsigned int cycles)
	{
		this->_interruptRequest |= this->_gpu.update(cycles);
		if (this->_cable.isTransfering())
			this->_interruptRequest |= SERIAL_INTERRUPT;
		this->_cable.transfer(cycles);
		if (this->_timer.update(cycles))
			this->_interruptRequest |= TIMER_INTERRUPT;
	}

	bool CPU::_checkInterrupts()
	{
		unsigned char mask = this->_interruptRequest & this->_interruptEnabled;

		for (unsigned i = 0; i < NB_INTERRUPT_BITS; i++)
			if (mask & (1U << i))
				return this->_executeInterrupt(i), true;
		return false;
	}

	void CPU::_executeInterrupt(unsigned int id)
	{
		std::cout << "Execute interrupt "<< id << std::endl;
		Instructions::CALL(*this, this->_registers, INTERRUPT_CODE_OFFSET + id * INTERRUPT_CODE_SIZE);
		this->_interruptRequest &= ~(1U << id);
		this->_interruptMasterEnableFlag = false;
		this->_sleeping = false;
	}

	unsigned char CPU::_generateJoypadByte() const
	{
		return (
			(this->_buttonEnabled << 5U) |
			(this->_directionEnabled << 4U) |
			((
				(this->_joypad.isButtonPressed(Input::JOYPAD_DOWN) && this->_directionEnabled) ||
				(this->_joypad.isButtonPressed(Input::JOYPAD_START) && this->_buttonEnabled)
			) << 3U) |
			((
				(this->_joypad.isButtonPressed(Input::JOYPAD_UP) && this->_directionEnabled) ||
				(this->_joypad.isButtonPressed(Input::JOYPAD_SELECT) && this->_buttonEnabled)
			) << 2U) |
			((
				(this->_joypad.isButtonPressed(Input::JOYPAD_LEFT) && this->_directionEnabled) ||
				(this->_joypad.isButtonPressed(Input::JOYPAD_B) && this->_buttonEnabled)
			) << 1U) |
			((
				(this->_joypad.isButtonPressed(Input::JOYPAD_RIGHT) && this->_directionEnabled) ||
				(this->_joypad.isButtonPressed(Input::JOYPAD_A) && this->_buttonEnabled)
			) << 0U)
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

		case LCDC_Y_COORD:
			return this->_gpu.getCurrentLine();

		case LCD_BG_COLOR:
			return this->_gpu.getBGPalette();

		case LCD_SCROLL_X:
			return this->_gpu.getXScroll();

		case LCD_SCROLL_Y:
			return this->_gpu.getYScroll();

		case TIMER_MODULO:
			return this->_timer.modulo;

		case TIMER_CONTROL:
			return this->_timer.getControlByte();

		case JOYPAD_REGISTER:
			return this->_generateJoypadByte();

		case INTERRUPT_REQUESTS:
			return this->_interruptRequest;

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
			this->_internalRomEnabled = false;
			break;

		case TIMER_CONTROL:
			return this->_timer.setControlByte(value);

		case LCD_CONTROL:
			return this->_gpu.setControlByte(value);

		case LCD_BG_COLOR:
			return this->_gpu.setBGPalette(value);

		case LCD_SCROLL_X:
			return this->_gpu.setXScroll(value);

		case LCD_SCROLL_Y:
			return this->_gpu.setYScroll(value);

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

		try {
			unsigned cycles = Instructions::_instructions[opcode](*this, this->_registers);

			this->_divRegister += cycles;
			this->_updateComponents(cycles);
		} catch (std::bad_function_call &) {
			this->_halted = true;
			throw InvalidOpcodeException(opcode, this->_registers.pc - 1);
		}
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
}