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
#include <thread>
#include <SDL2/SDL.h>
#include "JoypadEmulator.hpp"
#include "../LCD/LCDSDL.hpp"

namespace GBEmulator::Input
{
	class SDLKeyboardJoypadEmulator : public JoypadEmulator {
	private:
		standard::map<Keys, SDL_Keycode> _keys;
		standard::unordered_map<SDL_Keycode, Keys> _rkeys;
		bool _keyPressed[KEYS_LENGTH] = {false, false, false, false, false, false, false, false, false};
		Graphics::LCDSDL &_screen;
		standard::thread _thread;
		bool _ended = false;

	public:
		SDLKeyboardJoypadEmulator() = delete;
		SDLKeyboardJoypadEmulator(const SDLKeyboardJoypadEmulator &) = delete;
		~SDLKeyboardJoypadEmulator();
		SDLKeyboardJoypadEmulator &operator=(const SDLKeyboardJoypadEmulator &) = delete;
		explicit SDLKeyboardJoypadEmulator(Graphics::LCDSDL &screen, const standard::map<Keys, SDL_Keycode> &&keys);
		void update();
		void setKeyValue(SDL_Keycode keysym, bool value);
		void setKey(Keys button, SDL_Keycode key);
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_SDLKEYBOARDJOYPADEMULATOR_HPP
