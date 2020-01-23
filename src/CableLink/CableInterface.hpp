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
		virtual void _sync(unsigned cycles) = 0;
		virtual void _sendByte(unsigned char byte) = 0;

	protected:
		bool _needInterrupt = false;
		bool _isExternal = false;
		bool _isTransfering = false;

	public:
		unsigned char byte = 0xFF;

		void setControlByte(unsigned char c_byte);
		unsigned char getControlByte() const;
		bool isExternal() const;
		bool triggerInterrupt();
		bool isTransfering() const;
		void update(unsigned int cycles);
		void transfer();
	};
}

#endif //GBEMULATOR_CABLEINTERFACE_HPP
