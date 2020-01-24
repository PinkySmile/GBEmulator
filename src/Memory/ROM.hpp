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
	//! @brief Mémoire en lecture seule.
	class ROM : public Memory {
	public:
		ROM();
	};
}


#endif //GBEMULATOR_ROM_HPP
