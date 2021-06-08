/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** RaspberryJoypadEmulator.cpp
*/

#include <iostream>
#include <wiringPi.h>
#include "RaspberryJoypadEmulator.hpp"

namespace GBEmulator::Input
{
	RaspberryJoypadEmulator::RaspberryJoypadEmulator(const standard::map<GBEmulator::Input::Keys, uint8_t> &&keys) :
		_keys(keys)
	{
		if (wiringPiSetupGpio() == -1) {
                        std::cout << "Setup wiring pi failed" << std::endl;
                        abort();
                }
		for (auto pin : this->_keys)
			pinMode(pin.second, INPUT);
	}

	bool RaspberryJoypadEmulator::isButtonPressed(GBEmulator::Input::Keys button) const noexcept
	{
		auto it = this->_keys.find(button);

		if (it == this->_keys.end() || it->second == -1)
			return false;
		return digitalRead(it->second) == HIGH;
	}
}
