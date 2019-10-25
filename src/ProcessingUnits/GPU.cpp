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
		_tiles(new unsigned char [VRAM_SIZE * 4])
	{
		std::memset(this->_tiles, 0xFF, VRAM_SIZE * 4 * sizeof(*this->_tiles));
		unsigned char mushroom[] = {195, 195, 129, 189, 0, 126, 0, 126, 0, 0, 189, 189, 189, 189, 195, 195};
		for (int i = 0; i < 64; i++)
			this->writeVRAM(i, mushroom[i]);
		_oam.write(0, 80);
		_oam.write(1, 72);
		_oam.write(2, 0);
		_oam.write(3, 0);

		for (int i = 0; i < 256; i++)
			this->_screen.updateTexture(this->_getTile(i), i);
	}

	GPU::~GPU() {
		delete[] this->_tiles;
	}

	unsigned char *GPU::_getTile(std::size_t id) {
		return this->_tiles + id * 64;
	}

	unsigned char GPU::readVRAM(unsigned short address) const {
		unsigned tile = (address / 2) * 8;

		if (address % 2 == 0)
			return (
					(this->_tiles[tile    ] & 0b10U << 6U) |
					(this->_tiles[tile + 1] & 0b10U << 5U) |
					(this->_tiles[tile + 2] & 0b10U << 4U) |
					(this->_tiles[tile + 3] & 0b10U << 3U) |
					(this->_tiles[tile + 4] & 0b10U << 2U) |
					(this->_tiles[tile + 5] & 0b10U << 1U) |
					(this->_tiles[tile + 6] & 0b10U << 0U) |
					(this->_tiles[tile + 7] & 0b10U >> 1U)
			);

		return (
				(this->_tiles[tile    ] & 0b01U << 7U) |
				(this->_tiles[tile + 1] & 0b01U << 6U) |
				(this->_tiles[tile + 2] & 0b01U << 5U) |
				(this->_tiles[tile + 3] & 0b01U << 4U) |
				(this->_tiles[tile + 4] & 0b01U << 3U) |
				(this->_tiles[tile + 5] & 0b01U << 2U) |
				(this->_tiles[tile + 6] & 0b01U << 1U) |
				(this->_tiles[tile + 7] & 0b01U << 0U)
		);
	}

	void GPU::writeVRAM(unsigned short address, unsigned char value) {
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

	unsigned char GPU::readOAM(unsigned short address) const {

		return _oam.read(address);
	}

	void GPU::writeOAM(unsigned short address, unsigned char value) {
		_oam.write(address, value);
	}

	void GPU::update(int cycle) {

		this->_cycles += cycle;
		if (this->_cycles > 500) {
			this->_cycles -= 500;
			this->_updateTiles();
			for (int i = 0; i < 160; i += 4) {
				Graphics::Sprite sprite{};
				sprite.x     = this->_oam.read(i);
				sprite.y     = this->_oam.read(i + 1);
				sprite.texture_id = this->_oam.read(i + 2);
				sprite.flags = this->_oam.read(i + 3);
				this->_screen.drawSprite(sprite);
			}
			this->_screen.display();
		}
	}

	unsigned char GPU::readIOPorts(unsigned short) const {
		return 0xff;
	}

	void GPU::writeIOPorts(unsigned short, unsigned char) {
		//if (address == LCD_BG_COLOR)
		//	this->_screen.setColor(value);
		//this->_screen.writeIOPorts(address, value);
	}

	void GPU::_updateTiles() {
		for (auto &id : this->_tilesToUpdate)
			this->_screen.updateTexture(this->_getTile(id), id);
		this->_tilesToUpdate.clear();
	}
}