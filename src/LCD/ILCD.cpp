/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ILCD.cpp
*/

#include <iostream>
#include "ILCD.hpp"

namespace GBEmulator::Graphics
{
	const RGBColor RGBColor::White{255, 255, 255};
	const RGBColor RGBColor::LGray{190, 190, 190};
	const RGBColor RGBColor::DGray{120, 120, 120};
	const RGBColor RGBColor::Black{0, 0, 0};

	RGBColor::RGBColor(unsigned char red, unsigned char green, unsigned char blue) noexcept :
		r(red),
		g(green),
		b(blue)
	{
	}

	RGBColor::RGBColor(unsigned short gbc_color) noexcept :
		r((gbc_color >> 0U)  & 0x1FU),
		g((gbc_color >> 5U)  & 0x1FU),
		b((gbc_color >> 10U) & 0x1FU)
	{
	}

	RGBColor::RGBColor(unsigned rgba_color) noexcept :
		r(rgba_color >> 24U),
		g(rgba_color >> 16U),
		b(rgba_color >> 8U)
	{
	}
}
