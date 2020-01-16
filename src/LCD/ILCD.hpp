/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ILCD.hpp
*/

#ifndef GBEMULATOR_ILCD_HPP
#define GBEMULATOR_ILCD_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace GBEmulator::Debugger {
	class Debugger;
}

namespace GBEmulator::Graphics
{
	struct RGBColor {
		static const struct GBEmulator::Graphics::RGBColor White;
		static const struct GBEmulator::Graphics::RGBColor LGray;
		static const struct GBEmulator::Graphics::RGBColor DGray;
		static const struct GBEmulator::Graphics::RGBColor Black;

		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	class ILCD {
	public:
		friend Debugger::Debugger;
		virtual void setMaxSize(unsigned int x, unsigned y) = 0;
		virtual void setPixel(unsigned int x, unsigned y, const RGBColor &color) = 0;
		virtual void display() = 0;
		virtual void clear() = 0;
		virtual bool isClosed() const = 0;
		virtual void close() = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP