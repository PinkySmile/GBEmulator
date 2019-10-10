/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Memory.hpp
*/

#ifndef GBEMULATOR_MEMORY_HPP
#define GBEMULATOR_MEMORY_HPP


#include <vector>

namespace GBEmulator
{
	class Memory {
	private:
		unsigned char _currentBank;
		unsigned short _bankSize;

	protected:
		std::vector<unsigned char> _memory;

	public:
		Memory(unsigned size, unsigned short bankSize);

		void setBank(unsigned char bank);
		unsigned char read(unsigned short address) const;
		void write(unsigned short address,unsigned char value);
	};
}


#endif //GBEMULATOR_MEMORY_HPP
