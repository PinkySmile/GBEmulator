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

#define VRAM_SIZE 0x2000
#define OAM_SIZE 0x100
#define GPU_FULL_CYCLE_DURATION 70224

namespace GBEmulator
{
	class GPU {

	private:
		Memory _oam;
		Graphics::ILCD &_screen;
		unsigned char *_tiles;

	public:
		GPU(Graphics::ILCD &screen);
		~GPU();
		GPU() = delete;
		GPU(const GPU &) = delete;
		GPU &operator=(const GPU &) = delete;

		unsigned char getCurrentLine() const;
		unsigned char readVRAM(unsigned short address) const;
		void writeVRAM(unsigned short address, unsigned char value);
		unsigned char readOAM(unsigned short address) const;
		void writeOAM(unsigned short address, unsigned char value);
		unsigned char readIOPorts(unsigned short address) const;
		void writeIOPorts(unsigned short address, unsigned char value);
		void update(int cycle);

	private:
		unsigned _cycles;
		std::vector<unsigned> _tilesToUpdate;

		void _updateTiles();
		unsigned char *_getTile(std::size_t id);
	};
}


#endif //GBEMULATOR_GPU_HPP
