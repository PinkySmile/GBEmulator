/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** JoypadEmulator.hpp
*/

#ifndef GBEMULATOR_JOYPADEMULATOR_HPP
#define GBEMULATOR_JOYPADEMULATOR_HPP


namespace GBEmulator::Input
{
	enum Keys {
		JOYPAD_RIGHT,
		JOYPAD_LEFT,
		JOYPAD_UP,
		JOYPAD_DOWN,
		JOYPAD_A,
		JOYPAD_B,
		JOYPAD_SELECT,
		JOYPAD_START
	};

	class JoypadEmulator {
	public:
		virtual bool isButtonPressed(Keys button) const noexcept = 0;
	};
}


#endif //GBEMULATOR_JOYPADEMULATOR_HPP
