//
// Created by Gegel85 on 20/06/2019.
//

#ifndef POKE_AI_EXCEPTION_HPP
#define POKE_AI_EXCEPTION_HPP


#include <exception>
#include <string>

namespace GBEmulator::Network
{
	//! Exception de base pour le module réseau de la GameBoy
	class BaseException : public std::exception {
	private:
		std::string _msg;

	public:
		explicit BaseException(const std::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	//! Exception levée quand le flux est terminé
	class EOFException : public BaseException {
	public:
		explicit EOFException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée lorsque une erreur survient à la création d'un socket
	class SocketCreationErrorException : public BaseException {
	public:
		explicit SocketCreationErrorException(const std::string &msg) : BaseException((msg)) {};
	};

	//! Exception levée quand l'utilisateur n'est pas connecté
	class NotConnectedException : public BaseException {
	public:
		explicit NotConnectedException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand l'utilisateur est déconnecté
	class DisconnectException : public BaseException {
	public:
		explicit DisconnectException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand le numéro de version n'est pas valide
	class InvalidVersionException : public BaseException {
	public:
		explicit InvalidVersionException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand le socket est déjà ouvert
	class AlreadyOpenedException : public BaseException {
	public:
		explicit AlreadyOpenedException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand une erreur pendant la connection arrive
	class ConnectException : public BaseException {
	public:
		explicit ConnectException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand l'hote n'est pas trouvé
	class HostNotFoundException : public BaseException {
	public:
		explicit HostNotFoundException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand le délai d'attente à expiré
	class TimeOutException : public BaseException {
	public:
		explicit TimeOutException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand la fonction appellé n'a pas été implémenté
	class NotImplementedException : public BaseException {
	public:
		explicit NotImplementedException(const std::string &msg) : BaseException(msg) {};
	};

	//! Exception levée quand l'écoute du socket a renvoyé une erreur
	class ListenFailedException : public BaseException {
	public:
		explicit ListenFailedException(const std::string &msg) : BaseException(msg) {};
	};
}


#endif //POKE_AI_EXCEPTION_HPP
