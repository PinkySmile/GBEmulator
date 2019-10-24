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

namespace GBEmulator
{
	#define VRAM_SIZE 8 * 1024
	#define OAM_SIZE 159

	class GPU {

	private:
		Memory _vram;
		Memory _oam;
		Graphics::ILCD &_screen;

	public:
		GPU(Graphics::ILCD &screen);
		unsigned char readVRAM(unsigned short address) const;
		void writeVRAM(unsigned short address, unsigned char value);
		unsigned char readOAM(unsigned short address) const;
		void writeOAM(unsigned short address, unsigned char value);
		void update(int cycle);

	private:
		unsigned _cycles;

		std::vector<int> getTile(std::size_t id);
	};
}


#endif //GBEMULATOR_GPU_HPP
