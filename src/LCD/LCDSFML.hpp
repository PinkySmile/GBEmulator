/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.hpp
*/

#ifndef GBEMULATOR_LCDSFML_HPP
#define GBEMULATOR_LCDSFML_HPP

#include "ILCD.hpp"

namespace GBEmulator::Graphics
{
	class LCDSFML : public ILCD, public sf::RenderWindow {
	private:
		std::vector<sf::Color> _colors = {sf::Color::Black, sf::Color::Magenta, sf::Color::Green, sf::Color::White};
		std::vector<sf::Texture> _texture;
		std::vector<sf::Sprite> _forground;
		std::vector<sf::Sprite> _background;

	public:
		LCDSFML(sf::VideoMode mode, const std::string &title);
		void write(Sprite sprite) override;
		void display() override;

	private:
		sf::Texture getTextureFromTile(std::vector<int> tile, bool forground) const;
	};
}

#endif //GBEMULATOR_LCDSFML_HPP
