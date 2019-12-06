/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ServerSocket.cpp
*/

#include <iostream>
#include "TCPServerSocket.hpp"
#include "Exception.hpp"

namespace GBEmulator::Network
{
	TCPServerSocket::~TCPServerSocket()
	{
		for (auto &thread : this->_threads)
			if (thread.joinable())
				thread.join();
	}

	void TCPServerSocket::bind(unsigned short port)
	{
		struct sockaddr_in address{};

		address.sin_port = htons(port);
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		if (::bind(this->_socket, (struct sockaddr *)&address, sizeof(address)) == -1)
			throw BindFailedException(getLastSocketError());
		if (listen(this->_socket, MAX_SOCKETS) == -1)
			throw ListenFailedException(getLastSocketError());
		this->_opened = true;
	}

	std::shared_ptr<TCPSocket> TCPServerSocket::acceptClient(const std::function<void(TCPSocket &)> &handler)
	{
		if (!this->isOpen())
			throw NotConnectedException("The server socket is not bound to a port. Call bind first.");

		if (!handler)
			throw InvalidHandlerException("The data handler sent to acceptClient is empty");

		unsigned i = 0;

		while (i < this->_clients.size() && this->_clients.at(i)->isOpen())
			i++;

		if (i == this->_clients.size())
			this->_clients.emplace_back(new TCPSocket());

		TCPSocket &socket = *this->_clients[i];
		sockaddr_in address{};
		socklen_t size = sizeof(address);
		SOCKET sock = ::accept(
			this->getSystemSocket(),
			reinterpret_cast<struct sockaddr *>(&address),
			&size
		);

		socket.setSocket(
			sock,
			address.sin_addr.s_addr
		);

		this->_threads.emplace_back([&socket, handler, this](){
			TCPSocket &clientsock = socket;

			while (this->isOpen() && clientsock.isOpen())
				try {
					clientsock.waitFor(1);
					handler(clientsock);
				} catch (TimeOutException &) {
				} catch (std::exception &e) {
					std::cerr << "Error while receiving data " << e.what() << std::endl;
					try { clientsock.disconnect(); } catch (std::exception &) {}
				}
		});
		return this->_clients[i];
	}

	void TCPServerSocket::disconnectClients()
	{
		for (auto &sock : this->_clients)
			try {
				sock->disconnect();
			} catch (std::exception &) {}
		this->_clients.clear();
	}
}