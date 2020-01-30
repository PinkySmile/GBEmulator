/*
65;5803;1c** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.cpp
*/

#include <iostream>
#include <cstring>
#include <cmath>
#include "GPU.hpp"
#include "CPU.hpp"

#define DUCT_TAPE(value) ((((value) & 0b1U) << 1U) | ((value) >> 1U))

namespace GBEmulator
{
	const std::vector<Graphics::RGBColor> GPU::defaultColors{
		Graphics::RGBColor::White,
		Graphics::RGBColor::LGray,
		Graphics::RGBColor::DGray,
		Graphics::RGBColor::Black,
	};

	GPU::GPU(Graphics::ILCD &screen) :
		_oam(OAM_SIZE, OAM_SIZE),
		_screen(screen),
		_tiles(new unsigned char [NB_TILES]),
		_spritesMap(new unsigned char [256 * 256]),
		_backgroundMap(new unsigned char [BG_MAP_SIZE])
	{
		std::memset(this->_spritesMap, 0, 256 * 256);
		screen.setMaxSize(160, 144);
		screen.clear();
		screen.display();
		for (int i = 0; i < NB_TILES; i++)
			this->_tiles[i] = rand() & 0b11;
		for (int i = 0; i < BG_MAP_SIZE; i++)
			this->_backgroundMap[i] = rand() & 0xFF;
	}

	GPU::~GPU()
	{
		delete[] this->_tiles;
		delete[] this->_backgroundMap;
	}

	unsigned char GPU::readVRAM(unsigned short address) const
	{
		if (this->getMode() == 3)
			return 0xFF;

		if (address >= TILE_DATA_SIZE)
			return this->_backgroundMap[address - TILE_DATA_SIZE];

		unsigned tile = (address / 2) * 8;

		if (address % 2 == 0)
			return (
			       ((this->_tiles[tile    ] & 0b10U) << 6U) |
			       ((this->_tiles[tile + 1] & 0b10U) << 5U) |
			       ((this->_tiles[tile + 2] & 0b10U) << 4U) |
			       ((this->_tiles[tile + 3] & 0b10U) << 3U) |
			       ((this->_tiles[tile + 4] & 0b10U) << 2U) |
			       ((this->_tiles[tile + 5] & 0b10U) << 1U) |
			       ((this->_tiles[tile + 6] & 0b10U) << 0U) |
			       ((this->_tiles[tile + 7] & 0b10U) >> 1U)
			);

		return (
		       ((this->_tiles[tile    ] & 0b01U) << 7U) |
		       ((this->_tiles[tile + 1] & 0b01U) << 6U) |
		       ((this->_tiles[tile + 2] & 0b01U) << 5U) |
		       ((this->_tiles[tile + 3] & 0b01U) << 4U) |
		       ((this->_tiles[tile + 4] & 0b01U) << 3U) |
		       ((this->_tiles[tile + 5] & 0b01U) << 2U) |
		       ((this->_tiles[tile + 6] & 0b01U) << 1U) |
		       ((this->_tiles[tile + 7] & 0b01U) << 0U)
		);
	}

	void GPU::writeVRAM(unsigned short address, unsigned char value)
	{
		if (this->getMode() == 3)
			return;

		if (address >= TILE_DATA_SIZE) {
			this->_backgroundMap[address - TILE_DATA_SIZE] = value;
			return;
		}

		unsigned tile = (address / 2) * 8;

		if (address % 2 == 0)
			for (unsigned i = 0; i < 8; i++) {
				this->_tiles[tile + i] &= 0b01U;
				this->_tiles[tile + i] |= (value >> (7U - i) & 1U) << 1U;
			}
		else
			for (unsigned i = 0; i < 8; i++) {
				this->_tiles[tile + i] &= 0b10U;
				this->_tiles[tile + i] |= value >> (7U - i) & 1U;
			}
		if (std::find(this->_tilesToUpdate.begin(), this->_tilesToUpdate.end(), address / 16) == this->_tilesToUpdate.end())
			this->_tilesToUpdate.push_back(address / 16);
	}

	unsigned char GPU::readOAM(unsigned short address) const
	{
		if (this->getMode() >= 2)
			return 0xFF;

		return _oam.read(address);
	}

	void GPU::writeOAM(unsigned short address, unsigned char value)
	{
		if (this->getMode() >= 2)
			return;

		this->_oam.write(address, value);
	}

	unsigned char GPU::_getPixelAt(const unsigned char *tile, unsigned int x, unsigned int y)
	{
		return tile[x + y * 8];
	}

	unsigned char GPU::_getPixelAt(const unsigned char *tiles, unsigned int x, unsigned int y, bool signedMode)
	{
		int id = static_cast<int>(x / 8 % 32) + 32 * static_cast<int>(y / 8 % 32);

		if (id < 0 || id > 1024)
			return 0;

		const unsigned char *tile = this->_tiles + (signedMode ? static_cast<char>(tiles[id]) + 0x100 : tiles[id]) * 64;

		return tile[x % 8 + (y % 8) * 8];
	}

	unsigned char GPU::_getSpritePixel(const Sprite &sprite, unsigned int x, unsigned int y)
	{
		return this->_tiles[sprite.texture_id * 64 + x + y * 8];
	}

	void GPU::_drawPixel(unsigned x, unsigned y)
	{
		unsigned char color = 0;
		bool bgZero = false;

		if (this->_control & 0b00000001U) {
			unsigned char val = this->_getPixelAt(
				this->_getTileMap(this->_control & 0b00001000U),
				x + this->_scrollX,
				y + this->_scrollY,
				!(this->_control & 0b00010000U)
			);

			color = (this->_bgPaletteValue >> DUCT_TAPE(val) * 2) & 0b11U;
			bgZero = val == 0;
		}

		if (
			(this->_control & 0b00100000U) &&
			static_cast<int>(x) - this->_windowX >= 0 &&
			static_cast<int>(x) - this->_windowX < 160 &&
			static_cast<int>(y) - this->_windowY >= 0
		) {
			unsigned val = this->_getPixelAt(
				this->_getTileMap(this->_control & 0b01000000U),
				x - this->_windowX,
				y - this->_windowY,
				!(this->_control & 0b00010000U)
			);

			color = (this->_bgPaletteValue >> DUCT_TAPE(val) * 2) & 0b11U;
		}

		if (this->_control & 0b00000010U && this->_spritesMap[x + y * 256] < 8)
			if (((this->_spritesMap[x + y * 256] & 0b100) == 0) || bgZero)
				color = this->_spritesMap[x + y * 256] & 0b11U;

		this->_screen.setPixel(x, y, defaultColors[color]);
	}

	void GPU::updateOAM()
	{
		std::memset(this->_spritesMap, 0xFF, 256 * 256);

		unsigned char v = 8 * (1 + ((this->_control & 0b00000100U) != 0));

		for (int i = 0; i < OAM_SIZE; i += 4) {
			Sprite sprite;

			sprite.y = this->_oam.read(i) - 16;
			sprite.x = this->_oam.read(i + 1) - 8;
			sprite.texture_id = this->_oam.read(i + 2);
			sprite.flags = this->_oam.read(i + 3);

			unsigned char *tile = this->_tiles + sprite.texture_id * 64;

			for (int x = 0; x < 8; x += 1) {
				for (int y = 0; y < v; y += 1) {
					int realX = ((sprite.x_flip ? 7 - x : x) + sprite.x) % 256;
					int realY = ((sprite.y_flip ? v - 1 - y : y) + sprite.y) % 256;

					if (realX < 160 && realY < 144) {
						unsigned char newColor = DUCT_TAPE(tile[x + y * 8]);
						unsigned char palette = sprite.palette_number == 0 ? this->_objectPalette0Value : this->_objectPalette1Value;

						if (newColor)
							this->_spritesMap[realX + realY * 256] = ((palette >> (newColor * 2U)) & 0b11U) | (sprite.priority * 0b100);
					}
				}
			}
		}
	}

	void GPU::update()
	{
		if ((this->_control & 0x80U) == 0)
			return;

		if (this->_cycles == VBLANK_CYCLE_PT) {
			this->_screen.display();
			this->_screen.clear();
		} else if (this->_cycles % DEVIDER == 0 && (this->_control & 0b00000010U)) {
			this->updateOAM();
		} else if (this->getMode() == 3)
			this->_drawPixel(this->_cycles % DEVIDER - (DEVIDER - 373), this->getCurrentLine());

		this->_cycles++;

		if (this->_cycles > GPU_FULL_CYCLE_DURATION)
			this->_cycles = 0;
	}

	unsigned char GPU::update(int cycle)
	{
		while (cycle-- > 0)
			this->update();

		if (this->_isVBlankInterrupt()) {
			if (this->_isStatInterrupt())
				return CPU::VBLANK_INTERRUPT | CPU::LCD_STAT_INTERRUPT;
			return CPU::VBLANK_INTERRUPT;
		} else if (this->_isStatInterrupt())
			return CPU::LCD_STAT_INTERRUPT;
		return 0;
	}

	unsigned char GPU::getCurrentLine() const
	{
		return this->_cycles * 153 / GPU_FULL_CYCLE_DURATION;
	}

	void GPU::setControlByte(unsigned char value)
	{
		if ((this->_control & 0x80U) == 0x80 && (value & 0x80U) == 0)
			this->_cycles = 0;
		this->_control = value;
	}

	unsigned char GPU::getControlByte() const
	{
		return this->_control;
	}

	unsigned char GPU::getXScroll() const
	{
		return this->_scrollX;
	}

	unsigned char GPU::getYScroll() const
	{
		return this->_scrollY;
	}

	void GPU::setXScroll(unsigned char value)
	{
		this->_scrollX = value;
	}

	void GPU::setYScroll(unsigned char value)
	{
		this->_scrollY = value;
	}

	unsigned char *GPU::_getTileMap(bool alt)
	{
		if (alt)
			return this->_backgroundMap + 0x400;
		return this->_backgroundMap;
	}

	unsigned char *GPU::_getTile(std::size_t id)
	{
		return this->_tiles + id * 64;
	}

	unsigned char GPU::getStatByte() const
	{
		return (this->_stat & 0b01111000U) | 0x80U | ((this->getCurrentLine() == this->_lyc && (this->_control & 0x80U)) << 2U) | this->getMode();
	}

	void GPU::setStatByte(unsigned char value)
	{
		//TODO: Implement the quirk that sometimes triggers interrupts when writing
		this->_stat = value;
	}

	bool GPU::_isVBlankInterrupt()
	{
		bool needInterrupt = this->getMode() == 1;
		bool trigger = !this->_triggeredVBlankInterrupt && needInterrupt;

		this->_triggeredVBlankInterrupt = needInterrupt;
		return trigger;
	}

	unsigned char GPU::getMode() const
	{
		if ((this->_control & 0x80U) == 0)
			return 0;
		if (this->getCurrentLine() >= 144)
			return 1;
		if (this->_cycles % DEVIDER < DEVIDER - 373)
			return 2;
		if (this->_cycles % DEVIDER < DEVIDER - 213)
			return 3;
		return 0;
	}

	bool GPU::_isStatInterrupt()
	{
		bool needInterrupt = (this->_control & 0x80U) && (
			((this->_stat & 0b01000000U) && this->_lyc == this->getCurrentLine()) ||
			((this->_stat & 0b00100000U) && this->getMode() == 2) ||
			((this->_stat & 0b00010000U) && this->getMode() == 1) ||
			((this->_stat & 0b00001000U) && !this->getMode())
		);
		bool trigger = !this->_triggeredStatInterrupt && needInterrupt;

		this->_triggeredStatInterrupt = needInterrupt;
		return trigger;
	}

	unsigned char GPU::getLycByte() const
	{
		return this->_lyc;
	}

	void GPU::setLycByte(unsigned char value)
	{
		this->_lyc = value;
	}

	void GPU::setWindowX(unsigned char value)
	{
		this->_windowX = value - 7;
	}

	unsigned char GPU::getWindowX() const {

		return this->_windowX + 7;
	}

	void GPU::setWindowY(unsigned char value)
	{
		this->_windowY = value;
	}

	unsigned char GPU::getWindowY() const {

		return this->_windowY;
	}

	unsigned char GPU::getBGPalette() const
	{
		return this->_bgPaletteValue;
	}

	unsigned char GPU::getObjectPalette0() const {

		return this->_objectPalette0Value;
	}

	unsigned char GPU::getObjectPalette1() const {

		return this->_objectPalette1Value;
	}

	void GPU::setBGPalette(unsigned char value)
	{
		if (this->_bgPaletteValue != value)
			for (unsigned i = 0; i < 4; i++)
				this->_bgPalette[i] = defaultColors[((value >> (i * 2))) & 0b11U];
		this->_bgPaletteValue = value;
	}

	void GPU::setObjectPalette0(unsigned char value)
	{
		if (this->_objectPalette0Value != value)
			for (unsigned i = 0; i < 4; i++)
				this->_objectPalette0[i] = defaultColors[((value >> (i * 2))) & 0b11U];
		this->_objectPalette0Value = value;
	}

	void GPU::setObjectPalette1(unsigned char value)
	{
		if (this->_objectPalette1Value != value)
			for (unsigned i = 0; i < 4; i++)
				this->_objectPalette1[i] = defaultColors[((value >> (i * 2))) & 0b11U];
		this->_objectPalette1Value = value;
	}
}
