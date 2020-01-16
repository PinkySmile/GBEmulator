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
#include <SFML/Graphics/RenderWindow.hpp>
#include "JoypadEmulator.hpp"

namespace GBEmulator::Input
{
	class SFMLKeyboardJoypadEmulator : public JoypadEmulator {
	private:
		std::map<Keys, sf::Keyboard::Key> _keys;
		sf::RenderWindow &_window;

	public:
		SFMLKeyboardJoypadEmulator() = delete;
		SFMLKeyboardJoypadEmulator(const SFMLKeyboardJoypadEmulator &) = delete;
		~SFMLKeyboardJoypadEmulator() = default;
		SFMLKeyboardJoypadEmulator &operator=(const SFMLKeyboardJoypadEmulator &) = delete;
		explicit SFMLKeyboardJoypadEmulator(sf::RenderWindow &window, const std::map<Keys, sf::Keyboard::Key> &&keys);

		void setKey(Keys button, sf::Keyboard::Key key);
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_SFMLKEYBOARDJOYPADEMULATOR_HPP
