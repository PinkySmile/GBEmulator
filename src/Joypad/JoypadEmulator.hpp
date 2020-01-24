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
	//! @brief Enumeration des touches possibles.
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

	//! @brief Emulateur du Joypad de la GameBoy.
	class JoypadEmulator {
	public:
		/*!
		 * Vérifie si un bouton est appuyé.
		 * @param button La Keys à verifier.
		 * @return True si la touche est enfoncée. Sinon, false.
		 */
		virtual bool isButtonPressed(Keys button) const noexcept = 0;
	};
}


#endif //GBEMULATOR_JOYPADEMULATOR_HPP
