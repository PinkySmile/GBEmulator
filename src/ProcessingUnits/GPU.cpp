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
	GPU::GPU() : _vram(VRAM_SIZE, ROM_BANK_SIZE), _oam(OAM_SIZE, ROM_BANK_SIZE) {
		sf::RenderWindow window(sf::VideoMode(160, 144), "GPU Test");

		unsigned char mushroom[] = {195, 195, 129, 189, 0, 126, 0, 126, 0, 0, 189, 189, 189, 189, 195, 195};
		for (int i = 0; i < 64; i++)
			_vram.write(i, mushroom[i]);
		_oam.write(0, 80);
		_oam.write(1, 72);
		_oam.write(2, 0);
		_oam.write(3, 0);

		loadTextures();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();

			window.clear(sf::Color::White);

			window.draw(getSprite());

			window.display();
		}
	}

	std::vector<int> GPU::getTile(std::size_t id) {
		std::vector<int> tile(64);
		int k = 0;

		for (int i = id * 16; i < (id + 1) * 16; i += 2) {
			auto layer1 = decToBin(_vram.read(i));
			auto layer2 = decToBin(_vram.read(i + 1));
			for (int j = 0; j < 8; j++)
				tile[j + 4 * k] = (layer1[j] * 2) + layer2[j];
			k+=2;
		}
		return tile;
	}

	std::vector<int> GPU::decToBin(int nbr) {
		std::vector<int> result(8);

		for (int i = 0; i < 8; i++)
		{
			result[i] = nbr % 2;
			nbr = nbr / 2;
		}
		return result;
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

	sf::Sprite GPU::getSprite() {
		sf::Sprite sprite;

		float x = _oam.read(0);
		float y = _oam.read(1);
		int type = _oam.read(2);
		int flag = _oam.read(3);

		sprite.setTexture(_textures[type]);
		sprite.setPosition(x, y);

		return sprite;
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
		for (int i = 0; i < 256; i++)
			_textures.push_back(getTextureFromTile(getTile(i)));
	}
}