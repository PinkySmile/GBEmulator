//
// Created by Gegel85 on 13/07/2019.
//

#ifndef POKEAI_BGBHANDLER_HPP
#define POKEAI_BGBHANDLER_HPP


#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include <SFML/Network.hpp>
#include "ProtocolHandle.hpp"

namespace GBEmulator::Network
{
	//! @brief Implementation du ProtocolHandle avec le protocole de BGB.
	class BGBHandler : public ProtocolHandle {
	private:
		//! @brief Est-ce que le logging est activé.
		bool _log;
		//! @brief Est-ce que un byte à été reçu.
		bool _received = true;
		//! @brief Est-ce que le logging est en cours.
		bool _logging = false;
		//! @brief Socket du serveur.
		sf::TcpListener _serv;
		//! @brief Socket du client.
		sf::TcpSocket _socket;
		//! @brief Thread qui gère les connections.
		standard::unique_ptr<sf::Thread> _mainThread;
		//! @brief Nombre de cycles CPU écoulés.
		unsigned _ticks = 0;
		//! @brief Handler qui gère les connections.
		std::function<void ()> _mainHandler;

		//! @brief Un packet
		struct BGBPacket {
			uint8_t b1;
			uint8_t b2;
			uint8_t b3;
			uint8_t b4;
			unsigned int  i1;
		};

		//! @brief Effectue une poingnée de main avec le pair.
		void _handshake();
		//! @brief Fonction appelé en boucle et qui traite un packet reçu par le pair.
		bool _handleLoop();
		//! @brief Envoie un packet.
		void _sendPacket(const BGBPacket &packet);
		//! @brief Envoie un packet de syncronisation.
		void _sync();
		//! @brief Lis le prochain packet reçu.
		BGBPacket _getNextPacket();

	public:
		//! @brief Constructeur
		//! @param masterHandler Handler appelé quand un byte est reçu en mode master.
		//! @param slaveHandler Handler appelé quand un byte est reçu en mode slave.
		//! @param log Dés/active le logging.
		BGBHandler(
			const ByteHandle &masterHandler,
			const ByteHandle &slaveHandler,
			bool log = false
		);
		//! @brief Déstructeur
		~BGBHandler();
		void host(unsigned short port) override;
		//! @param Afficher un message dans le flux.
		void log(const standard::string &string, std::ostream &stream = std::cerr);
		void connect(const standard::string &ip, unsigned short port) override;
		void disconnect() override;
		void sendByte(uint8_t byte) override;
		void reply(uint8_t byte) override;
		void waitAnswer(unsigned timeout = -1) override;
		//! @brief Fait s'ecouler nb ticks.
		//! @param nb Nombre de cycles CPU écoulés.
		void tick(unsigned nb);

		//! @brief Opcodes du protocol BGB.
		enum BGBCommand {
			VERSION_CHECK	= 1,
			JOYPAD_CHANGE	= 101,
			SYNC1_SIGNAL	= 104,
			SYNC2_SIGNAL	= 105,
			SYNC3_SIGNAL	= 106,
			STATUS		= 108,
			WANT_DISCONNECT	= 109,
		};

		//! @brief Flag de status du protocol.
		enum BGBStatusFlag {
			STATUSFLAG_RUNNING		= 1U << 0U,
			STATUSFLAG_PAUSED		= 1U << 1U,
			STATUSFLAG_SUPPORT_RECONNECT	= 1U << 2U,
		};

		//! @brief Taille d'un packet dans le protocol.
		static const int8_t PACKET_SIZE = 8;
	};
}


#endif //POKEAI_BGBHANDLER_HPP
