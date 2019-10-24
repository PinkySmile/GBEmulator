/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.hpp
*/

#ifndef GBEMULATOR_GPU_HPP
#define GBEMULATOR_GPU_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Memory/Memory.hpp"

namespace GBEmulator
{
	#define VRAM_SIZE 8 * 1024
	#define OAM_SIZE 159

	class GPU {
		std::vector<sf::Color> COLORS = {sf::Color::Black, sf::Color::Magenta, sf::Color::Green, sf::Color::White};

	private:
		Memory _vram;
		Memory _oam;
		sf::RenderWindow &_screen;
		std::vector<sf::Texture> _textures;

	public:
		GPU(sf::RenderWindow &screen);
		unsigned char readVRAM(unsigned short address) const;
		void writeVRAM(unsigned short address, unsigned char value);
		unsigned char readOAM(unsigned short address) const;
		void writeOAM(unsigned short address, unsigned char value);
		void update(int cycle);

	private:
		unsigned _cycles;

		std::vector<int> getTile(std::size_t id);
		std::vector<int> decToBin(int nbr);
		sf::Texture getTextureFromTile(std::vector<int> tile);
		std::vector<sf::Sprite> _getSprites();
		void loadTextures();
	};
}


#endif //GBEMULATOR_GPU_HPP
