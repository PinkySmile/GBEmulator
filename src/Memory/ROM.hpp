/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.hpp
*/

#ifndef GBEMULATOR_ROM_HPP
#define GBEMULATOR_ROM_HPP


#ifndef ARDUINO
#include <map>
#include <string>
#else
#include "../ArduinoStuff/FakeSTL.hpp"
#endif
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
