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
		bool _readOnly;
		unsigned char _currentBank;
		unsigned short _bankSize;

	protected:
		size_t _size;
		unsigned char *_memory;

	public:
		Memory() = delete;
		Memory(const Memory &) = delete;
		~Memory() = default;
		Memory &operator=(const Memory &) = delete;
		Memory(unsigned size, unsigned short bankSize, bool readOnly = false);

		void setBank(unsigned char bank);
		unsigned char read(unsigned short address) const;
		unsigned char rawRead(unsigned short address) const;
		void write(unsigned short address,unsigned char value);
		void dump(unsigned short offset = 0) const;
	};
}


#endif //GBEMULATOR_MEMORY_HPP
