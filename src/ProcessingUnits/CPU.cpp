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
#include "CPUInstructions.hpp"

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

	CPU::CPU(const std::string &romPath, sf::RenderWindow &window) :
		_gpu(window),
		_halted(false),
		_sleeping(false),
		_interruptRequest(0x00),
		_interruptEnabled(0x00),
		_totalCycles(0),
		_rom(romPath, ROM_BANK_SIZE),
		_ram(RAM_SIZE, RAM_SIZE),
		_hram(HRAM_SIZE, HRAM_SIZE),
		_registers{0, 0, 0, 0, 0, 0},
		_internalRomEnabled(true),
		_interruptMasterEnableFlag(true)
	{
		this->_rom.setBank(1);
	}

	unsigned char CPU::read(unsigned short address) const
	{
		switch (address) {
		case STARTUP_CODE_RANGE:
			if (this->_internalRomEnabled)
				return CPU::_startupCode.at(address);

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
			return this->_interruptRequest;

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
			this->_interruptRequest = value;
			break;

		//Read only address
		default:
			break;
		}
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
	}

	bool CPU::_checkInterrupts()
	{
		unsigned char mask = this->_interruptEnabled & this->_interruptRequest;

		for (unsigned i = 0; i < NB_INTERRUPT_BITS; i++)
			if (mask & (1U << i))
				return this->_executeInterrupt(i), true;
		return false;
	}

	void CPU::_executeInterrupt(unsigned int id)
	{
		Instructions::CALL(*this, this->_registers, INTERRUPT_CODE_OFFSET + id * INTERRUPT_CODE_SIZE);
		this->_sleeping = false;
	}

	unsigned char CPU::_readIOPort(unsigned char address) const
	{
		switch (address) {
		case INTERRUPT_REQUESTS:
			return this->_interruptRequest;

		default:
			return 0xFF;
		}
	}

	void CPU::_writeIOPort(unsigned char address, unsigned char value)
	{
		switch (address) {
		case INTERRUPT_REQUESTS:
			this->_interruptRequest = value;
			break;
		default:
			break;
		}
	}

	void CPU::_executeNextInstruction()
	{
		unsigned char opcode = this->read(this->_registers.pc++);

		try {
			this->_totalCycles = Instructions::_instructions.at(opcode)(*this, this->_registers);
		} catch (std::out_of_range &) {
			this->_halted = true;
			throw InvalidOpcodeException(opcode, this->_registers.pc - 1);
		}
	}

	void CPU::dumpRegisters() const
	{
		std::cout << std::hex << std::uppercase;
		std::cout << "af: " << std::setw(4) << std::setfill('0') << this->_registers.af << " (a: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.a) << ", f: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.f) << ")" << std::endl;
		std::cout << "bc: " << std::setw(4) << std::setfill('0') << this->_registers.bc << " (b: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.b) << ", c: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.c) << ")" << std::endl;
		std::cout << "de: " << std::setw(4) << std::setfill('0') << this->_registers.de << " (d: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.d) << ", e: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.e) << ")" << std::endl;
		std::cout << "hl: " << std::setw(4) << std::setfill('0') << this->_registers.hl << " (h: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.h) << ", l: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->_registers.l) << ")" << std::endl;
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