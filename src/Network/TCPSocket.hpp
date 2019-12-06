//
// Created by Gegel85 on 05/04/2019.
//

#ifndef DISC_ORD_SOCKET_HPP
#define DISC_ORD_SOCKET_HPP


#if defined _WIN32
#	include <winsock.h>
#else
#	include <netdb.h>
#	include <arpa/inet.h>
#	include <sys/select.h>
#	define INVALID_SOCKET -1
#	define closesocket(socket) close(socket)
	typedef int SOCKET;
	typedef fd_set FD_SET;
#endif
#include <string>
#include <map>

namespace GBEmulator::Network
{
	class TCPSocket {
	public:
		static std::string getLastSocketError();

		TCPSocket();
		TCPSocket(SOCKET sock, bool connected = false);
		~TCPSocket();
		bool                    isOpen();
		virtual void            connect(const std::string &host, unsigned short portno);
		virtual void            connect(unsigned int ip, unsigned short portno);
		virtual void            disconnect();
		virtual void            send(const std::string &);
		virtual std::string     read(int size);
		unsigned                getRemoteIp();
		SOCKET                  getSystemSocket() const { return this->_socket; };
		void                    waitFor(int seconds);
		void                    setSocket(SOCKET sock, unsigned int ip = 0);

	protected:
		SOCKET		_socket = INVALID_SOCKET;
		bool		_opened = false;
		unsigned	_remote = 0;
	};
}

#endif //DISC_ORD_SOCKET_HPP
