/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BgbProtocolNetworkInterface.cpp
*/

#include "BgbProtocolNetworkInterface.hpp"

namespace GBEmulator::Network
{
	BGBProtocolCableInterface::BGBProtocolCableInterface() :
		_handler([this](ProtocolHandle &, unsigned char rbyte){
			unsigned char tosend = this->byte;

			this->byte = rbyte;
			return tosend;
		},
		[this](ProtocolHandle &, unsigned char b){
			this->byte = b;
		}, true)
	{
	}

	void BGBProtocolCableInterface::_sync(unsigned cycles)
	{
		this->_handler.tick(cycles);
	}

	void BGBProtocolCableInterface::host(unsigned short port)
	{
		this->_handler.host(port);
		this->_received = true;
	}

	void BGBProtocolCableInterface::_sendByte(unsigned char sbyte)
	{
		if (this->_byte & 0b1U)
			this->_handler.sendByte(sbyte);
		else if (!this->_received)
			this->_handler.reply(sbyte);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool BGBProtocolCableInterface::_isTransfering()
	{
		return false;
	}

	void BGBProtocolCableInterface::connect(const std::string &host, unsigned short port)
	{
		this->_handler.connect(host, port);
		this->_received = true;
	}

	void BGBProtocolCableInterface::disconnect()
	{
		this->_handler.disconnect();
	}
}