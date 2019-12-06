//
// Created by Gegel85 on 05/04/2019.
//

#include <cstring>
#include <sstream>
#include <unistd.h>
#include <csignal>
#include "TCPSocket.hpp"
#include "Exception.hpp"

void nothing(int)
{
}

namespace GBEmulator::Network
{
	std::string TCPSocket::getLastSocketError()
	{
	#ifdef _WIN32
		wchar_t *s = nullptr;

		FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&s,
			0,
			NULL
		);

		std::stringstream stream;

		stream << "WSAGetLastError " << WSAGetLastError() << ": ";
		for (int i = 0; s[i]; i++)
			stream << static_cast<char>(s[i]);
		LocalFree(s);
		return stream.str();
	#else
		return strerror(errno);
	#endif
	}

	TCPSocket::TCPSocket()
	{
	#ifdef _WIN32
		WSADATA			WSAData;
		WSAStartup(MAKEWORD(2,0), &WSAData);
	#endif
		/* create the socket */
		this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->_socket == INVALID_SOCKET)
			throw SocketCreationErrorException(getLastSocketError());
	}

	void TCPSocket::setSocket(SOCKET sock, unsigned int ip)
	{
		signal(SIGPIPE, nothing);
		if (this->isOpen())
			throw AlreadyOpenedException("This socket is already opened");
		closesocket(this->_socket);
		this->_socket = sock;
		this->_remote = ip;
		this->_opened = true;
	}

	TCPSocket::TCPSocket(SOCKET sock, bool connected)
	{
		signal(SIGPIPE, nothing);
		this->_socket = sock;
		this->_opened = connected;
	}

	TCPSocket::~TCPSocket()
	{
		closesocket(this->_socket);
	}

	void TCPSocket::connect(const std::string &host, unsigned short portno)
	{
		struct hostent	*server;

		if (this->isOpen())
			throw AlreadyOpenedException("This socket is already opened");

		/* lookup the ip address */
		server = gethostbyname(host.c_str());
		if (server == nullptr)
			throw HostNotFoundException("Cannot find host '" + host + "'");
		this->connect(*reinterpret_cast<unsigned *>(server->h_addr), portno);
	}

	void TCPSocket::connect(unsigned int ip, unsigned short portno)
	{
		struct sockaddr_in	serv_addr = {};

		if (this->isOpen())
			throw AlreadyOpenedException("This socket is already opened");

		/* fill in the structure */
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(portno);
		serv_addr.sin_addr.s_addr = ip;

		/* connect the socket */
		if (::connect(this->_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
			throw ConnectException(std::string("Cannot connect to ") + inet_ntoa(serv_addr.sin_addr) + " on port " + std::to_string(portno));
		this->_opened = true;
		this->_remote = ip;
	}

	void TCPSocket::disconnect()
	{
		if (!this->isOpen())
			throw NotConnectedException("This socket is not connected");
		closesocket(this->_socket);
		this->_opened = false;
		this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->_socket == INVALID_SOCKET)
			throw SocketCreationErrorException(strerror(errno));
	}

	unsigned TCPSocket::getRemoteIp()
	{
		if (!this->isOpen())
			throw NotConnectedException("This socket is not connected");
		return this->_remote;
	}

	std::string TCPSocket::read(int size)
	{
		std::stringstream	stream;
		char	buffer[1024];

		while (size != 0) {
			int bytes = recv(this->_socket, buffer, static_cast<unsigned>(size) >= sizeof(buffer) ? sizeof(buffer) : size, 0);

			if (bytes <= 0)
				throw EOFException(getLastSocketError());
			stream << std::string(buffer, bytes);
			size -= bytes;
			if (bytes < static_cast<int>(sizeof(buffer)))
				break;
		}
		return stream.str();
	}

	void TCPSocket::waitFor(int seconds)
	{
		FD_SET set;
		timeval timestruct{seconds, 0};

		if (!this->isOpen())
			throw NotConnectedException("This socket is not connected");

		FD_ZERO(&set);
		FD_SET(this->_socket, &set);

		if (select(FD_SETSIZE, &set, nullptr, nullptr, seconds >= 0 ? &timestruct : nullptr) == 0)
			throw TimeOutException("Connection timed out after " + std::to_string(seconds) + " seconds");
	}

	void TCPSocket::send(const std::string &msg)
	{
		unsigned	pos = 0;

		while (pos < msg.length()) {
			int bytes = ::send(this->_socket, &msg.c_str()[pos], msg.length() - pos, 0);

			if (bytes <= 0)
				throw EOFException(getLastSocketError());
			pos += bytes;
		}
	}

	bool	TCPSocket::isOpen()
	{
		FD_SET	set;
		timeval time = {0, 0};

		FD_ZERO(&set);
		FD_SET(this->_socket, &set);
		if (this->_opened && select(FD_SETSIZE, &set, nullptr, nullptr, &time) == -1 && errno != EINTR) {
			this->_opened = false;
			throw DisconnectException(getLastSocketError());
		}
		return (this->_opened);
	}
}
