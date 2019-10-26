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

namespace GBEmulator::Graphics
{
	struct Sprite {
		unsigned char x;
		unsigned char y;
		unsigned char texture_id;
		union {
			struct {
				unsigned char cgb_palette_number:3;
				bool tile_bank:1;
				bool palette_number:1;
				bool y_flip:1;
				bool x_flip:1;
				bool priority:1;
			};
			unsigned char flags;
		};
	};

	class ILCD {
	private:
		unsigned char _screenColor = 0;

	public:
		virtual void setColor(unsigned char color);
		virtual void updateTexture(unsigned char *tile, size_t id) = 0;
		virtual void drawSprite(Sprite sprite, bool signedMode) = 0;
		virtual void drawBackground(const unsigned char *tiles, float x, float y, bool signedMode) = 0;
		virtual void drawWindow(const unsigned char *tiles, float x, float y, bool signedMode) = 0;
		virtual void display() = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP