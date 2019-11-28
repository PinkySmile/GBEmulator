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
	struct Sprite {
		unsigned char x;
		unsigned char y;
		unsigned char texture_id;
		union {
			struct {
				unsigned char cgb_palette_number:3;
				bool tile_bank:1;
				bool palette_number:1;
				bool x_flip:1;
				bool y_flip:1;
				bool priority:1;
			};
			unsigned char flags;
		};
	};

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
	protected:
		 std::vector<RGBColor> _BGColorPalette = {
			RGBColor::White,
			RGBColor::LGray,
			RGBColor::DGray,
			RGBColor::Black
		 };
		std::vector<RGBColor> _objectColorPalette0 = {
				RGBColor::White,
				RGBColor::LGray,
				RGBColor::DGray,
				RGBColor::Black
		};
		std::vector<RGBColor> _objectColorPalette1 = {
				RGBColor::White,
				RGBColor::LGray,
				RGBColor::DGray,
				RGBColor::Black
		};

	public:
		friend Debugger::Debugger;
		virtual void updateTexture(unsigned char *tile, size_t id) = 0;
		virtual void drawSprite(Sprite sprite, bool signedMode, bool doubleSize) = 0;
		virtual void drawBackground(const unsigned char *tiles, float x, float y, bool signedMode) = 0;
		virtual void drawWindow(const unsigned char *tiles, float x, float y, bool signedMode) = 0;
		virtual void display() = 0;
		virtual void clear() = 0;
		virtual bool isClosed() const = 0;
		virtual void close() = 0;

		void setBGPalette(const std::vector<RGBColor> &colors);
		void setBGPalette(unsigned char colors);
		void setObjectPalette0(const std::vector<RGBColor> &colors);
		void setObjectPalette0(unsigned char colors);
		void setObjectPalette1(const std::vector<RGBColor> &colors);
		void setObjectPalette1(unsigned char colors);
	};
}


#endif //GBEMULATOR_ILCD_HPP