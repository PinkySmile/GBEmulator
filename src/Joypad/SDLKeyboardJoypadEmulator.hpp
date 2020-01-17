/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SDLKeyboardJoypadEmulator.hpp
*/
#ifndef GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP
#define GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP

#include <map>
#include "JoypadEmulator.hpp"
#include <SDL/SDL.h>

namespace GBEmulator::Input
{
	class SDLKeyboardJoypadEmulator : public JoypadEmulator {
	private:
		std::map<Keys, SDL_keysym> _keys;
		std::map<SDL_keysym, Keys> _rkeys;
		bool keyPressed[KEYS_LENGTH] = {false};

	public:
		SDLKeyboardJoypadEmulator() = delete;
		SDLKeyboardJoypadEmulator(const SDLKeyboardJoypadEmulator &) = delete;
		~SDLKeyboardJoypadEmulator() = default;
		SDLKeyboardJoypadEmulator &operator=(const SDLKeyboardJoypadEmulator &) = delete;
		explicit SDLKeyboardJoypadEmulator(const std::map<Keys, SDL_keysym> &&keys);
		void update();
		void setKeyValue(SDL_keysym keysym, bool value);
		void setKey(Keys button, SDL_keysym key);
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP
