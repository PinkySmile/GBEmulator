/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ServerSocket.hpp
*/

#ifndef CPP_BABEL_2019_SERVERSOCKET_HPP
#define CPP_BABEL_2019_SERVERSOCKET_HPP


#include <functional>
#include <vector>
#include <thread>
#include "TCPSocket.hpp"

#define MAX_SOCKETS 32

namespace GBEmulator::Network
{
	class TCPServerSocket : public TCPSocket {
	private:
		std::vector<std::thread> _threads;
		std::vector<std::shared_ptr<TCPSocket>> _clients;

	public:
		~TCPServerSocket();
		void bind(unsigned short port);
		std::shared_ptr<TCPSocket> acceptClient(const std::function<void (TCPSocket &)> &handler = {});
		void disconnectClients();
	};
}


#endif //CPP_BABEL_2019_SERVERSOCKET_HPP
