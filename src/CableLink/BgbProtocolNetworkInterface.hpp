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
	//! @brief L'interface CableLink utilisant le protocole de l'émulateur BGB.
	class BGBProtocolCableInterface : public CableInterface {
	private:
		//! @brief Le ProtocolHandler utilisée pour communiquer via le protocole de BGB.
		BGBHandler _handler;
		void _sync(unsigned cycles) override;
		void _sendByte(uint8_t byte) override;

	public:
		//! @brief Constructeur.
		BGBProtocolCableInterface();
		//! @brief Connecte à un émulateur avec une ip ou un nom de domaine et son port.
		//! @param host Nom de domaine ou ip du serveur.
		//! @param port Port d'écoute du serveur.
		void connect(const standard::string &host, unsigned short port);
		//! @brief Héberge un serveur sur un port.
		//! @param port Port d'écoute.
		void host(unsigned short port);
		//! @brief Se déconnecte de l'éumateur distant.
		void disconnect();
	};
}


#endif //GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP
