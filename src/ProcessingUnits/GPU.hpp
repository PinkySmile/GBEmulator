/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.hpp
*/

#ifndef GBEMULATOR_GPU_HPP
#define GBEMULATOR_GPU_HPP

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "../Memory/Memory.hpp"
#include "../LCD/ILCD.hpp"

#define TILE_DATA_SIZE 0x1800
#define NB_TILES TILE_DATA_SIZE * 4
#define BG_MAP_SIZE 0x800
#define OAM_SIZE 0xA0
#define GPU_FULL_CYCLE_DURATION 70224
#define VBLANK_CYCLE_PT 66093
#define HBLANK_CYLCE_PT

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}

	class GPU {
	private:
		bool _triggeredStatInterrupt = false;
		bool _triggeredVBlankInterrupt = false;
		Memory::Memory _oam;
		Graphics::ILCD &_screen;
		unsigned char _scrollX = 0;
		unsigned char _scrollY = 0;
		signed short _windowX = 0;
		unsigned char _windowY = 0;
		unsigned char _bgPaletteValue = 0b00011011;
		unsigned char _objectPalette0Value = 0b00011011;
		unsigned char _objectPalette1Value = 0b00011011;
		std::vector<Graphics::RGBColor> _bgPalette{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};;
		std::vector<Graphics::RGBColor> _objectPalette0{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};
		std::vector<Graphics::RGBColor> _objectPalette1{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};;
		unsigned char _stat = 0;
		unsigned char _lyc = 0;
		unsigned char _control = 0;
		unsigned char *_tiles = nullptr;
		unsigned char *_spritesMap = nullptr;
		unsigned char *_backgroundMap = nullptr;
		unsigned _cycles = 0;
		std::vector<unsigned> _tilesToUpdate;

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

		void _drawPixel(unsigned x, unsigned y);
		unsigned char _getSpritePixel(const Sprite &sprite, unsigned int x, unsigned int y);
		unsigned char _getPixelAt(const unsigned char *tile, unsigned int x, unsigned int y);
		unsigned char _getPixelAt(const unsigned char *tiles, unsigned int x, unsigned int y, bool signedMode);

	public:
		GPU(Graphics::ILCD &screen);
		~GPU();
		GPU() = delete;
		GPU(const GPU &) = delete;
		GPU &operator=(const GPU &) = delete;

		static const std::vector<Graphics::RGBColor> defaultColors;
		unsigned char getMode() const;
		unsigned char getCurrentLine() const;
		unsigned char readVRAM(unsigned short address) const;
		unsigned char readOAM(unsigned short address) const;
		unsigned char getControlByte() const;
		unsigned char getBGPalette() const;
		unsigned char getXScroll() const;
		unsigned char getYScroll() const;
		unsigned char getStatByte() const;
		unsigned char getLycByte() const;
		unsigned char getWindowX() const;
		unsigned char getWindowY() const;
		unsigned char getObjectPalette0() const;
		unsigned char getObjectPalette1() const;

		void updateOAM();
		void writeVRAM(unsigned short address, unsigned char value);
		void writeOAM(unsigned short address, unsigned char value);
		void setControlByte(unsigned char value);
		void setStatByte(unsigned char value);
		void setBGPalette(unsigned char value);
		void setXScroll(unsigned char value);
		void setYScroll(unsigned char value);
		void setLycByte(unsigned char value);
		void setWindowX(unsigned char value);
		void setWindowY(unsigned char value);
		void setObjectPalette0(unsigned char value);
		void setObjectPalette1(unsigned char value);

		unsigned char update(int cycle);
		void update();

	private:
		friend Debugger::Debugger;
		unsigned char *_getTile(std::size_t id);
		unsigned char *_getTileMap(bool alt);

		//Interrupts
		bool _isVBlankInterrupt();
		bool _isStatInterrupt();
	};
}


#endif //GBEMULATOR_GPU_HPP
