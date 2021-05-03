/*
** EPITECH PROJECT, 2019
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
		Network::CableInterface &cable,
		bool errorReport
	) :
		_apu(channelOne, channelTwo, channelThree, channelFour),
		_gpu(window),
		_buttonEnabled(false),
		_directionEnabled(false),
		_halted(false),
		_stopped(false),
		_errorReport(errorReport),
		_ram(RAM_SIZE, RAM_BANK_SIZE),
		_hram(HRAM_SIZE, HRAM_SIZE),
		_registers{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		_window(window),
		_internalRomEnabled(true),
		_divRegister(0),
		_joypad(joypad),
		_interruptEnabled(0x00),
		_interruptRequest(0x00),
		_interruptMasterEnableFlag(false),
		_cable(cable)
	{
		this->_ram.setBank(1);
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
		auto it = this->_frozenAddresses.find(address);

		if (it != this->_frozenAddresses.end())
			return it->second;

#if defined(__GNUG__) || defined(DIRTY_MSVC_SWITCH)
		switch (address) {
		case STARTUP_CODE_RANGE:
			if (this->_internalRomEnabled && this->_rom.isGameBoyOnly())
				return CPU::_startupCode[address];
#ifdef __GNUG__
			__attribute__((fallthrough));
#endif
		case GBC_STARTUP_CODE_RANGE:
			if (address > 0x101 && address < 0x200)
				return this->_rom.read(address);
			if (this->_internalRomEnabled && !this->_rom.isGameBoyOnly())
				return CPU::_gbcStartupCode[address];
#ifdef __GNUG__
			__attribute__((fallthrough));
#endif
		case ROM0_RANGE:
		case ROM1_RANGE:
			return this->_rom.read(address);

		case VRAM_RANGE:
			return this->_gpu.readVRAM(address - VRAM_STARTING_ADDRESS);

		case SRAM_RANGE:
			return this->_rom.read(address);

		case WRAM_RANGE:
			return this->_ram.rawRead(address - WRAM_STARTING_ADDRESS);

		case WRAMBX_RANGE:
			return this->_ram.read(address - WRAMBX_STARTING_ADDRESS);

		case ECHO_RAM_RANGE:
			return this->read(address - ECHO_RAM_STARTING_ADDRESS + WRAM_STARTING_ADDRESS);

		case OAM_RANGE:
			return this->_gpu.readOAM(address - OAM_STARTING_ADDRESS);

		case IO_PORT1_RANGE:
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		case APU_RANGE:
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
#else
		if (address < STARTUP_CODE_ENDING_ADDRESS)
			if (this->_internalRomEnabled)
				return CPU::_startupCode[address];

		if (address < GBC_STARTUP_CODE_ENDING_ADDRESS) {
			if (address > 0x101 && address < 0x200)
				return this->_rom.read(address);
			if (this->_internalRomEnabled && !this->_rom.isGameBoyOnly())
				return CPU::_gbcStartupCode[address];
		}

		if (address < ROM0_ENDING_ADDRESS)
			return this->_rom.read(address);

		if (address < ROM1_ENDING_ADDRESS)
			return this->_rom.read(address);

		if (address < VRAM_ENDING_ADDRESS)
			return this->_gpu.readVRAM(address - VRAM_STARTING_ADDRESS);

		if (address < SRAM_ENDING_ADDRESS)
			return this->_rom.read(address);

		if (address < WRAM_ENDING_ADDRESS)
			return this->_ram.rawRead(address - WRAM_STARTING_ADDRESS);

		if (address < WRAMBX_ENDING_ADDRESS)
			return this->_ram.read(address - WRAMBX_STARTING_ADDRESS);

		if (address < ECHO_RAM_ENDING_ADDRESS)
			return this->_ram.read(address - ECHO_RAM_STARTING_ADDRESS);

		if (address < OAM_ENDING_ADDRESS)
			return this->_gpu.readOAM(address - OAM_STARTING_ADDRESS);

		if (address >= IO_PORTS_STARTING_ADDRESS && address < IO_PORTS_ENDING_ADDRESS)
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		if (address < APU_ENDING_ADDRESS)
			return this->_apu.read(address - APU_STARTING_ADDRESS);

		if (address < WPRAM_ENDING_ADDRESS)
			return this->_apu.read(address - APU_STARTING_ADDRESS);

		if (address < HRAM_STARTING_ADDRESS)
			return this->_readIOPort(address - IO_PORTS_STARTING_ADDRESS);

		if (address < HRAM_ENDING_ADDRESS)
			return this->_hram.read(address - HRAM_STARTING_ADDRESS);

		if (address == INTERRUPT_ENABLE_ADDRESS)
			return this->_interruptEnabled;

		return 0x00;
#endif
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
		this->_stopped = !this->_speedSwitch;
		this->_speedSwitch = false;
		this->_isDoubleSpeed = !this->_isDoubleSpeed;
		//TODO: Implement double speed mode
	}

	bool CPU::isStopped() const
	{
		return this->_stopped;
	}

	void CPU::write(unsigned short address, unsigned char value)
	{
		auto it = this->_frozenAddresses.find(address);

		if (it != this->_frozenAddresses.end())
			return;

#if defined(__GNUG__) || defined(DIRTY_MSVC_SWITCH)
		switch (address) {
		case STARTUP_CODE_RANGE:
		case GBC_STARTUP_CODE_RANGE:
		case ROM0_RANGE:
		case ROM1_RANGE:
			return this->_rom.write(address, value);

		case VRAM_RANGE:
			return this->_gpu.writeVRAM(address - 0x8000, value);

		case SRAM_RANGE:
			return this->_rom.write(address, value);

		case WRAM_RANGE:
			return this->_ram.rawWrite(address - WRAM_STARTING_ADDRESS, value);

		case WRAMBX_RANGE:
			return this->_ram.write(address - WRAMBX_STARTING_ADDRESS, value);

		case ECHO_RAM_RANGE:
			return this->write(address - ECHO_RAM_STARTING_ADDRESS + WRAM_STARTING_ADDRESS, value);

		case IO_PORT1_RANGE:
			return this->_writeIOPort(address - IO_PORTS_STARTING_ADDRESS, value);

		case APU_RANGE:
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
#else
		if (address < ROM1_ENDING_ADDRESS)
			return this->_rom.write(address, value);

		if (address < VRAM_ENDING_ADDRESS)
			return this->_gpu.writeVRAM(address - 0x8000, value);

		if (address < SRAM_ENDING_ADDRESS)
			return this->_rom.write(address, value);

		if (address < WRAM_ENDING_ADDRESS)
			return this->_ram.rawWrite(address - WRAM_STARTING_ADDRESS, value);

		if (address < WRAMBX_ENDING_ADDRESS)
			return this->_ram.write(address - WRAMBX_STARTING_ADDRESS, value);

		if (address < ECHO_RAM_ENDING_ADDRESS)
			return this->_ram.write(address - ECHO_RAM_STARTING_ADDRESS, value);

		if (address < OAM_ENDING_ADDRESS)
			return this->_gpu.writeOAM(address - 0xFE00, value);

		if (address >= IO_PORTS_STARTING_ADDRESS && address < IO_PORTS_ENDING_ADDRESS)
			return this->_writeIOPort(address - IO_PORTS_STARTING_ADDRESS, value);

		if (address < WPRAM_ENDING_ADDRESS)
			return this->_apu.write(address - APU_STARTING_ADDRESS, value);

		if (address < HRAM_STARTING_ADDRESS)
			return this->_writeIOPort(address - IO_PORTS_STARTING_ADDRESS, value);

		if (address < HRAM_ENDING_ADDRESS)
			return this->_hram.write(address - HRAM_STARTING_ADDRESS, value);

		if (address == INTERRUPT_ENABLE_ADDRESS)
			this->_interruptEnabled = value;
#endif
	}

	void CPU::setInterruptMaster(bool val)
	{
		this->_interruptMasterEnableFlag = val;
	}

	bool CPU::isHalted() const
	{
		return this->_halted;
	}

	int CPU::_executeNextAction()
	{
		if (this->_stopped) {
			for (unsigned i = 0; i < Input::ENABLE_DEBUGGING; i++)
				if (this->_joypad.isButtonPressed(static_cast<Input::Keys>(i)))
					this->_stopped = false;
			this->_window.display();
			return 0;
		}


		int cycles = 0;

		if (!this->_halted)
			cycles = this->_executeNextInstruction();
		else
			cycles = 16;

		this->_checkInterrupts();
		return cycles;
	}

	int CPU::update(unsigned number)
	{
		int total = 0;

		if (this->_joypad.isButtonPressed(Input::RESET)) {
			this->init();
			return -1;
		}
		while (true) {
			if (!this->_maxSpeed) {
				this->_newTime = this->_clock.getElapsedTime().asSeconds();
				if (this->_newTime < this->_oldTime)
					break;
			}

			if (!number)
				break;

			number--;

			while (!this->_maxSpeed && this->_newTime > 20) {
				this->_clock.restart();
				this->_newTime -= 20;
				this->_oldTime -= 20;
			}

			int cycles = this->_executeNextAction();

			total += cycles;
			if (cycles) {
				this->_divRegister += cycles;
				this->_updateComponents(cycles / (this->_isDoubleSpeed + 1));
			}

			if (!this->_maxSpeed && this->_newTime - this->_oldTime > 0.1) {
				this->_oldTime = this->_newTime;
				break;
			}
		}
		return total;
	}

	void CPU::setSpeed(float speed)
	{
		this->_speed = speed;
	}

	void CPU::_updateComponents(unsigned int cycles)
	{
		unsigned gpuInts = this->_gpu.update(*this, cycles);

		this->_oldTime += cycles * 1. / GB_CPU_FREQUENCY / this->_speed;
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
			if ((mask & (1U << i)) && this->_executeInterrupt(i))
				return true;
		return false;
	}

	bool CPU::_executeInterrupt(unsigned int id)
	{
		if (!((1U << id) & this->_interruptEnabled))
			return false;

		this->_halted = false;

		if (!this->_interruptMasterEnableFlag)
			return false;

		this->_interruptRequest &= ~(1U << id);
		Instructions::CALL(*this, this->_registers, INTERRUPT_CODE_OFFSET + id * INTERRUPT_CODE_SIZE);
		this->_interruptMasterEnableFlag = false;
		return true;
	}

	unsigned char CPU::_generateJoypadByte() const
	{
		unsigned byte = this->_joypadCache | 0x0FU;

		if (this->_buttonEnabled)
			byte &= (
				0b11110000U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_START) << 3U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_SELECT)<< 2U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_B)     << 1U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_A)     << 0U
			);

		if (this->_directionEnabled)
			byte &= (
				0b11110000U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_DOWN) << 3U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_UP)   << 2U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_LEFT) << 1U |
				!this->_joypad.isButtonPressed(Input::JOYPAD_RIGHT)<< 0U
			);

		return byte;
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

		case BGPI:
			return this->_bgpi | (this->_autoIncrementBgpi << 7U);

		case BGPD:
			return this->_gpu.readBGPD(this->_bgpi);

		case OBPI:
			return this->_obpi | (this->_autoIncrementObpi << 7U);

		case OBPD:
			return this->_gpu.readOBPD(this->_bgpi);

		case TIMER_CONTROL:
			return this->_timer.getControlByte();

		case JOYPAD_REGISTER:
			return this->_generateJoypadByte();

		case INTERRUPT_REQUESTS:
			return this->_interruptRequest | this->_hardwareInterruptRequests | 0b11100000U;

		case DIVIDER_REGISTER:
			return this->_divRegister >> 8U;

		case SVBK:
			return this->_WRAMBank;

		case KEY1:
			return (0b01111110U | this->_speedSwitch) | (this->_isDoubleSpeed << 7U);

		case VBK:
			return this->_gpu.getVBK();

		case HDMA1:
			return this->_HDMASrc >> 8U;

		case HDMA2:
			return this->_HDMASrc;

		case HDMA3:
			return this->_HDMADest >> 8U;

		case HDMA4:
			return this->_HDMADest;

		case HDMA5:
			return (this->_gpu.getTransferLength() / 16 - 1) | (!this->_gpu.isTransfering() << 7U);

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
			if (!(value & 1) && this->_errorReport) {
				this->_halted = true;
				this->_interruptEnabled = 0;
			} else
				this->_internalRomEnabled = false;
			break;

		case TIMER_CONTROL:
			return this->_timer.setControlByte(value);

		case LCD_CONTROL:
			return this->_gpu.setControlByte(value);

		case LCDC_STAT:
			return this->_gpu.setStatByte(value);

		case BGPI:
			this->_bgpi = value & 0x3FU;
			this->_autoIncrementBgpi = value >> 7U;
			break;

		case BGPD:
			this->_gpu.writeBGPD(this->_bgpi, value);
			this->_bgpi += this->_autoIncrementBgpi;
			return;

		case OBPI:
			this->_obpi = value & 0x3FU;
			this->_autoIncrementObpi = value >> 7U;
			break;

		case OBPD:
			this->_gpu.writeOBPD(this->_obpi, value);
			this->_obpi += this->_autoIncrementObpi;
			return;

		//TODO: Add inaccessibility of everything but HRAM during DMA
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
			this->_directionEnabled = (value & 0b010000U) == 0;
			this->_buttonEnabled =    (value & 0b100000U) == 0;
			this->_joypadCache &= 0xC0U;
			this->_joypadCache |= value;
			break;

		case INTERRUPT_REQUESTS:
			this->_interruptRequest = value;
			break;

		case DIVIDER_REGISTER:
			this->_divRegister = 0;
			break;

		case SVBK:
			this->_WRAMBank = value & 7U;
			this->_WRAMBank += this->_WRAMBank == 0;
			this->_ram.setBank(this->_WRAMBank);
			break;

		case KEY1:
			this->_speedSwitch = value & 0b00000001;
			break;

		case VBK:
			this->_gpu.setVBK(value & 0b00000001);
			break;

		case HDMA1:
			this->_HDMASrc = (this->_HDMASrc & 0xFFU) | (value << 8U);
			break;

		case HDMA2:
			this->_HDMASrc = (this->_HDMASrc & 0xFF00U) | (value & 0xF0);
			break;

		case HDMA3:
			this->_HDMADest = (this->_HDMADest & 0xFFU) | ((value << 8U) & 0x1F00) | 0x8000;
			break;

		case HDMA4:
			this->_HDMADest = (this->_HDMADest & 0xFF00U) | (value & 0xF0);
			break;

		case HDMA5:
			this->_HDMAStart = value;
			this->_startDMA();
			break;

		default:
			break;
		}
	}

	int CPU::_executeNextInstruction()
	{
		unsigned char opcode = this->read(this->_registers.pc++);
		unsigned cycles;

		if (!this->_profiling)
			cycles = Instructions::executeInstruction(opcode, *this, this->_registers);
		else {
			unsigned old = this->_registers.pc;
			Timing::Clock clock;

			cycles = Instructions::executeInstruction(opcode, *this, this->_registers);

			auto time = clock.getElapsedTime().asSeconds();
			auto &elem = this->_profiler[Instructions::_instructionsString2[opcode](*this, old)];

			elem.first += time;
			elem.second++;
		}

		this->_registers._ = 0;
		return cycles;
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
		std::cout << "ie: " << std::setw(2) << std::setfill('0') << static_cast<int>(this->read(0xFF00 + INTERRUPT_ENABLED)) << std::endl;
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

	void CPU::init()
	{
		this->_interruptRequest = 0;
		this->_hardwareInterruptRequests = 0;
		this->_bgpi = 0;
		this->_autoIncrementBgpi = false;
		this->_obpi = 0;
		this->_autoIncrementObpi = false;
		this->_WRAMBank = 0;
		this->_speedSwitch = false;
		this->_isDoubleSpeed = false;
		this->_HDMADest = 0x8000;
		this->_HDMASrc = 0;
		this->_HDMAStart = 0;
		this->_joypadCache = 0xFF;
		this->_buttonEnabled = false;
		this->_directionEnabled = false;
		this->_halted = false;
		this->_stopped = false;
		if (this->_noBootRom)
			this->_initState();
		else {
			this->_registers = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			this->_internalRomEnabled = true;
			this->_gpu.setControlByte(0);
			this->_gpu.setXScroll(0);
			this->_gpu.setYScroll(0);
		}
		this->_divRegister = 0;
		this->_interruptEnabled = 0x00;
		this->_interruptRequest = 0x00;
		this->_interruptMasterEnableFlag = false;
		this->_gpu.setToGBMode(this->_rom.isGameBoyOnly());
		this->_oldTime = 0;
		this->_newTime = 0;
		this->_clock.restart();
	}

	void CPU::_startDMA()
	{
		unsigned short len = ((this->_HDMAStart & 0x7F) + 1) * 0x10;

		if (this->_gpu.isTransfering())
			return;
		if (!(this->_HDMAStart & 0x80)) {
			for (unsigned short i = 0; i < len; i++) {
				this->write(i + this->_HDMADest, this->read(i + this->_HDMASrc));
				if (i % 0x10 == 0xF)
					this->_updateComponents(8);
			}
		} else
			this->_gpu.startHDMA(len, this->_HDMASrc, this->_HDMADest);
	}

	void CPU::dumpProfiler()
	{
		std::vector<std::pair<std::string, std::pair<float, unsigned>>> v{
			this->_profiler.begin(),
			this->_profiler.end()
		};

		std::sort(v.begin(), v.end(), [](std::pair<std::string, std::pair<float, unsigned>> g1, std::pair<std::string, std::pair<float, unsigned>> g2){
			return g1.second.first / g1.second.second < g2.second.first / g2.second.second;
		});
		std::cout << "Mnemonic;Sample size;Total time;Average time" << std::endl;
		for (auto &g : v)
			std::cout << g.first << ";" << g.second.second << ";" << g.second.first << ";" << g.second.first / g.second.second << std::endl;
	}

	void CPU::setProfiling(bool profiling)
	{
		this->_profiling = profiling;
	}

	bool CPU::freezeAddress(unsigned short address, unsigned char value)
	{
		auto it = this->_frozenAddresses.find(address);

		if (it != this->_frozenAddresses.end())
			return this->_frozenAddresses.erase(it), false;
		return this->_frozenAddresses[address] = value, true;
	}

	void CPU::ignoreBootRom(bool ignored)
	{
		this->_noBootRom = ignored;
	}

	void CPU::goMaxSpeed(bool speed)
	{
		this->_maxSpeed = speed;
	}

	void CPU::_initState()
	{
		unsigned char pattern[] = {
			0x00, 0x00, 0x00, 0x00, 0xF0, 0xFC, 0xFC, 0xF3,
			0x3C, 0x3C, 0x3C, 0x3C, 0xF0, 0xF0, 0x00, 0xF3,
			0x00, 0x00, 0x00, 0xCF, 0x00, 0x0F, 0x3F, 0x0F,
			0x00, 0x00, 0xC0, 0x0F, 0x00, 0x00, 0x00, 0xF0,
			0x00, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x00, 0xC0,
			0x03, 0x03, 0x03, 0xFF, 0xC0, 0xC0, 0xC0, 0xC3,
			0x00, 0x00, 0x00, 0xFC, 0xF3, 0xF0, 0xF0, 0xF0,
			0x3C, 0xFC, 0xFC, 0x3C, 0xF3, 0xF3, 0xF3, 0xF3,
			0xF3, 0xC3, 0xC3, 0xC3, 0xCF, 0xCF, 0xCF, 0xCF,
			0x3C, 0x3F, 0x3C, 0x0F, 0x3C, 0xFC, 0x00, 0xFC,
			0xFC, 0xF0, 0xF0, 0xF0, 0xF3, 0xF3, 0xF3, 0xF0,
			0xC3, 0xC3, 0xC3, 0xFF, 0xCF, 0xCF, 0xCF, 0xC3,
			0x0F, 0x0F, 0x0F, 0xFC
		};
		unsigned char pattern2[] = {
			0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C
		};
		unsigned short addr = 0;

		this->_internalRomEnabled = false;
		if (this->_rom.isGameBoyOnly()) {
			this->_registers = {
				.af = 0x01B0,
				.bc = 0x0013,
				.de = 0x00D8,
				.hl = 0x014D,
				.pc = 0x0100,
				.sp = 0xFFFE
			};
			for (int i = 0; i < 0x2000; i++)
				this->_gpu.writeVRAM(i, 0);
			for (int i = 1; i <= 0xC; i++)
				this->_gpu.writeVRAM(0x1903 + i, i);
			for (int i = 0xD; i <= 0x18; i++)
				this->_gpu.writeVRAM(0x1924 - 0xD + i, i);
			this->_gpu.writeVRAM(0x1910, 0x19);
		} else {
			this->_registers = {
				.af = 0x1180,
				.bc = 0x0000,
				.de = 0xFF56,
				.hl = 0x000D,
				.pc = 0x0100,
				.sp = 0xFFFE
			};
			this->_gpu.setVBK(true);
			for (int i = 0; i < 0x2000; i++)
				this->_gpu.writeVRAM(i, 0);
			this->_gpu.setVBK(false);
			for (int i = 0; i < 0x2000; i++)
				this->_gpu.writeVRAM(i, 0);
		}

		this->_gpu.setBGPalette(0xFC);
		this->_gpu.setControlByte(0x91);
		this->_gpu.setXScroll(0);
		this->_gpu.setYScroll(0);
		for (auto c : pattern) {
			this->_gpu.writeVRAM(addr, c);
			this->_gpu.writeVRAM(addr + 2, c);
			addr += 4;
		}
		for (auto c : pattern2) {
			this->_gpu.writeVRAM(addr, c);
			addr += 2;
		}
		if (!this->_rom.isGameBoyOnly())
			this->_gpu.update(*this, GPU_FULL_CYCLE_DURATION * 0x90/ 153);
	}
}
