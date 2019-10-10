/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.hpp
*/

#ifndef GBEMULATOR_CPU_INSTRUCTIONS_HPP
#define GBEMULATOR_CPU_INSTRUCTIONS_HPP


namespace GBEmulator {
	class CPU;
	namespace Instructions {
		void LD8(unsigned char &register1, unsigned char register2);
		void LD16(unsigned short &register1, unsigned short register2);
		void LDPTR(CPU &cpu, unsigned short &register1, unsigned short register2);
	}
}


#endif //GBEMULATOR_CPU_INSTRUCTIONS_HPP
