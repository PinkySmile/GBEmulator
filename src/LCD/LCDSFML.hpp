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
		sf::Color _colors[4] = {sf::Color::Black, sf::Color::Magenta, sf::Color::Green, sf::Color::White};
		std::vector<sf::Texture> _texture;
		sf::Sprite _sprite;
		std::string _title;
		sf::Clock _fpsClock;
		sf::Clock _clock;

	public:
		LCDSFML() = delete;
		LCDSFML(const LCDSFML &) = delete;
		~LCDSFML() override = default;
		LCDSFML &operator=(const LCDSFML &) = delete;
		LCDSFML(sf::VideoMode mode, const std::string &title);
		void updateTexture(unsigned char *tile, size_t id) override;
		void drawSprite(Sprite sprite) override;
		void display() override;
		double getFramerate();

	private:
		void _getTextureFromTile(unsigned char *tile, sf::Texture &texture) const;
	};
}

#endif //GBEMULATOR_LCDSFML_HPP
