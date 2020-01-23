//
// Created by Gegel85 on 13/07/2019.
//

#ifndef POKEAI_EMULATORHANDLE_HPP
#define POKEAI_EMULATORHANDLE_HPP


#include <sstream>
#include <iomanip>
#include <iostream>
#include <functional>

#define charToHex(val)\
([](unsigned char i){\
	std::stringstream stream;\
\
	stream << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<int>(i);\
	return stream.str();\
}(val))

namespace GBEmulator::Network
{
	typedef std::function<void(class ProtocolHandle &handler, unsigned char byte)> ByteHandle;

	class ProtocolHandle {
	protected:
		bool _disconnected = true;
		ByteHandle _slaveHandler;
		ByteHandle _masterHandler;

		ProtocolHandle(const ByteHandle &masterHandler, const ByteHandle &slaveHandler) :
			_slaveHandler(slaveHandler),
			_masterHandler(masterHandler)
		{};

	public:
		virtual ~ProtocolHandle() = default;
		virtual void host(unsigned short port) = 0;
		virtual void connect(const std::string &ip, unsigned short port) = 0;
		virtual void sendByte(unsigned char byte) = 0;
		virtual void reply(unsigned char byte) = 0;
		virtual void disconnect() = 0;

		bool isConnected()
		{
			return !this->_disconnected;
		}
	};
}


#endif //POKEAI_EMULATORHANDLE_HPP
