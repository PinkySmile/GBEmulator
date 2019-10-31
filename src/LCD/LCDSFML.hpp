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
		enum TextureType {
			Background,
			Palette0,
			Palette1
		};

	private:
		std::vector<sf::Texture> _BGTexture;
		std::vector<sf::Texture> _palette0Texture;
		std::vector<sf::Texture> _palette1Texture;
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
		void drawSprite(Sprite sprite, bool signedMode, bool doubleSize) override;
		void drawBackground(const unsigned char *tiles, float x, float y, bool signedMode) override;
		void drawWindow(const unsigned char *tiles, float x, float y, bool signedMode) override;
		void display() override;
		void clear() override;
		bool isClosed() const override;
		void close() override;
		double getFramerate();

	private:
		sf::Texture &_getTexture(unsigned char id, bool signedMode, TextureType type);
		void _getTextureFromTile(const unsigned char *tile, sf::Texture &texture, TextureType type) const;
	};
}

#endif //GBEMULATOR_LCDSFML_HPP
