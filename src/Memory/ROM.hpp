/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.hpp
*/

#ifndef GBEMULATOR_ROM_HPP
#define GBEMULATOR_ROM_HPP


#include <map>
#include <string>
#include "Memory.hpp"

namespace GBEmulator::Memory
{
	class ROM : public Memory {
	public:
		ROM();
		ROM(const ROM &) = delete;
		~ROM() = default;
		ROM &operator=(const ROM &) = delete;
	};
}


#endif //GBEMULATOR_ROM_HPP
