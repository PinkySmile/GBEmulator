/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CableInterface.cpp
*/

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

	void CableInterface::setControlByte(uint8_t c_byte)
	{
		this->_isExternal = (c_byte & 0x01U) == 0;
		this->_isTransfering = c_byte & 0x80U;
		if (this->_isTransfering && !this->_isExternal)
			this->transfer();
	}

	uint8_t CableInterface::getControlByte() const
	{
		return (this->_isTransfering << 7U) | !this->_isExternal | 0b01111110U;
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
		//TODO: Don't wait for other response here.
		//      Rather, wait when the ROM needs the received byte.
		//      It should give us more time to do the network stuff.
		this->_sendByte(this->byte);
	}
}