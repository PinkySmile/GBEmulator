/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SfmlKeyboardJoypadEmulator.hpp
*/

#ifndef GBEMULATOR_SFMLKEYBOARDJOYPADEMULATOR_HPP
#define GBEMULATOR_SFMLKEYBOARDJOYPADEMULATOR_HPP


#include <map>
#include <SFML/Window/Keyboard.hpp>
#include "JoypadEmulator.hpp"

namespace GBEmulator::Input
{
	class SFMLKeyboardJoypadEmulator : public JoypadEmulator {
	private:
		std::map<Keys, sf::Keyboard::Key> _keys;

	public:
		SFMLKeyboardJoypadEmulator() = delete;
		SFMLKeyboardJoypadEmulator(const SFMLKeyboardJoypadEmulator &) = delete;
		~SFMLKeyboardJoypadEmulator() = default;
		SFMLKeyboardJoypadEmulator &operator=(const SFMLKeyboardJoypadEmulator &) = delete;
		explicit SFMLKeyboardJoypadEmulator(const std::map<Keys, sf::Keyboard::Key> &&keys);

		//! Lie une touche du clavier à un bouton du Joypad
		void setKey(Keys button, sf::Keyboard::Key key);
		//! Renvoie True si le bouton donnée est appuyé
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_SFMLKEYBOARDJOYPADEMULATOR_HPP
