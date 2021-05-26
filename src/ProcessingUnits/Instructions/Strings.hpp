//
// Created by PinkySmile on 26/05/2021.
//

#ifndef GBEMULATOR_STRINGS_HPP
#define GBEMULATOR_STRINGS_HPP


#include <string>
#include <functional>
#include "../CPU.hpp"

namespace GBEmulator::Instructions
{
	//! @brief Transforme un entier dans sa représentation hexadécimal.
	//! @param i Entier à convertir.
	//! @param size Nombre de chiffre minimum.
	//! @return La représentation hexadécimale de i.
	standard::string intToHex(unsigned i, unsigned size = 2);

	extern const std::function<standard::string (const CPU &, uint16_t address)> _instructionsString[256];
	extern const std::function<standard::string (const CPU &, uint16_t address)> _bitLevelInstructionsString[256];
	extern const std::function<standard::string (const CPU &, uint16_t address)> _instructionsString2[256];
	extern const std::function<standard::string (const CPU &, uint16_t address)> _bitLevelInstructionsString2[256];
}


#endif //GBEMULATOR_STRINGS_HPP
