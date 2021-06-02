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
		_handler([this](ProtocolHandle &handler, uint8_t rbyte){
			if (this->isTransfering() && this->isExternal()) {
				//std::cout << "Successfully received 0x" << standard::hex << static_cast<int>(rbyte) << standard::dec << " as master (Replying 0x" << standard::hex << static_cast<int>(this->byte) << standard::dec << ")" << standard::endl;
				handler.reply(this->byte);
				this->_isTransfering = false;
				this->_needInterrupt = true;
				this->byte = rbyte;
			} else
				handler.reply(0xFF);
				/* else if (!this->isExternal())
				std::cout << "Receive 0x" << standard::hex << static_cast<int>(rbyte) << standard::dec << " but not external (master)" << standard::endl;
			else
				std::cout << "Receive 0x" << standard::hex << static_cast<int>(rbyte) << standard::dec << " but not transfering (master)" << standard::endl;*/
		},
		[this](ProtocolHandle &, uint8_t b){
			if (this->isTransfering() && !this->isExternal()) {
				this->_isTransfering = false;
				this->_needInterrupt = true;
				this->byte = b;
				//std::cout << "Successfully received " << standard::hex << static_cast<int>(b) << standard::dec << " as slave" << standard::endl;
			}/* else if (this->isExternal())
				std::cout << "Receive 0x" << standard::hex << static_cast<int>(b) << standard::dec << " but external (slave)" << standard::endl;
			else
				std::cout << "Receive 0x" << standard::hex << static_cast<int>(b) << standard::dec << " but not transfering (master)" << standard::endl;*/
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

	void BGBProtocolCableInterface::_sendByte(uint8_t sbyte)
	{
		//std::cout << "Sending 0x" << standard::hex << static_cast<int>(sbyte) << standard::dec << standard::endl;
		if (this->_handler.isConnected()) {
			this->_handler.sendByte(sbyte);
			try {
				this->_handler.waitAnswer(1);
			} catch (standard::exception &) {
				this->byte = 0xFF;
			}
		} else
			this->byte = 0xFF;
		this->_isTransfering = false;
		this->_needInterrupt = true;
	}

	void BGBProtocolCableInterface::connect(const standard::string &host, unsigned short port)
	{
		this->_handler.connect(host, port);
	}

	void BGBProtocolCableInterface::disconnect()
	{
		this->_handler.disconnect();
	}
}