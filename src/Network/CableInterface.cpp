/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CableInterface.cpp
*/

#include "CableInterface.hpp"

namespace GBEmulator::Network
{
	bool CableInterface::isActivated()
	{
		return this->_activated;
	}

	void CableInterface::setActivated(bool activated)
	{
		this->_activated = activated;
	}
}