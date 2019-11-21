/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.cpp
*/

#include <iostream>
#include <cstring>
#include "GPU.hpp"
#include "CPU.hpp"

namespace GBEmulator
{
	GPU::GPU(Graphics::ILCD &screen) :
		_oam(OAM_SIZE, OAM_SIZE),
		_screen(screen),
		_tiles(new unsigned char [NB_TILES]),
		_backgroundMap(new unsigned char [BG_MAP_SIZE])
	{
		screen.clear();
		screen.display();
		for (int i = 0; i < NB_TILES; i++)
			this->_tiles[i] = rand() & 0b11;
		for (int i = 0; i < BG_MAP_SIZE; i++)
			this->_backgroundMap[i] = rand() & 0xFF;

		for (int i = 0; i < 256; i++)
			this->_screen.updateTexture(this->_getTile(i), i);
	}

	GPU::~GPU()
	{
		delete[] this->_tiles;
		delete[] this->_backgroundMap;
	}

	unsigned char GPU::getBGPalette() const
	{
		return this->_bgPalette;
	}

	void GPU::setBGPalette(unsigned char value)
	{
		this->_paletteChanged = this->_paletteChanged || this->_bgPalette != value;
		this->_bgPalette = value;
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

	unsigned char GPU::update(int cycle)
	{
		static int buf = 0;

		this->_cycles += cycle;
		buf += cycle;
		if (this->_control & 0x80U) {
			buf = 0;
			if (this->_cycles > GPU_FULL_CYCLE_DURATION) {
				this->_cycles -= GPU_FULL_CYCLE_DURATION;
				this->_screen.clear();

				if (this->_paletteChanged) {
					this->_screen.setBGPalette(this->_bgPalette);
					this->_screen.setObjectPalette0(this->_objectPalette0);
					this->_screen.setObjectPalette1(this->_objectPalette1);
					this->_paletteChanged = false;
				}
				this->_updateTiles();

				if (this->_control & 0b00000001U)
					this->_screen.drawBackground(this->_getTileMap(this->_control & 0b00001000U), -this->_scrollX, -this->_scrollY, !(this->_control & 0b00010000U));

				if (this->_control & 0b00100000U)
					this->_screen.drawWindow(this->_getTileMap(this->_control & 0b01000000U), this->_windowX, this->_windowY, !(this->_control & 0b00010000U));

				for (int i = 0; i < OAM_SIZE && (this->_control & 0b00000010U); i += 4) {
					Graphics::Sprite sprite;

					sprite.x = this->_oam.read(i);
					sprite.y = this->_oam.read(i + 1);
					sprite.texture_id = this->_oam.read(i + 2);
					sprite.flags = this->_oam.read(i + 3);
					this->_screen.drawSprite(sprite, false, this->_control & 0b00000100U);
				}
				this->_screen.display();
			}
		} else
			this->_cycles = 0;

		if (buf > 30000) {
			this->_screen.clear();
			this->_screen.display();
			buf = 0;
		}

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
		if ((this->_control & 0x80U) == 0 && (value & 0x80U))
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

	void GPU::_updateTiles()
	{
		if (this->_paletteChanged) {
			for (int i = 0; i < 384; i++)
				this->_screen.updateTexture(this->_getTile(i), i);
		} else
			for (auto &id : this->_tilesToUpdate)
				this->_screen.updateTexture(this->_getTile(id), id);
		this->_tilesToUpdate.clear();
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
		return (this->_stat & 0b01111000U) | 0x80U | (this->getCurrentLine() == this->_lyc) << 2U | this->getMode();
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
		if ((this->_control & 0x80U) == 0 || this->getCurrentLine() >= 144)
			return 1;
		if (this->_cycles % 456 < 83)
			return 2;
		if (this->_cycles % 456 < 258)
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

		return this->_windowX;
	}

	void GPU::setWindowY(unsigned char value)
	{
		this->_windowY = value;
	}

	unsigned char GPU::getWindowY() const {

		return this->_windowY;
	}

	unsigned char GPU::getObjectPalette0() const {

		return this->_objectPalette0;
	}

	unsigned char GPU::getObjectPalette1() const {

		return this->_objectPalette1;
	}

	void GPU::setObjectPalette0(unsigned char value)
	{
		this->_paletteChanged = this->_paletteChanged || this->_objectPalette0 != value;
		this->_objectPalette0 = value;
	}

	void GPU::setObjectPalette1(unsigned char value)
	{
		this->_paletteChanged = this->_paletteChanged || this->_objectPalette0 != value;
		this->_objectPalette1 = value;
	}
}