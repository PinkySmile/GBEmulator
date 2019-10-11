/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.hpp
*/

#ifndef GBEMULATOR_GPU_HPP
#define GBEMULATOR_GPU_HPP

#include "../Memory/Memory.hpp"

namespace GBEmulator
{
	class GPU {
	private:
		Memory _vram;
		Memory _oam;

	public:
		GPU();
		std::vector<int> getTile(std::size_t id);
		std::vector<int> decToBin(int nbr);
	};
}


#endif //GBEMULATOR_GPU_HPP
