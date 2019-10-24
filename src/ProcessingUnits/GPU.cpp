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
	GPU::GPU(sf::RenderWindow &screen) :
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
		_oam.write(3, 0);

		loadTextures();
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

	sf::Texture GPU::getTextureFromTile(std::vector<int> tile) {
		sf::Texture texture;
		auto *pixels = new sf::Uint8[8 * 8 * 4];

		texture.create(8, 8);
		for (int i = 0; i < 64; i++) {
			pixels[0 + i * 4] = this->COLORS[tile[i]].r;
			pixels[1 + i * 4] = this->COLORS[tile[i]].g;
			pixels[2 + i * 4] = this->COLORS[tile[i]].b;
			pixels[3 + i * 4] = this->COLORS[tile[i]].a;
		}
		texture.update(pixels);
		delete[] pixels;
		return texture;
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

	void GPU::loadTextures() {
		this->_textures.clear();
		for (int i = 0; i < 256; i++)
			this->_textures.push_back(getTextureFromTile(getTile(i)));
	}

	void GPU::update(int cycle) {
		this->_cycles += cycle;
		if (this->_cycles > 500) {
			this->_cycles -= 500;
			auto sprites = _getSprites();
			for (auto &sprite : sprites)
				_screen.draw(sprite);
			this->_screen.display();
		}
	}

	std::vector<sf::Sprite> GPU::_getSprites() {
		sf::Sprite sprite;
		std::vector<sf::Sprite> sprites;

		for (int i = 0; i < 160; i += 4) {
			int flag = _oam.read(i + 3);

			sprite.setTexture(this->_textures.at(this->_oam.read(i + 2)), true);
			sprite.setPosition(this->_oam.read(i), this->_oam.read(i + 1));
			sprites.push_back(sprite);
		}
		return sprites;
	}
}