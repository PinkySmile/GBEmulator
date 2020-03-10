/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SfmlKeyboardJoypadEmulator.cpp
*/

#include "SfmlKeyboardJoypadEmulator.hpp"

namespace GBEmulator::Input
{
	SFMLKeyboardJoypadEmulator::SFMLKeyboardJoypadEmulator(sf::RenderWindow &window, const std::map<GBEmulator::Input::Keys, sf::Keyboard::Key> &&keys) :
		_keys(keys),
		_window(window),
		_end(false),
		_state(NB_KEYS, false),
		_thread([this]{
			while (!this->_end) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				for (auto &data : this->_keys)
					this->_state[data.first] = this->_window.hasFocus() && sf::Keyboard::isKeyPressed(data.second);
			}
		})
	{
	}

	SFMLKeyboardJoypadEmulator::~SFMLKeyboardJoypadEmulator()
	{
		this->_end = true;
		if (this->_thread.joinable())
			this->_thread.join();
	}

	void SFMLKeyboardJoypadEmulator::setKey(GBEmulator::Input::Keys button, sf::Keyboard::Key key)
	{
		this->_keys[button] = key;
	}

	bool SFMLKeyboardJoypadEmulator::isButtonPressed(GBEmulator::Input::Keys button) const noexcept
	{
		return this->_state[button];
	}
}