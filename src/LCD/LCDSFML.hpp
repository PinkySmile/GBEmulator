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
		sf::Sprite _sprite;

	public:
		LCDSFML(sf::VideoMode mode, const std::string &title);
		void updateTexture(unsigned char *tile, size_t id) override;
		void drawSprite(Sprite sprite) override;
		void display() override;

	private:
		void _getTextureFromTile(unsigned char *tile, sf::Texture &texture) const;
	};
}

#endif //GBEMULATOR_LCDSFML_HPP
