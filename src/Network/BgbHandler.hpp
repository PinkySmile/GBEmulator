//
// Created by Gegel85 on 13/07/2019.
//

#ifndef POKEAI_BGBHANDLER_HPP
#define POKEAI_BGBHANDLER_HPP


#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include "TCPSocket.hpp"
#include "ProtocolHandle.hpp"
#include "TCPServerSocket.hpp"

namespace GBEmulator::Network
{
	class BGBHandler : public ProtocolHandle {
	private:
		bool _log;
		bool _logging = false;
		TCPServerSocket _serv;
		std::shared_ptr<TCPSocket> _socket;
		std::thread _mainThread;
		unsigned _ticks = 0;
		std::function<void ()> _mainHandler;

		struct BGBPacket {
			unsigned char b1;
			unsigned char b2;
			unsigned char b3;
			unsigned char b4;
			unsigned int  i1;
		};

		void _handshake();
		bool _handleLoop();
		void _sendPacket(const BGBPacket &packet);
		void _sync();
		BGBPacket _getNextPacket();

	public:
		BGBHandler(
			const MasterByteHandle &masterHandler,
			const SlaveByteHandle &slaveHandler,
			bool log = false
		);
		void host(unsigned short port) override;
		void log(const std::string &string, std::ostream &stream = std::cerr);
		void connect(const std::string &ip, unsigned short port) override;
		void disconnect() override;
		void sendByte(unsigned char byte) override;
		void reply(unsigned char byte) override;
		void tick(unsigned nb);
		~BGBHandler();

		enum BGBCommand {
			VERSION_CHECK	= 1,
			JOYPAD_CHANGE	= 101,
			SYNC1_SIGNAL	= 104,
			SYNC2_SIGNAL	= 105,
			SYNC3_SIGNAL	= 106,
			STATUS		= 108,
			WANT_DISCONNECT	= 109,
		};

		enum BGBStatusFlag {
			STATUSFLAG_RUNNING		= 1U << 0U,
			STATUSFLAG_PAUSED		= 1U << 1U,
			STATUSFLAG_SUPPORT_RECONNECT	= 1U << 2U,
		};

		static const char PACKET_SIZE = 8;
	};
}


#endif //POKEAI_BGBHANDLER_HPP
