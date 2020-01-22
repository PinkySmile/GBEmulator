/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CableInterface.cpp
*/

#include <iostream>
#include "CableInterface.hpp"

namespace GBEmulator::Network
{
	bool CableInterface::isExternal() const
	{
		return this->_isExternal;
	}

	bool CableInterface::isTransfering() const
	{
		return this->_isTransfering;
	}

	void CableInterface::setControlByte(unsigned char c_byte)
	{
		this->_isExternal = c_byte & 0x01U;
		this->_isTransfering = c_byte & 0x80U;
		std::cout << (this->_isTransfering ? "Set" : "Unset") << " transfering as " << (this->_isExternal ? "slave" : "master") << std::endl;
		if (this->_isTransfering && !this->_isExternal)
			transfer();
	}

	unsigned char CableInterface::getControlByte() const
	{
		return (this->_isTransfering << 7U) | this->_isExternal | 0b01111110U;
	}

	bool CableInterface::triggerInterrupt()
	{
		bool val = this->_needInterrupt;

		this->_needInterrupt = false;
		return val;
	}

	void CableInterface::update(unsigned int cycles)
	{
		this->_sync(cycles);
	}

	void CableInterface::transfer()
	{
		this->_sendByte(this->byte);
	}
}