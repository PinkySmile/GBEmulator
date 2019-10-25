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
		return this->_byte & 0x01U;
	}

	bool CableInterface::isTransfering() const
	{
		return this->_byte & 0x80U;
	}

	void CableInterface::setControlByte(unsigned char byte)
	{
		this->_byte = byte;
	}

	unsigned char CableInterface::getControlByte() const
	{
		return this->_byte;
	}

	void CableInterface::transfer(unsigned int cycles)
	{
		this->_sync(cycles);

		if (!this->isTransfering())
			return;

		unsigned char toSend = this->_byte;

		if (this->isExternal())
			this->_byte = this->_receiveByte();

		this->_sendByte(toSend);

		if (!this->isExternal())
			this->_byte = this->_receiveByte();

		this->_byte &= 0x7FU;
	}
}