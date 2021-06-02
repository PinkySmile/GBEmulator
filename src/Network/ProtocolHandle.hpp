//
// Created by Gegel85 on 13/07/2019.
//

#ifndef POKEAI_EMULATORHANDLE_HPP
#define POKEAI_EMULATORHANDLE_HPP


#include <sstream>
#include <iomanip>
#include <iostream>
#include <functional>

//! @brief Transforme un charactère sous sa représentation hexadécimale.
#define charToHex(val)\
([](uint8_t i){\
	standard::stringstream stream;\
\
	stream << "0x" << standard::setfill('0') << standard::setw(2) << standard::hex << standard::uppercase << static_cast<int>(i);\
	return stream.str();\
}(val))

namespace GBEmulator::Network
{
	//! @brief Handler appelé quand un byte est reçu.
	typedef std::function<void(class ProtocolHandle &handler, uint8_t byte)> ByteHandle;

	//! @brief Une interface qui permet de recevoire des données et en envoyer pour GameBoy.
	class ProtocolHandle {
	protected:
		//! @brief Est-ce que cet objet est connecté ?
		bool _disconnected = true;
		//! @brief Handler appelé quand un byte est reçu en mode slave.
		ByteHandle _slaveHandler;
		//! @brief Handler appelé quand un byte est reçu en mode master.
		ByteHandle _masterHandler;

		//! @brief Constructeur
		//! @param masterHandler Handler appelé quand un byte est reçu en mode master.
		//! @param slaveHandler Handler appelé quand un byte est reçu en mode slave.
		ProtocolHandle(const ByteHandle &masterHandler, const ByteHandle &slaveHandler) :
			_slaveHandler(slaveHandler),
			_masterHandler(masterHandler)
		{};

	public:
		//! @brief Destructeur.
		virtual ~ProtocolHandle() = default;
		//! @brief Ouvre un serveur sur un port.
		//! @param port Port sur lequel le serveur va écouter.
		virtual void host(unsigned short port) = 0;
		//! @brief Se connecte à un serveur avec une ip ou un nom de domaine et un port.
		//! @param ip Ip ou non de domaine.
		//! @param port Port d'écoute du serveur.
		virtual void connect(const standard::string &ip, unsigned short port) = 0;
		//! @brief Envoie un byte de donnée en mode master.
		//! @param byte Byte à envoyer.
		virtual void sendByte(uint8_t byte) = 0;
		//! @brief Envoie un byte de donnée en mode slave.
		//! @param byte Byte à envoyer.
		virtual void reply(uint8_t byte) = 0;
		//! @brief Se déconnecte du serveur
		virtual void disconnect() = 0;
		//! @brief Attends qu'un byte soit reçu pendant timeout secondes.
		//! @param timeout Temps en secondes à attendre
		virtual void waitAnswer(unsigned timeout = -1) = 0;

		//! @brief Renvoie si cet objet est connecté.
		//! @return True si l'objet est connecté. Sinon, false.
		bool isConnected()
		{
			return !this->_disconnected;
		}
	};
}


#endif //POKEAI_EMULATORHANDLE_HPP
