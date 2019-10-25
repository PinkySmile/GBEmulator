/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CableInterface.hpp
*/

#ifndef GBEMULATOR_CABLEINTERFACE_HPP
#define GBEMULATOR_CABLEINTERFACE_HPP

namespace GBEmulator::Network
{
	class CableInterface {
	private:
		unsigned char _byte;

		virtual void _sync(unsigned cycles) = 0;
		virtual unsigned char _receiveByte() = 0;
		virtual void _sendByte(unsigned char byte) = 0;

	public:
		unsigned char byte = 0xFF;

		void setControlByte(unsigned char byte);
		unsigned char getControlByte() const;
		bool isExternal() const;
		bool isTransfering() const;
		void transfer(unsigned int cycles);
	};
}

#endif //GBEMULATOR_CABLEINTERFACE_HPP
