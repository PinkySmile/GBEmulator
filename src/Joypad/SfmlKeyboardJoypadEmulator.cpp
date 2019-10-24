/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SfmlKeyboardJoypadEmulator.cpp
*/

#include "SfmlKeyboardJoypadEmulator.hpp"

namespace GBEmulator::Input
{
	SFMLKeyboardJoypadEmulator::SFMLKeyboardJoypadEmulator(const std::map<GBEmulator::Input::Keys, sf::Keyboard::Key> &&keys) :
		_keys(keys)
	{}

	void SFMLKeyboardJoypadEmulator::setKey(GBEmulator::Input::Keys button, sf::Keyboard::Key key)
	{
		this->_keys[button] = key;
	}

	bool SFMLKeyboardJoypadEmulator::isButtonPressed(GBEmulator::Input::Keys button) const noexcept
	{
		return sf::Keyboard::isKeyPressed(this->_keys.at(button));
	}
}