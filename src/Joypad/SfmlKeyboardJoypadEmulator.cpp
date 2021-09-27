/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SfmlKeyboardJoypadEmulator.cpp
*/

#include <SFML/Window/Joystick.hpp>
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
				//this->_state[JOYPAD_RIGHT] = sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50;
				//this->_state[JOYPAD_LEFT] = sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50;
				//this->_state[JOYPAD_UP] = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50;
				//this->_state[JOYPAD_DOWN] = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50;
				//this->_state[JOYPAD_A] = sf::Joystick::isButtonPressed(0, 1);
				//this->_state[JOYPAD_B] = sf::Joystick::isButtonPressed(0, 2);
				//this->_state[JOYPAD_SELECT] = sf::Joystick::isButtonPressed(0, 8);
				//this->_state[JOYPAD_START] = sf::Joystick::isButtonPressed(0, 9);
				//this->_state[RESET] = sf::Joystick::isButtonPressed(0, 0) && sf::Joystick::isButtonPressed(0, 3);
				//this->_state[ENABLE_DEBUGGING] = false;
				//this->_state[MENU] = sf::Joystick::isButtonPressed(0, 9) && sf::Joystick::isButtonPressed(0, 8);
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