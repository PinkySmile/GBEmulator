/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** GbgProtocolNetworkInterface.hpp
*/

#ifndef GBEMULATOR_GBGPROTOCOLNETWORKINTERFACE_HPP
#define GBEMULATOR_GBGPROTOCOLNETWORKINTERFACE_HPP


#include <string>
#include "CableInterface.hpp"

namespace GBEmulator::Network
{
	class GBGProtocolCableInterface : public CableInterface {
	public:
		void disconnect();
		void connect(const std::string &host, unsigned short port);

		void read() override;
		void write() override;
	};
}


#endif //GBEMULATOR_GBGPROTOCOLNETWORKINTERFACE_HPP
