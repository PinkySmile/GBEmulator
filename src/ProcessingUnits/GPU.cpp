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
		std::memset(this->_tiles, 0xFF, NB_TILES * sizeof(*this->_tiles));

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
		this->_bgPalette = value;
	}

	unsigned char GPU::readVRAM(unsigned short address) const
	{
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
		return _oam.read(address);
	}

	void GPU::writeOAM(unsigned short address, unsigned char value)
	{
		this->_oam.write(address, value);
	}

	unsigned char GPU::update(int cycle)
	{
		unsigned char line = this->getCurrentLine();

		this->_cycles += cycle;
		if (this->_cycles > GPU_FULL_CYCLE_DURATION) {
			this->_cycles -= GPU_FULL_CYCLE_DURATION;
			this->_screen.clear();

			if (this->_control & 0x80U) {
				this->_screen.setPalette(this->_bgPalette);
				this->_updateTiles();

				if (this->_control & 0b00000001U)
					this->_screen.drawBackground(this->_getTileMap(this->_control & 0b00001000U), -this->_scrollY, -this->_scrollX, !(this->_control & 0b00010000U));

				if (this->_control & 0b00100000U)
					this->_screen.drawWindow(this->_getTileMap(this->_control & 0b01000000U), !(this->_control & 0b00010000U));

				for (int i = 0; i < OAM_SIZE && (this->_control & 0b00000010U); i += 4) {
					Graphics::Sprite sprite;

					sprite.x = this->_oam.read(i);
					sprite.y = this->_oam.read(i + 1);
					sprite.texture_id = this->_oam.read(i + 2);
					sprite.flags = this->_oam.read(i + 3);
					this->_screen.drawSprite(sprite, false, this->_control & 0b00000100U);
				}
			}
			this->_screen.display();
		}
		return CPU::VBLANK_INTERRUPT * (line == 143 && this->getCurrentLine() == 144);
	}

	unsigned char GPU::getCurrentLine() const
	{
		return this->_cycles * 153 / GPU_FULL_CYCLE_DURATION;
	}

	void GPU::setControlByte(unsigned char value)
	{
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

	void GPU::_updateTiles() {
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
}