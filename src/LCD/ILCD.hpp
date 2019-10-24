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
				unsigned char cgb_palette_number:3;
				bool tile_bank:1;
				bool palette_number:1;
				bool y_flip:1;
				bool x_flip:1;
				bool priority:1;
			};
			unsigned char flags;
		};
	} Sprite;

	class ILCD {
	public:
		virtual void write(Sprite sprite) = 0;
		virtual void display() = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP