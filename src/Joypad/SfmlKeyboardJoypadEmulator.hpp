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
#include <thread>
#include "JoypadEmulator.hpp"

namespace GBEmulator::Input
{
	//! @brief Implémentation du JoypadEmulator pour un clavier en utilisant la SFML.
	class SFMLKeyboardJoypadEmulator : public JoypadEmulator {
	private:
		//! @brief Touches configurées.
		std::map<Keys, sf::Keyboard::Key> _keys;
		//! @brief Fenêtre liée au joypad.
		sf::RenderWindow &_window;
		bool _end;
		std::vector<bool> _state;
		std::thread _thread;

	public:
		/*!
		 * Constructeur.
		 * @param window Fenêtre liée au joypad.
		 * @param keys Touches configurées.
		 */
		explicit SFMLKeyboardJoypadEmulator(sf::RenderWindow &window, const std::map<Keys, sf::Keyboard::Key> &&keys);
		~SFMLKeyboardJoypadEmulator() override;

		/*!
		 * Lie une touche du clavier à un bouton du Joypad
		 * @param button Boutton à changer la valeur.
		 * @param key Nouvelle touche à assigner.
		 */
		void setKey(Keys button, sf::Keyboard::Key key);
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_SFMLKEYBOARDJOYPADEMULATOR_HPP
