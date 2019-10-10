/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Memory.cpp
*/

#include "Memory.hpp"

namespace GBEmulator
{
	Memory::Memory(unsigned size, unsigned short bankSize) :
		_currentBank(0),
		_bankSize(bankSize)
	{
		this->_memory.resize(size, 0xFF);
	}

	unsigned char Memory::read(unsigned short address) const
	{
		return this->_memory.at((address + this->_currentBank * this->_bankSize) % this->_memory.size());
	}

	void Memory::write(unsigned short address, unsigned char value)
	{
		this->_memory[(address + this->_currentBank * this->_bankSize) % this->_memory.size()] = value;
	}

	void Memory::setBank(unsigned char bank)
	{
		this->_currentBank = bank % (this->_memory.size() / this->_bankSize);
	}
}