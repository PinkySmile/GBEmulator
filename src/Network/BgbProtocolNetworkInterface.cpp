/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BgbProtocolNetworkInterface.cpp
*/

#include "BgbProtocolNetworkInterface.hpp"

namespace GBEmulator::Network
{
	void BGBProtocolCableInterface::_sync(unsigned)
	{
		//TODO: Sync the games with the remote
	}

	void BGBProtocolCableInterface::_sendByte(unsigned char)
	{
		//TODO: Send the byte
	}

	unsigned char BGBProtocolCableInterface::_receiveByte()
	{
		//TODO: Receive a byte
		return 0xFF;
	}
}