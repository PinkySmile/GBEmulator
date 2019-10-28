/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.hpp
*/

#ifndef GBEMULATOR_GPU_HPP
#define GBEMULATOR_GPU_HPP

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "../Memory/Memory.hpp"
#include "../LCD/ILCD.hpp"

#define TILE_DATA_SIZE 0x1800
#define NB_TILES TILE_DATA_SIZE * 4
#define BG_MAP_SIZE 0x800
#define OAM_SIZE 0x100
#define GPU_FULL_CYCLE_DURATION 70224

namespace GBEmulator
{
	class GPU {

	private:
		Memory _oam;
		Graphics::ILCD &_screen;
		unsigned char _scrollX;
		unsigned char _scrollY;
		unsigned char _bgPalette;
		unsigned char _control;
		unsigned char *_tiles;
		unsigned char *_backgroundMap;
		unsigned _cycles = 0;
		std::vector<unsigned> _tilesToUpdate;

	public:
		GPU(Graphics::ILCD &screen);
		~GPU();
		GPU() = delete;
		GPU(const GPU &) = delete;
		GPU &operator=(const GPU &) = delete;

		unsigned char getCurrentLine() const;
		unsigned char readVRAM(unsigned short address) const;
		unsigned char readOAM(unsigned short address) const;
		unsigned char getControlByte() const;
		unsigned char getBGPalette() const;
		unsigned char getXScroll() const;
		unsigned char getYScroll() const;

		void writeVRAM(unsigned short address, unsigned char value);
		void writeOAM(unsigned short address, unsigned char value);
		void setControlByte(unsigned char value);
		void setBGPalette(unsigned char value);
		void setXScroll(unsigned char value);
		void setYScroll(unsigned char value);
		void update(int cycle);

	private:
		void _updateTiles();
		unsigned char *_getTile(std::size_t id);
		unsigned char *_getTileMap(bool alt);
	};
}


#endif //GBEMULATOR_GPU_HPP
