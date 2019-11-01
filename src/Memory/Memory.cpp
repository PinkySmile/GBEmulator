/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Memory.cpp
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Memory.hpp"

namespace GBEmulator::Memory
{
	Memory::Memory(unsigned size, unsigned short bankSize, bool readOnly) :
		_readOnly(readOnly),
		_currentBank(0),
		_bankSize(bankSize),
		_size(size),
		_memory(new unsigned char [size])
	{
		std::memset(this->_memory, 0xFF, size);
	}

	Memory::~Memory()
	{
		delete[] this->_memory;
	}

	unsigned char Memory::rawRead(unsigned short address) const
	{
		return this->_memory[address % this->_size];
	}

	unsigned char Memory::read(unsigned short address) const
	{
		return this->_memory[(address + this->_currentBank * this->_bankSize) % this->_size];
	}

	size_t Memory::getSize() const
	{
		return this->_size;
	}

	void Memory::setBankSize(size_t size)
	{
		this->_bankSize = size;
	}

	unsigned char Memory::getCurrentBank() const
	{
		return this->_currentBank;
	}

	void Memory::setMemory(unsigned char *memory, size_t size)
	{
		delete[] this->_memory;
		this->_memory = memory;
		this->_size = size;
	}

	void Memory::resize(size_t size, unsigned char fill)
	{
		auto *tab = new unsigned char [size];

		std::memset(tab, fill, size);
		if (size > this->_size)
			std::memcpy(tab, this->_memory, this->_size);
		else
			std::memcpy(tab, this->_memory, size);
		delete[] this->_memory;
		this->_memory = tab;
		this->_size = size;
	}

	void Memory::write(unsigned short address, unsigned char value)
	{
		if (this->_readOnly)
			return;
		this->forceWrite(address, value);
	}

	void Memory::forceWrite(unsigned short address,unsigned char value)
	{
		this->_memory[(address + this->_currentBank * this->_bankSize) % this->_size] = value;
	}

	void Memory::setBank(unsigned char bank)
	{
		this->_currentBank = bank % (this->_size / this->_bankSize);
	}

	void Memory::dump(unsigned short offset) const
	{
		for (unsigned int i = 0; i < this->_size; i += 0x10) {
			std::cout << std::setw(4) << std::setfill('0') << (i + offset) << ":  ";
			for (unsigned j = 0; j < 0x10 && j + i < this->_size; j++)
				std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(this->_memory[j + i]) << " ";
			for (int j = 0; j < static_cast<int>(i - this->_size + 0x10); j++)
				std::cout << "   ";
			std::cout << " ";
			for (unsigned j = 0; j < 0x10 && j + i < this->_size; j++)
				std::cout << (std::isprint(this->_memory[j + i]) ? this->_memory[j + i] : '.');
			for (int j = 0; j < static_cast<int>(i - this->_size + 0x10); j++)
				std::cout << " ";
			std::cout << std::endl;
		}
	}
}