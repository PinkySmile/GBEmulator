/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SDLKeyboardJoypadEmulator.cpp
*/

#include "SDLKeyboardJoypadEmulator.hpp"

namespace GBEmulator::Input
{
	SDLKeyboardJoypadEmulator::SDLKeyboardJoypadEmulator(Graphics::LCDSDL &screen, const standard::map<GBEmulator::Input::Keys, SDL_KeyCode> &&keys) :
		_keys(keys),
		_screen(screen),
		_thread([this]{
			while (!this->_ended)
				this->update();
		})
	{
		for (standard::pair<GBEmulator::Input::Keys, SDL_KeyCode> i : this->_keys)
			this->_rkeys[i.second] = i.first;
	}

	SDLKeyboardJoypadEmulator::~SDLKeyboardJoypadEmulator()
	{
		this->_ended = true;
		if (this->_thread.joinable())
			this->_thread.join();
	}

	void SDLKeyboardJoypadEmulator::setKey(GBEmulator::Input::Keys button, SDL_KeyCode key)
	{
		this->_keys[button] = key;
		this->_rkeys.clear();
		for (standard::pair<GBEmulator::Input::Keys, SDL_KeyCode> i : this->_keys)
			this->_rkeys[i.second] = i.first;
	}

	void SDLKeyboardJoypadEmulator::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				this->setKeyValue(static_cast<SDL_KeyCode>(event.key.keysym.sym), true);
				break;
			case SDL_KEYUP:
				this->setKeyValue(static_cast<SDL_KeyCode>(event.key.keysym.sym), false);
				break;
			case SDL_QUIT:
			case SDL_WINDOWEVENT_CLOSE:
				this->_screen.close();
				this->_ended = true;
				break;
			default:
				break;
			}
		}
	}

	void SDLKeyboardJoypadEmulator::setKeyValue(SDL_KeyCode keysym, bool value) {
		try {
			Keys button = this->_rkeys.at(keysym);
			this->_keyPressed[button] = value;
		} catch (standard::exception &e) {}
	}

	bool SDLKeyboardJoypadEmulator::isButtonPressed(GBEmulator::Input::Keys button) const noexcept
	{
		return this->_keyPressed[button];
	}
}