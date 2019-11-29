/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.hpp
*/

#ifndef GBEMULATOR_LCDSFML_HPP
#define GBEMULATOR_LCDSFML_HPP

#include "ILCD.hpp"

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}
	namespace Graphics {
		class LCDSFML : public ILCD, public sf::RenderWindow {
		private:
			unsigned char *_tiles;
			sf::Color      *_screen;
			std::string    _title;
			sf::Clock      _fpsClock;
			sf::Clock      _clock;
			sf::Texture    _texture;

			void _drawTile(size_t id, int x, int y, bool swapX, bool swapY, const std::vector<RGBColor> &palette, bool transparency);

			friend Debugger::Debugger;

		public:
			LCDSFML() = delete;
			LCDSFML(const LCDSFML &) = delete;
			~LCDSFML() override;
			LCDSFML &operator =(const LCDSFML &) = delete;
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
		};
	}
}

#endif //GBEMULATOR_LCDSFML_HPP
