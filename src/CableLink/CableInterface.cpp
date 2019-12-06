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

	void CableInterface::setControlByte(unsigned char cbyte)
	{
		this->_byte = cbyte;
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

		unsigned char toSend = this->byte;

		this->_sendByte(toSend);

		if (!this->_isTransfering())
			this->_byte &= 0x7FU;
	}
}