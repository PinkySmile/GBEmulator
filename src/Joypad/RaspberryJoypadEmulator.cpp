/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** RaspberryJoypadEmulator.cpp
*/

#include <wiringPi.h>
#include "RaspberryJoypadEmulator.hpp"

namespace GBEmulator::Input
{
	RaspberryJoypadEmulator::RaspberryJoypadEmulator(const standard::map<GBEmulator::Input::Keys, uint8_t> &&keys) :
		_keys(keys)
	{
		for (auto pin : this->_keys)
			pinMode(pin.second, INPUT);
	}

	bool RaspberryJoypadEmulator::isButtonPressed(GBEmulator::Input::Keys button) const noexcept
	{
		return digitalRead(this->_keys[button]) == HIGH;
	}
}