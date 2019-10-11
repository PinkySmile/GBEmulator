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
		std::vector<sf::Texture> _textures;

	public:
		GPU();
		unsigned char readVRAM(unsigned short address);
		void writeVRAM(unsigned short address, unsigned char value);
		unsigned char readOAM(unsigned short address);
		void writeOAM(unsigned short address, unsigned char value);

	private:
		std::vector<int> getTile(std::size_t id);
		std::vector<int> decToBin(int nbr);
		sf::Texture getTextureFromTile(std::vector<int> tile);
		sf::Sprite getSprite();
	};
}


#endif //GBEMULATOR_GPU_HPP
