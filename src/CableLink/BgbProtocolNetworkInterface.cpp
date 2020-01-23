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
			if (this->isTransfering()) {
				this->_isExternal = true;
				this->_isTransfering = false;
				this->_needInterrupt = true;
				handler.reply(this->byte);
				this->byte = rbyte;
			} else {
				std::cout << "Receive but not transfering" << std::endl;
			}
		},
		[this](ProtocolHandle &, unsigned char b){
			if (this->isTransfering()) {
				this->_isTransfering = false;
				this->_needInterrupt = true;
				this->byte = b;
			} else {
				std::cout << "Receive but not transfering" << std::endl;
			}
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
		this->_handler.sendByte(sbyte);
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