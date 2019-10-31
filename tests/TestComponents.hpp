/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestComponents.hpp
*/
#ifndef GBEMULATOR_TESTCOMPONENTS_HPP
#define GBEMULATOR_TESTCOMPONENTS_HPP

#include "../src/Joypad/JoypadEmulator.hpp"

namespace Tests {
	enum Keys {
		JOYPAD_RIGHT,
		JOYPAD_LEFT,
		JOYPAD_UP,
		JOYPAD_DOWN,
		JOYPAD_A,
		JOYPAD_B,
		JOYPAD_SELECT,
		JOYPAD_START,
		ENABLE_DEBUGGING,
	};

	class Joypad : public GBEmulator::Input::JoypadEmulator {
	private:
		bool _rt_value;
	public:
		Joypad(bool return_value=false);
		bool isButtonPressed(Keys button) const noexcept;
	};

	class Screen {
	public:

	};
}


#endif //GBEMULATOR_TESTCOMPONENTS_HPP
