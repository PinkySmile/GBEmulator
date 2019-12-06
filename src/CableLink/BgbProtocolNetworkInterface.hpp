/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BgbProtocolNetworkInterface.hpp
*/

#ifndef GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP
#define GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP


#include <string>
#include "CableInterface.hpp"
#include "../Network/BgbHandler.hpp"

namespace GBEmulator::Network
{
	class BGBProtocolCableInterface : public CableInterface {
	private:
		bool _received = true;
		BGBHandler _handler;
		bool _isTransfering() override;
		void _sync(unsigned cycles) override;
		void _sendByte(unsigned char byte) override;

	public:
		BGBProtocolCableInterface();
		BGBProtocolCableInterface(const BGBProtocolCableInterface &) = delete;
		~BGBProtocolCableInterface() = default;
		BGBProtocolCableInterface &operator=(const BGBProtocolCableInterface &) = delete;
		void connect(const std::string &host, unsigned short port);
		void host(unsigned short port);
		void disconnect();
	};
}


#endif //GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP
