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
			sf::Color     *_screen;
			std::string   _title;
			sf::Clock     _fpsClock;
			sf::Clock     _clock;
			sf::Texture   _texture;
			sf::View      _view;

			friend Debugger::Debugger;

		public:
			LCDSFML() = delete;
			LCDSFML(const LCDSFML &) = delete;
			~LCDSFML() override;
			LCDSFML &operator =(const LCDSFML &) = delete;
			LCDSFML(sf::VideoMode mode, const std::string &title);
			void display() override;
			void clear() override;
			void setMaxSize(unsigned int x, unsigned y);
			void setPixel(unsigned int x, unsigned y, const RGBColor &color);
			bool isClosed() const override;
			void close() override;
			double getFramerate();
		};
	}
}

#endif //GBEMULATOR_LCDSFML_HPP
