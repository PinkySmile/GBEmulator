/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.cpp
*/

#include <iostream>
#include "GPU.hpp"
#include "CPU.hpp"

namespace GBEmulator
{
	GPU::GPU(Graphics::ILCD &screen) :
		_vram(VRAM_SIZE, ROM_BANK_SIZE),
		_oam(OAM_SIZE, ROM_BANK_SIZE),
		_screen(screen)
	{
		unsigned char mushroom[] = {195, 195, 129, 189, 0, 126, 0, 126, 0, 0, 189, 189, 189, 189, 195, 195};
		for (int i = 0; i < 64; i++)
			_vram.write(i, mushroom[i]);
		_oam.write(0, 80);
		_oam.write(1, 72);
		_oam.write(2, 0);
		_oam.write(3, 160);
	}

	std::vector<int> GPU::getTile(std::size_t id) {
		std::vector<int> tile(64);

		for (int i = 0; i < 16; i += 2) {
			auto layer1 = this->_vram.read(i + id * 16);
			auto layer2 = this->_vram.read(i + id * 16 + 1);
			for (unsigned j = 0; j < 8; j++)
				tile[j + 4 * i] = (((1U << j & layer1) != 0) * 2) + ((1U << j & layer2) != 0);
		}
		return tile;
	}

	unsigned char GPU::readVRAM(unsigned short address) const {

		return _vram.read(address);
	}

	void GPU::writeVRAM(unsigned short address, unsigned char value) {
		_vram.write(address, value);
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
			for (int i = 0; i < 160; i += 4) {
				Graphics::Sprite sprite;
				sprite.x     = this->_oam.read(i);
				sprite.y     = this->_oam.read(i + 1);
				sprite.tile  = this->getTile(this->_oam.read(i + 2));
				sprite.flags = this->_oam.read(i + 3);
				this->_screen.write(sprite);
			this->_screen.display();
			}
		}
	}
}