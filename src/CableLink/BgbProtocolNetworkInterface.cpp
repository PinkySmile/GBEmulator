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
			if (this->isTransfering() && this->isExternal()) {
				//std::cout << "Successfully received 0x" << std::hex << static_cast<int>(rbyte) << std::dec << " as master (Replying 0x" << std::hex << static_cast<int>(this->byte) << std::dec << ")" << std::endl;
				handler.reply(this->byte);
				this->byte = rbyte;
			} else
				handler.reply(0xFF);
				/* else if (!this->isExternal())
				std::cout << "Receive 0x" << std::hex << static_cast<int>(rbyte) << std::dec << " but not external (master)" << std::endl;
			else
				std::cout << "Receive 0x" << std::hex << static_cast<int>(rbyte) << std::dec << " but not transfering (master)" << std::endl;*/
		},
		[this](ProtocolHandle &, unsigned char b){
			if (this->isTransfering() && !this->isExternal()) {
				this->_isTransfering = false;
				this->_needInterrupt = true;
				this->byte = b;
				//std::cout << "Successfully received " << std::hex << static_cast<int>(b) << std::dec << " as slave" << std::endl;
			}/* else if (this->isExternal())
				std::cout << "Receive 0x" << std::hex << static_cast<int>(b) << std::dec << " but external (slave)" << std::endl;
			else
				std::cout << "Receive 0x" << std::hex << static_cast<int>(b) << std::dec << " but not transfering (master)" << std::endl;*/
		})
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
		//std::cout << "Sending 0x" << std::hex << static_cast<int>(sbyte) << std::dec << std::endl;
		if (this->_handler.isConnected()) {
			this->_handler.sendByte(sbyte);
			this->_handler.waitAnswer(1);
		} else
			this->byte = 0xFF;
		this->_isTransfering = false;
		this->_needInterrupt = true;
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