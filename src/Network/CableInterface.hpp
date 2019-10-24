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
		bool _activated = false;

	public:
		unsigned char byte = 0xFF;

		bool isActivated();
		virtual void setActivated(bool activated);

		virtual void read() = 0;
		virtual void write() = 0;
	};
}

#endif //GBEMULATOR_CABLEINTERFACE_HPP
