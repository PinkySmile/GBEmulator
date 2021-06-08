/*
65;5803;1c** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.cpp
*/

#ifndef ARDUINO
#include <cstring>
#include <algorithm>
#else
#include <string.h>
#include "../ArduinoStuff/Algorithm.h"
#endif
#undef _stat
#include "GPU.hpp"
#include "CPU.hpp"

#define DUCT_TAPE(value) ((((value) & 0b1U) << 1U) | ((value) >> 1U))

namespace GBEmulator
{
	Graphics::RGBColor GPU::defaultColors[4] = {
		{255, 255, 255},
		{190, 190, 190},
		{120, 120, 120},
		{0,   0,   0},
	};

	GPU::GPU(Graphics::ILCD &screen) :
		_oam(OAM_SIZE, OAM_SIZE),
		_screen(screen)
	{
		this->_bgpd.resize(0x40, 0x7FFF);
		this->_obpd.resize(0x40);
#ifdef ARDUINO
		this->_spritesMap = new uint8_t *[256];
		for (int i = 0; i < 256; i++) {
			this->_spritesMap[i] = new uint8_t [256];
			memset(this->_spritesMap[i], 0, 256);
		}
#else
		this->_spritesMap = new uint8_t[256 * 256];
		memset(this->_spritesMap, 0, 256 * 256);
#endif
		screen.setMaxSize(160, 144);
		screen.clear();
		screen.display();

		this->_tiles = new uint8_t *[NB_VRAM_BANK];
		for (int j = 0; j < NB_VRAM_BANK; j++) {
			this->_tiles[j] = new uint8_t[NB_TILES];
			for (int i = 0; i < NB_TILES; i++)
				this->_tiles[j][i] = rand() & 0b11U;
			memset(this->_tiles[j], 0, NB_TILES);
		}

		this->_backgroundMap = new uint8_t *[NB_VRAM_BANK];
		for (int j = 0; j < NB_VRAM_BANK; j++) {
			this->_backgroundMap[j] = new uint8_t[BG_MAP_SIZE];
			for (int i = 0; i < BG_MAP_SIZE; i++)
				this->_backgroundMap[j][i] = rand() & 0xFFU;
		}

		for (int i = 0; i < 0x40; i++)
			this->_obpd[i] = rand() & 0x7FFFU;
	}

	GPU::~GPU()
	{
		for (int i = 0; i < NB_VRAM_BANK; i++)
			delete[] this->_tiles[i];
		delete[] this->_tiles;
#ifdef ARDUINO
		for (int i = 0; i < 256; i++)
			delete[] this->_spritesMap[i];
#endif
		delete[] this->_spritesMap;
		delete[] this->_backgroundMap;
	}

	uint8_t GPU::readVRAM(uint16_t address) const
	{
		if (this->getMode() == 3)
			return 0xFF;

		if (address >= TILE_DATA_SIZE)
			return this->_backgroundMap[this->_vramBankSwitch][address - TILE_DATA_SIZE];

		unsigned tile = (address / 2) * 8;

		if (address % 2 == 0)
			return (
			       ((this->_tiles[this->_vramBankSwitch][tile    ] & 0b10U) << 6U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 1] & 0b10U) << 5U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 2] & 0b10U) << 4U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 3] & 0b10U) << 3U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 4] & 0b10U) << 2U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 5] & 0b10U) << 1U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 6] & 0b10U) << 0U) |
			       ((this->_tiles[this->_vramBankSwitch][tile + 7] & 0b10U) >> 1U)
			);

		return (
		       ((this->_tiles[this->_vramBankSwitch][tile    ] & 0b01U) << 7U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 1] & 0b01U) << 6U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 2] & 0b01U) << 5U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 3] & 0b01U) << 4U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 4] & 0b01U) << 3U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 5] & 0b01U) << 2U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 6] & 0b01U) << 1U) |
		       ((this->_tiles[this->_vramBankSwitch][tile + 7] & 0b01U) << 0U)
		);
	}

	void GPU::writeVRAM(uint16_t address, uint8_t value)
	{
		if (this->getMode() == 3)
			return;

		if (address >= TILE_DATA_SIZE) {
			this->_backgroundMap[this->_vramBankSwitch][address - TILE_DATA_SIZE] = value;
			return;
		}

		unsigned tile = (address / 2) * 8;

		if (address % 2 == 0)
			for (unsigned i = 0; i < 8; i++) {
				this->_tiles[this->_vramBankSwitch][tile + i] &= 0b01U;
				this->_tiles[this->_vramBankSwitch][tile + i] |= (value >> (7U - i) & 1U) << 1U;
			}
		else
			for (unsigned i = 0; i < 8; i++) {
				this->_tiles[this->_vramBankSwitch][tile + i] &= 0b10U;
				this->_tiles[this->_vramBankSwitch][tile + i] |= value >> (7U - i) & 1U;
			}
		if (standard::find(this->_tilesToUpdate.begin(), this->_tilesToUpdate.end(), address / 16) == this->_tilesToUpdate.end())
			this->_tilesToUpdate.push_back(address / 16);
	}

	uint8_t GPU::readOAM(uint16_t address) const
	{
		if (this->getMode() >= 2)
			return 0xFF;

		return _oam.read(address);
	}

	void GPU::writeOAM(uint16_t address, uint8_t value)
	{
		if (this->getMode() >= 2)
			return;

		this->_oam.write(address, value);
	}

	uint8_t GPU::readBGPD(uint16_t address) const
	{
		if (address % 2)
			return this->_bgpd[address / 2] >> 8U;
		return this->_bgpd[address / 2] & 0xFFU;
	}

	void GPU::writeBGPD(uint16_t address, uint8_t value)
	{
		if (address % 2)
			this->_bgpd[address / 2] = (this->_bgpd[address / 2] & 0x00FFU) | (value << 8U);
		else
			this->_bgpd[address / 2] = (this->_bgpd[address / 2] & 0xFF00U) | value;
	}

	uint8_t GPU::readOBPD(uint16_t address) const
	{
		if (address % 2)
			return this->_obpd[address / 2] >> 8U;
		return this->_obpd[address / 2] & 0xFFU;
	}

	void GPU::writeOBPD(uint16_t address, uint8_t value)
	{
		if (address % 2)
			this->_obpd[address / 2] = (this->_obpd[address / 2] & 0x00FFU) | (value << 8U);
		else
			this->_obpd[address / 2] = (this->_obpd[address / 2] & 0xFF00U) | value;
	}

	uint8_t GPU::_getPixelAt(const uint8_t *tiles, unsigned int x, unsigned int y, bool signedMode, bool flipped_x, bool flipped_y, bool bank)
	{
		int id = static_cast<int>(x / 8 % 32) + 32 * static_cast<int>(y / 8 % 32);

		if (id < 0 || id > 1024)
			return 0;

		const uint8_t *tile = this->_tiles[bank] + (signedMode ? static_cast<int8_t>(tiles[id]) + 0x100 : tiles[id]) * 64;
		unsigned int realX = (flipped_x ? 7 - (x % 8) : (x % 8));
		unsigned int realY = (flipped_y ? 7 - (y % 8) : (y % 8));

		return tile[realX + realY * 8];
	}

	uint8_t GPU::_getSpritePixel(const Sprite &sprite, unsigned int x, unsigned int y)
	{
		return this->_tiles[this->_vramBankSwitch][sprite.texture_id * 64 + x + y * 8];
	}

	void GPU::_drawPixel(unsigned x, unsigned y)
	{
		uint8_t color = 0;
		uint8_t paletteIndex = 0;
		bool bgZero = false;
		bool bgPriority = false;

		if (this->_control.bgDisplayEnabled || !this->_gbMode) {
			int id = static_cast<int>((x + this->_scrollX) / 8 % 32) + 32 * static_cast<int>((y + this->_scrollY) / 8 % 32);
			auto bgData = reinterpret_cast<BGData*>(&this->_getTileMap(1, this->_control.bgTileMapSelect)[id]);
			uint8_t val = this->_getPixelAt(
				this->_getTileMap(0, this->_control.bgTileMapSelect),
				x + this->_scrollX,
				y + this->_scrollY,
				!this->_control.bgAndWindowTileDataSelect,
				bgData->x_flip && !this->_gbMode,
				bgData->y_flip && !this->_gbMode,
				bgData->tile_bank && !this->_gbMode
			);

			bgPriority = bgData->priority && !this->_gbMode;
			if (this->_gbMode)
				color = (this->_bgPaletteValue >> DUCT_TAPE(val) * 2) & 0b11U;
			else {
				paletteIndex = bgData->palette + 1;
				color = DUCT_TAPE(val) & 0b11U;
			}
			bgZero = val == 0;
		}

		if (
			this->_control.windowEnabled &&
			static_cast<int>(x) - this->_windowX >= 0 &&
			static_cast<int>(x) - this->_windowX < 160 &&
			static_cast<int>(y) - this->_windowY >= 0
		) {
			int id = static_cast<int>((x - this->_windowX) / 8 % 32) + 32 * static_cast<int>((y - this->_windowY) / 8 % 32);
			auto bgData = reinterpret_cast<BGData*>(&this->_getTileMap(1, this->_control.windowTileMapSelect)[id]);
			unsigned val = this->_getPixelAt(
				this->_getTileMap(0, this->_control.windowTileMapSelect),
				x - this->_windowX,
				y - this->_windowY,
				!this->_control.bgAndWindowTileDataSelect,
				bgData->x_flip && !this->_gbMode,
				bgData->y_flip && !this->_gbMode,
				bgData->tile_bank && !this->_gbMode
			);

			if (this->_gbMode)
				color = (this->_bgPaletteValue >> DUCT_TAPE(val) * 2) & 0b11U;
			else {
				paletteIndex = bgData->palette + 1;
				color = DUCT_TAPE(val) & 0b11U;
			}
		}

#ifdef ARDUINO
		if (!(this->_spritesMap[y][x] & 0x80))
			if (((this->_spritesMap[y][x] & 0b100U) == 0 && (this->_control.bgDisplayEnabled || this->_gbMode) && !bgPriority) || bgZero) {
				color = this->_spritesMap[y][x] & 0b11U;
				if (!this->_gbMode)
					paletteIndex = ((this->_spritesMap[y][x] & 0b111000U) >> 3U) + 9;
			}
#else
		if (!(this->_spritesMap[x + y * 256] & 0x80))
			if (((this->_spritesMap[x + y * 256] & 0b100U) == 0 && (this->_control.bgDisplayEnabled || this->_gbMode) && !bgPriority) || bgZero) {
				color = this->_spritesMap[x + y * 256] & 0b11U;
				if (!this->_gbMode)
					paletteIndex = ((this->_spritesMap[x + y * 256] & 0b111000U) >> 3U) + 9;
			}
#endif

		if (paletteIndex > 8)
			this->_screen.setPixel(x, y, Graphics::RGBColor(this->_obpd[(paletteIndex - 9) * 4 + color]));
		else if (paletteIndex > 0)
			this->_screen.setPixel(x, y, Graphics::RGBColor(this->_bgpd[(paletteIndex - 1) * 4 + color]));
		else
			this->_screen.setPixel(x, y, defaultColors[color]);
	}

	struct sss {
		GPU::Sprite sprite;
		unsigned index;
	};

#if ARDUINO
	bool cmpFct(const sss *s1, const sss *s2)
	{
		if (s1->sprite.x == s2->sprite.x)
			return s1->index > s2->index;
		return s1->sprite.x < s2->sprite.x;
	}
#endif

	void GPU::updateOAM(unsigned int line)
	{
		unsigned nbPixels = 0;
		uint8_t v = 8 * (1 + this->_control.spriteSizeSelect);
		sss sprites[OAM_SIZE / 4];
		auto buf = reinterpret_cast<Sprite *>(this->_oam.getBuffer());

		for (unsigned i = 0; i < OAM_SIZE / 4; i++) {
			sprites[i].index = i;
			sprites[i].sprite = buf[i];
		}
#ifdef ARDUINO
		qsort(sprites, OAM_SIZE / 4, sizeof(sss), reinterpret_cast<int (*)(const void *, const void *)>(cmpFct));
#else
		standard::sort(sprites, sprites + OAM_SIZE / 4, [](sss &s1, sss &s2){
			if (s1.sprite.x == s2.sprite.x)
				return s1.index > s2.index;
			return s1.sprite.x < s2.sprite.x;
		});
#endif
		for (auto &sprite : sprites) {
			if (nbPixels == 80)
				break;
			if (sprite.sprite.x == 0 || sprite.sprite.x >= 168 || sprite.sprite.y == 0 || sprite.sprite.y >= 160)
				continue;

			sprite.sprite.y -= 16;
			sprite.sprite.x -= 8;

			if (this->_control.spriteSizeSelect)
				sprite.sprite.texture_id &= 0xFEU;

			for (int x = 0; x < 8; x += 1) {
				for (int y = 0; y < v; y += 1) {
					int realX = ((sprite.sprite.x_flip ? 7 - x : x) + sprite.sprite.x) % 256;
					int realY = ((sprite.sprite.y_flip ? v - 1 - y : y) + sprite.sprite.y) % 256;

					if (static_cast<unsigned>(realY) == line/*< 144*/) {
						uint8_t val = (this->_tiles[sprite.sprite.tile_bank] + sprite.sprite.texture_id * 64)[x + y * 8];
						uint8_t newColor = DUCT_TAPE(val);
						uint8_t palette = sprite.sprite.palette_number == 0 ? this->_objectPalette0Value : this->_objectPalette1Value;

#ifdef ARDUINO
						if (newColor && !this->_gbMode)
							this->_spritesMap[realY][realX] = newColor | (sprite.sprite.priority * 0b100) | (sprite.sprite.cgb_palette_number << 3U);
						else if (newColor)
							this->_spritesMap[realY][realX] = ((palette >> (newColor * 2U)) & 0b11U) | (sprite.sprite.priority * 0b100);
#else
						if (newColor && !this->_gbMode)
							this->_spritesMap[realX + realY * 256] = newColor | (sprite.sprite.priority * 0b100) | (sprite.sprite.cgb_palette_number << 3U);
						else if (newColor)
							this->_spritesMap[realX + realY * 256] = ((palette >> (newColor * 2U)) & 0b11U) | (sprite.sprite.priority * 0b100);
#endif
						nbPixels += newColor != 0;
					}
				}
			}
		}
	}

	void GPU::update(CPU &cpu)
	{
		if (!this->_control.enabled)
			return;

		if (this->_cycles == 0) {
#ifdef ARDUINO
			for (int i = 0; i < 256; i++)
				memset(this->_spritesMap[i], 0xFF, 256);
#else
			memset(this->_spritesMap, 0xFF, 256 * 256);
#endif
		} else if (this->_cycles == VBLANK_CYCLE_PT) {
			this->_screen.display();
			this->_screen.clear();
		} else if (this->_cycles % DEVIDER == 0 && this->_control.spriteDisplayEnabled)
			this->updateOAM(this->_cycles / DEVIDER);
		else if (this->getMode() == 3)
			this->_drawPixel(this->_cycles % DEVIDER - (DEVIDER - 373), this->getCurrentLine());
		else if ((this->_cycles % DEVIDER == DEVIDER - 213) && this->_isTransferring) {
			for (uint8_t i = 0; i < 16; i++) {
				this->writeVRAM(this->_HDMADest, cpu.read(this->_HDMASrc));
				this->_transfertLen--;
				this->_HDMADest++;
				this->_HDMASrc++;
			}
			this->_isTransferring = this->_transfertLen;
		}


		this->_cycles++;

		if (this->_cycles > GPU_FULL_CYCLE_DURATION)
			this->_cycles = 0;
	}

	bool GPU::isTransfering() const
	{
		return this->_isTransferring;
	}

	uint8_t GPU::update(CPU &cpu, long cycle)
	{
		while (cycle-- > 0)
			this->update(cpu);

		if (this->_isVBlankInterrupt()) {
			if (this->_isStatInterrupt())
				return CPU::VBLANK_INTERRUPT | CPU::LCD_STAT_INTERRUPT;
			return CPU::VBLANK_INTERRUPT;
		} else if (this->_isStatInterrupt())
			return CPU::LCD_STAT_INTERRUPT;
		return 0;
	}

	uint8_t GPU::getCurrentLine() const
	{
		return this->_cycles / DEVIDER;
	}

	void GPU::setControlByte(uint8_t value)
	{
		if (this->_control.enabled && (value & 0x80U) == 0)
			this->_cycles = 0;
		this->_control = *reinterpret_cast<const ControlByte *>(&value);
	}

	uint8_t GPU::getControlByte() const
	{
		return *reinterpret_cast<const uint8_t *>(&this->_control);
	}

	uint8_t GPU::getXScroll() const
	{
		return this->_scrollX;
	}

	uint8_t GPU::getYScroll() const
	{
		return this->_scrollY;
	}

	void GPU::setXScroll(uint8_t value)
	{
		this->_scrollX = value;
	}

	void GPU::setYScroll(uint8_t value)
	{
		this->_scrollY = value;
	}

	uint8_t *GPU::_getTileMap(uint8_t bank, bool alt)
	{
		if (alt)
			return this->_backgroundMap[bank] + 0x400;
		return this->_backgroundMap[bank];
	}

	uint8_t GPU::getStatByte() const
	{
		return (this->_stat & 0b01111000U) | 0x80U | ((this->getCurrentLine() == this->_lyc && this->_control.enabled) << 2U) | this->getMode();
	}

	void GPU::setStatByte(uint8_t value)
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

	uint8_t GPU::getMode() const
	{
		if (!this->_control.enabled)
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
		bool needInterrupt = this->_control.enabled && (
			((this->_stat & 0b01000000U) && this->_lyc == this->getCurrentLine()) ||
			((this->_stat & 0b00100000U) && this->getMode() == 2) ||
			((this->_stat & 0b00010000U) && this->getMode() == 1) ||
			((this->_stat & 0b00001000U) && !this->getMode())
		);
		bool trigger = !this->_triggeredStatInterrupt && needInterrupt;

		this->_triggeredStatInterrupt = needInterrupt;
		return trigger;
	}

	uint8_t GPU::getLycByte() const
	{
		return this->_lyc;
	}

	void GPU::setLycByte(uint8_t value)
	{
		this->_lyc = value;
	}

	void GPU::setWindowX(uint8_t value)
	{
		this->_windowX = value - 7;
	}

	uint8_t GPU::getWindowX() const
	{
		return this->_windowX + 7;
	}

	void GPU::setWindowY(uint8_t value)
	{
		this->_windowY = value;
	}

	uint8_t GPU::getWindowY() const
	{
		return this->_windowY;
	}

	uint8_t GPU::getBGPalette() const
	{
		return this->_bgPaletteValue;
	}

	uint8_t GPU::getObjectPalette0() const
	{
		return this->_objectPalette0Value;
	}

	uint8_t GPU::getObjectPalette1() const
	{
		return this->_objectPalette1Value;
	}

	void GPU::setBGPalette(uint8_t value)
	{
		if (this->_bgPaletteValue != value)
			for (unsigned i = 0; i < 4; i++)
				this->_bgPalette[i] = defaultColors[((value >> (i * 2))) & 0b11U];
		this->_bgPaletteValue = value;
	}

	void GPU::setObjectPalette0(uint8_t value)
	{
		if (this->_objectPalette0Value != value)
			for (unsigned i = 0; i < 4; i++)
				this->_objectPalette0[i] = defaultColors[((value >> (i * 2))) & 0b11U];
		this->_objectPalette0Value = value;
	}

	void GPU::setObjectPalette1(uint8_t value)
	{
		if (this->_objectPalette1Value != value)
			for (unsigned i = 0; i < 4; i++)
				this->_objectPalette1[i] = defaultColors[((value >> (i * 2))) & 0b11U];
		this->_objectPalette1Value = value;
	}

	bool GPU::getVBK() const
	{
		return this->_vramBankSwitch;
	}

	void GPU::setVBK(bool value)
	{
		if (this->_gbMode)
			return;

		this->_vramBankSwitch = value & 0b1U;
	}

	void GPU::startHDMA(uint16_t len, uint16_t src, uint16_t dest)
	{
		if (this->_gbMode)
			return;

		this->_HDMASrc = src;
		this->_HDMADest = dest & 0x1FFFU;
		this->_transfertLen = len;
		this->_isTransferring = true;
	}

	uint16_t GPU::getTransferLength() const
	{
		return this->_transfertLen;
	}

	void GPU::setToGBMode(bool isGb)
	{
		this->_gbMode = isGb;

		if (isGb) {
			this->_vramBankSwitch = false;
			this->_isTransferring = false;
		}
	}
}
