/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SDLKeyboardJoypadEmulator.cpp
*/

#include "SDLKeyboardJoypadEmulator.hpp"

namespace GBEmulator::Input {
	SDLKeyboardJoypadEmulator::SDLKeyboardJoypadEmulator(const std::map<GBEmulator::Input::Keys, SDLKey> &&keys):
	_keys(keys)
	{
		for (std::pair<GBEmulator::Input::Keys, SDLKey> i : this->_keys)
			this->_rkeys[i.second] = i.first;
	}

	void SDLKeyboardJoypadEmulator::setKey(GBEmulator::Input::Keys button, SDLKey key)
	{
		this->_keys[button] = key;
		this->_rkeys.clear();
		for (std::pair<GBEmulator::Input::Keys, SDLKey> i : this->_keys)
			this->_rkeys[i.second] = i.first;
	}

	void SDLKeyboardJoypadEmulator::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				this->setKeyValue(event.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				this->setKeyValue(event.key.keysym.sym, false);
				break;
			default:
				break;
			}
		}
	}

	void SDLKeyboardJoypadEmulator::setKeyValue(SDLKey keysym, bool value) {
		try {
			Keys button = this->_rkeys.at(keysym);
			this->keyPressed[button] = value;
		}
		catch (std::exception &e) {}
	}

	bool SDLKeyboardJoypadEmulator::isButtonPressed(GBEmulator::Input::Keys button) const noexcept
	{
		return this->keyPressed[button];
	}
}