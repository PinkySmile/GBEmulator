/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ILCD.cpp
*/

#include "ILCD.hpp"

namespace GBEmulator::Graphics
{
	const RGBColor RGBColor::White{200, 200, 200};
	const RGBColor RGBColor::LGray{150, 150, 150};
	const RGBColor RGBColor::DGray{50, 50, 50};
	const RGBColor RGBColor::Black{0, 0, 0};

	void ILCD::setPalette(const std::vector<GBEmulator::Graphics::RGBColor> &colors)
	{
		this->_colorPalette = colors;
	}

	void ILCD::setPalette(unsigned char colors)
	{
		for (unsigned i = 0; i < 4; i++) {
			switch (((colors >> (i * 2))) & 0b11U) {
			case 0b00:
				this->_colorPalette[i] = RGBColor::White;
				break;
			case 0b01:
				this->_colorPalette[i] = RGBColor::LGray;
				break;
			case 0b10:
				this->_colorPalette[i] = RGBColor::DGray;
				break;
			default:
				this->_colorPalette[i] = RGBColor::Black;
			}
		}
	}
}
