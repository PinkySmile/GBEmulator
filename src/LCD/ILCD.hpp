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
	typedef struct s_sprite {
		int x;
		int y;
		std::vector<int> tile;
		union {
			struct {
				bool priority:1;
				bool x_flip:1;
				bool y_flip:1;
				bool palette_number:1;
				bool tile_bank:1;
				unsigned char cgb_palette_number:3;
			};
			unsigned char flags;
		};
	} Sprite;

	class ILCD {
	public:
		std::vector<sf::Color> COLORS = {sf::Color::Black, sf::Color::Magenta, sf::Color::Green, sf::Color::White};

		virtual void write(Sprite sprite) = 0;
		virtual void display() = 0;

	private:
		virtual sf::Texture getTextureFromTile(std::vector<int> tile, bool forground) const = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP