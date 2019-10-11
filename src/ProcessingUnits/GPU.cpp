/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GPU.hpp"
#include "CPU.hpp"

#define VRAM_SIZE 8 * 1024
#define OAM_SIZE 159

namespace GBEmulator
{
	GPU::GPU() : _vram(VRAM_SIZE, 0), _oam(OAM_SIZE, ROM_BANK_SIZE) {
		sf::RenderWindow window(sf::VideoMode(160 * 4, 144 * 4), "GPU Test");
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<sf::Color> colors;
		colors.push_back(sf::Color::Black);
		colors.push_back(sf::Color::Magenta);
		colors.push_back(sf::Color::Green);
		colors.push_back(sf::Color::White);

		unsigned char mushroom[] = {195, 195, 129, 189, 0, 126, 0, 126, 0, 0, 189, 189, 189, 189, 195, 195};
		for (int i = 0; i < 16; i++)
			_vram.write(i, mushroom[i]);
		_oam.write(0, 80);
		_oam.write(1, 72);
		_oam.write(2, 0);
		_oam.write(3, 0);

		auto *pixels = new sf::Uint8[8 * 8 * 4];

		auto tile = getTile(0);
		for (int i = 0; i < 64; i++) {
			pixels[0 + i * 4] = colors[tile[i]].r;
			pixels[1 + i * 4] = colors[tile[i]].g;
			pixels[2 + i * 4] = colors[tile[i]].b;
			pixels[3 + i * 4] = colors[tile[i]].a;
		}

		texture.create(8, 8);
		texture.update(pixels);

		sprite.setTexture(texture);
		sprite.setPosition(80 * 4, 72* 4);
		sprite.setScale(6, 6);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();
			window.clear(sf::Color::White);

			window.draw(sprite);

			window.display();
		}
	}

	std::vector<int> GPU::getTile(std::size_t id) {
		std::vector<int> tile(64);

		for (int i = id; i < id + 16; i += 2) {
			auto layer1 = decToBin(_vram.read(i));
			auto layer2 = decToBin(_vram.read(i + 1));

			for (int j = 0; j < 8; j++)
				tile[j + 4 * i] = (layer1[j] * 2) + layer2[j];
		}

		int k = 1;
		for (int i = 0; i < 64; i++) {
			std::cout << tile[i];
			if (k == 8) {
				std::cout << std::endl;
				k = 0;
			}
			k++;
		}
		std::cout << std::endl;
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
}