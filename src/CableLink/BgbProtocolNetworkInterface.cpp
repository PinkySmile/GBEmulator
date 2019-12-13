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
		_handler([this](ProtocolHandle &handler, unsigned char rbyte){
			unsigned char tosend = this->byte;

			this->byte = rbyte;
			if (this->isTransfering())
				handler.reply(tosend);
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
	}

	void BGBProtocolCableInterface::_sendByte(unsigned char sbyte)
	{
		if (this->_byte & 0b1U)
			this->_handler.sendByte(sbyte);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool BGBProtocolCableInterface::_isTransfering()
	{
		return false;
	}

	void BGBProtocolCableInterface::connect(const std::string &host, unsigned short port)
	{
		this->_handler.connect(host, port);
	}

	void BGBProtocolCableInterface::disconnect()
	{
		this->_handler.disconnect();
	}
}