//
// Created by Gegel85 on 13/07/2019.
//

#ifdef _WIN32
#include <inaddr.h>
#else
#include <sys/socket.h>

typedef fd_set FD_SET;
typedef struct timeval TIMEVAL;
#endif
#include "BgbHandler.hpp"
#include "Exception.hpp"

namespace GBEmulator::Network
{
	BGBHandler::BGBHandler(
		const std::function<unsigned char(ProtocolHandle &handler, unsigned char byte)> &masterHandler,
		const std::function<void(ProtocolHandle &handler, unsigned char byte)> &slaveHandler,
		bool log
	) :
		ProtocolHandle(masterHandler, slaveHandler),
		_log(log),
		_mainHandler([this] { while (this->_handleLoop()); })
	{}

	BGBHandler::~BGBHandler()
	{
		if (this->isConnected())
			this->disconnect();
	}

	void BGBHandler::host(unsigned short port)
	{
		if (this->_serv.isOpen())
			this->_serv.disconnect();
		this->log("Waiting for connection on port " + std::to_string(port));
		this->_serv.disconnectClients();
		this->_serv.bind(port);
		this->_socket = this->_serv.acceptClient([](TCPSocket &){});
		this->_handshake();
	}

	void BGBHandler::_handshake()
	{
		this->log("Performing handshake");
		this->_sendPacket({VERSION_CHECK, 1, 4, 0, 0});

		BGBPacket packet = this->_getNextPacket();

		if (packet.b1 != VERSION_CHECK)
			throw InvalidVersionException("Remote didn't send the version packet");

		if (packet.b2 != 1 || packet.b3 != 4 || packet.b4 != 0 || packet.i1 != 0) {
			this->log("Remote version is invalid");
			throw InvalidVersionException("Remote version is not compatible");
		}
		this->_sendPacket({STATUS, STATUSFLAG_RUNNING, 0, 0, 0});
		this->log("Remote version is OK");
	}

	void BGBHandler::connect(const std::string &ip, unsigned short port)
	{
		this->log("Connecting to " + ip + ":" + std::to_string(port));
		this->_socket.reset(new TCPSocket());
		this->_socket->connect(ip, port);

		try {
			this->_handshake();
		} catch (std::exception &e) {
			this->log(e.what());
			this->_socket->disconnect();
			throw;
		}

		this->_disconnected = false;
		this->_mainThread = std::thread(this->_mainHandler);
	}

	void BGBHandler::disconnect()
	{
		this->log("Disconnecting...");
		this->_sendPacket({WANT_DISCONNECT, 0, 0, 0, 0});
		this->_socket->disconnect();
		if (this->_mainThread.joinable())
			this->_mainThread.join();
		this->_disconnected = true;
	}

	void BGBHandler::log(const std::string &string, std::ostream &stream)
	{
		while (this->_logging)
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->_logging = true;
		if (this->_log)
			stream << "[BGBHandler]: " << string << std::endl;
		this->_logging = false;
	}

	void BGBHandler::sendByte(unsigned char byte)
	{
		this->log("Sending " + charToHex(byte));
		this->_sendPacket({SYNC1_SIGNAL, byte, 0x80, 0, this->_ticks});
	}

	void BGBHandler::reply(unsigned char byte)
	{
		this->log("Replying " + charToHex(byte));
		this->_sendPacket({SYNC2_SIGNAL, byte, 0x80, 0, 0});
	}

	void BGBHandler::_sendPacket(const BGBHandler::BGBPacket &packet)
	{
		char buffer[8];

		//this->log("Sending opcode " + std::to_string(packet.b1));
		buffer[0] = packet.b1;
		buffer[1] = packet.b2;
		buffer[2] = packet.b3;
		buffer[3] = packet.b4;
		buffer[4] = (static_cast<unsigned char>(packet.i1) >> 0LU);
		buffer[5] = (static_cast<unsigned char>(packet.i1) >> 8LU);
		buffer[6] = (static_cast<unsigned char>(packet.i1) >> 16LU);
		buffer[7] = (static_cast<unsigned char>(packet.i1) >> 24LU);
		try {
			this->_socket->send({
				buffer,
				sizeof(buffer)
			});
		} catch (std::exception &) {}
	}

	BGBHandler::BGBPacket BGBHandler::_getNextPacket()
	{
		std::string serverMessage;

		this->_socket->waitFor(10);

		if (!this->_socket->isOpen())
			throw EOFException("EndOfFile");

		serverMessage = this->_socket->read(PACKET_SIZE);

		if (serverMessage.length() != 8)
			throw InvalidVersionException("Server sent a " + std::to_string(serverMessage.length()) + " bytes long packet but it should be 8");

		return {
			static_cast<unsigned char>(serverMessage[0]),
			static_cast<unsigned char>(serverMessage[1]),
			static_cast<unsigned char>(serverMessage[2]),
			static_cast<unsigned char>(serverMessage[3]),
			static_cast<unsigned int>(
				(static_cast<unsigned char>(serverMessage[4]) << 0LU) +
				(static_cast<unsigned char>(serverMessage[5]) << 8LU) +
				(static_cast<unsigned char>(serverMessage[6]) << 16LU)+
				(static_cast<unsigned char>(serverMessage[7]) << 24LU)
			)
		};
	}

	void BGBHandler::tick(unsigned nb)
	{
		this->_ticks += nb;
	}

	void BGBHandler::_sync()
	{
		this->_sendPacket({SYNC3_SIGNAL, 0, 0, 0, this->_ticks});
	}

	bool BGBHandler::_handleLoop()
	{
		if (this->_disconnected || !this->_socket->isOpen())
			return false;

		BGBPacket packet;

		//this->log("Received opcode " + std::to_string(packet.b1));
		try {
			packet = this->_getNextPacket();
		} catch (TimeOutException &e) {
			this->log("Error: " + std::string(e.what()));
			return false;
		} catch (EOFException &e) {
			this->log("Error: EOF found" + std::string(e.what()));
			return false;
		}

		switch (packet.b1) {
		case VERSION_CHECK:
			if (packet.b2 != 1 || packet.b3 != 4 || packet.b4 != 0 || packet.i1 != 0) {
				this->log("Server version is invalid");
				throw InvalidVersionException("Server version is not compatible");
			}
			this->_sendPacket({STATUS, STATUSFLAG_RUNNING, 0, 0, 0});
			this->log("Server version is OK");
			return true;

		case SYNC1_SIGNAL:
			this->log("Received one byte (" + charToHex(packet.b2) + ") as master");
			this->reply(this->_masterHandler(*this, packet.b2));
			return true;

		case SYNC2_SIGNAL:
			if (packet.b3 != 0x80) {
				this->log("Received invalid sync2 packet");
				return true;
			}
			this->log("Received one byte (" + charToHex(packet.b2) + ") as slave");
			this->_slaveHandler(*this, packet.b2);
			return true;

		case SYNC3_SIGNAL:
			this->_sync();
			return true;

		case STATUS:
			this->_sendPacket({STATUS, STATUSFLAG_RUNNING, 0, 0, 0});
			this->_sync();
			return true;

		case JOYPAD_CHANGE:
			return true;

		case WANT_DISCONNECT:
			this->_socket->disconnect();
			return false;
		default:
			this->log("Unknown command sent by server (Opcode: " + std::to_string(packet.b1) + ")");
		}
		return true;
	}
}
