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

	void ILCD::setBGPalette(const std::vector<RGBColor> &colors) {
		this->_BGColorPalette = colors;
	}

	void ILCD::setBGPalette(unsigned char colors) {
		for (unsigned i = 0; i < 4; i++) {
			switch (((colors >> (i * 2))) & 0b11U) {
				case 0b00:
					this->_BGColorPalette[i] = RGBColor::White;
					break;
				case 0b01:
					this->_BGColorPalette[i] = RGBColor::LGray;
					break;
				case 0b10:
					this->_BGColorPalette[i] = RGBColor::DGray;
					break;
				default:
					this->_BGColorPalette[i] = RGBColor::Black;
			}
		}
	}

	void ILCD::setObjectPalette0(const std::vector<RGBColor> &colors) {
		this->_objectColorPalette0 = colors;
	}

	void ILCD::setObjectPalette0(unsigned char colors) {
		for (unsigned i = 0; i < 4; i++) {
			switch (((colors >> (i * 2))) & 0b11U) {
				case 0b00:
					this->_objectColorPalette0[i] = RGBColor::White;
					break;
				case 0b01:
					this->_objectColorPalette0[i] = RGBColor::LGray;
					break;
				case 0b10:
					this->_objectColorPalette0[i] = RGBColor::DGray;
					break;
				default:
					this->_objectColorPalette0[i] = RGBColor::Black;
			}
		}
	}

	void ILCD::setObjectPalette1(const std::vector<RGBColor> &colors) {
		this->_objectColorPalette1 = colors;
	}

	void ILCD::setObjectPalette1(unsigned char colors) {
		for (unsigned i = 0; i < 4; i++) {
			switch (((colors >> (i * 2))) & 0b11U) {
				case 0b00:
					this->_objectColorPalette1[i] = RGBColor::White;
					break;
				case 0b01:
					this->_objectColorPalette1[i] = RGBColor::LGray;
					break;
				case 0b10:
					this->_objectColorPalette1[i] = RGBColor::DGray;
					break;
				default:
					this->_objectColorPalette1[i] = RGBColor::Black;
			}
		}
	}
}
