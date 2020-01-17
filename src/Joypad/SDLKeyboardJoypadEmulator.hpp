/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SDLKeyboardJoypadEmulator.hpp
*/
#ifndef GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP
#define GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP

#include <unordered_map>
#include <map>
#include "JoypadEmulator.hpp"
#include <SDL/SDL.h>

namespace GBEmulator::Input
{
	class SDLKeyboardJoypadEmulator : public JoypadEmulator {
	private:
		std::map<Keys, SDLKey> _keys;
		std::unordered_map<SDLKey, Keys> _rkeys;
		bool keyPressed[KEYS_LENGTH] = {false};

	public:
		SDLKeyboardJoypadEmulator() = delete;
		SDLKeyboardJoypadEmulator(const SDLKeyboardJoypadEmulator &) = delete;
		~SDLKeyboardJoypadEmulator() = default;
		SDLKeyboardJoypadEmulator &operator=(const SDLKeyboardJoypadEmulator &) = delete;
		explicit SDLKeyboardJoypadEmulator(const std::map<Keys, SDLKey> &&keys);
		void update();
		void setKeyValue(SDLKey keysym, bool value);
		void setKey(Keys button, SDLKey key);
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP
